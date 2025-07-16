#include "crow.h"
#include "AddressBook.h"
#include <iostream>
#include <nlohmann/json.hpp>

// Debug macro function
#define DEBUG_LOG(msg) std::cout << "[DEBUG] " << msg << std::endl

// URL decoding function to handle spaces and special characters
std::string urlDecode(const std::string& encoded) {
    std::string decoded;
    for (size_t i = 0; i < encoded.length(); ++i) {
        if (encoded[i] == '%' && i + 2 < encoded.length()) {
            int value = 0;
            std::sscanf(encoded.substr(i + 1, 2).c_str(), "%x", &value);
            decoded += static_cast<char>(value);
            i += 2;
        } else if (encoded[i] == '+') {
            decoded += ' ';
        } else {
            decoded += encoded[i];
        }
    }
    return decoded;
}

int main()
{
    // Create Crow app
    crow::SimpleApp app;

    // Create AddressBook object
    AddressBook addressBook;
    
    // Add sample data (in English)
    addressBook.addContact(Contact("John Smith", "123-456-7890", "john@example.com", "New York"));
    addressBook.addContact(Contact("Jane Doe", "987-654-3210", "jane@example.com", "Los Angeles"));
    addressBook.addContact(Contact("Mike Johnson", "555-123-4567", "mike@example.com", "Chicago"));
    
    DEBUG_LOG(addressBook.getContacts().size() << " sample contacts added.");

    // Root path (/) GET request handler
    CROW_ROUTE(app, "/")([](){
        return "Hello, C++ Web!";
    });
    
    // "/api/contacts" path GET request handler (get all contacts)
    CROW_ROUTE(app, "/api/contacts")
    ([&addressBook](){
        DEBUG_LOG("GET /api/contacts request received");
        
        // Convert all contacts to JSON
        nlohmann::json result = nlohmann::json::array();
        for (const auto& contact : addressBook.getContacts()) {
            nlohmann::json j;
            j["name"] = contact.getName();
            j["phone"] = contact.getPhone();
            j["email"] = contact.getEmail();
            j["address"] = contact.getAddress();
            result.push_back(j);
        }
        
        // Convert to JSON string
        // Second parameter 4 is the number of spaces for indentation
        std::string jsonStr = result.dump(4);
        
        DEBUG_LOG("Response data: " << jsonStr);
        
        // Set JSON response header and return
        crow::response res(jsonStr);
        res.set_header("Content-Type", "application/json");
        return res;
    });
    
    // "/api/contacts" path POST request handler (add new contact)
    CROW_ROUTE(app, "/api/contacts")
    .methods("POST"_method)
    ([&addressBook](const crow::request& req){
        DEBUG_LOG("POST /api/contacts request received");
        
        try {
            // Parse request body as JSON
            auto reqJson = nlohmann::json::parse(req.body);
            DEBUG_LOG("Request data: " << reqJson.dump());
            
            // Validate required fields
            if (!reqJson.contains("name") || !reqJson.contains("phone")) {
                crow::response res(400);  // Bad Request
                res.set_header("Content-Type", "application/json");
                nlohmann::json error = {{"error", "Name and phone are required fields"}};
                res.write(error.dump());
                return res;
            }
            
            // Create and add new contact
            Contact newContact(
                reqJson["name"].get<std::string>(),
                reqJson["phone"].get<std::string>(),
                reqJson.contains("email") ? reqJson["email"].get<std::string>() : "",
                reqJson.contains("address") ? reqJson["address"].get<std::string>() : ""
            );
            
            addressBook.addContact(newContact);
            DEBUG_LOG("New contact added: " << newContact.getName());
            
            // Return success response
            crow::response res(201);  // Created
            res.set_header("Content-Type", "application/json");
            nlohmann::json success = {
                {"message", "Contact successfully added"},
                {"contact", {
                    {"name", newContact.getName()},
                    {"phone", newContact.getPhone()},
                    {"email", newContact.getEmail()},
                    {"address", newContact.getAddress()}
                }}
            };
            res.write(success.dump(4));
            return res;
        }
        catch (const std::exception& e) {
            // Exception handling (JSON parsing error, etc.)
            crow::response res(400);  // Bad Request
            res.set_header("Content-Type", "application/json");
            nlohmann::json error = {{"error", std::string("Error processing request: ") + e.what()}};
            res.write(error.dump());
            return res;
        }
    });
    
    // "/api/contacts/{name}" path GET request handler (get specific contact)
    CROW_ROUTE(app, "/api/contacts/<string>")
    .methods("GET"_method)
    ([&addressBook](const std::string& name){
        // Decode URL to handle spaces and special characters
        std::string decodedName = urlDecode(name);
        
        DEBUG_LOG("GET /api/contacts/" << name << " request received");
        DEBUG_LOG("Decoded name: '" << decodedName << "'");
        DEBUG_LOG("Requested name length: " << name.length() << " bytes");
        DEBUG_LOG("Requested name hex dump: ");
        for (unsigned char c : name) {
            std::cout << std::hex << static_cast<int>(c) << " ";
        }
        std::cout << std::dec << std::endl;
        
        // Search contacts by name
        auto contacts = addressBook.findContactByName(decodedName);
        
        // Debug: print all contacts
        DEBUG_LOG("Current stored contacts:");
        for (const auto& contact : addressBook.getContacts()) {
            DEBUG_LOG(" - " << contact.getName() << " (length: " << contact.getName().length() << " bytes)");
            DEBUG_LOG("   hex dump: ");
            for (unsigned char c : contact.getName()) {
                std::cout << std::hex << static_cast<int>(c) << " ";
            }
            std::cout << std::dec << std::endl;
        }
        
        // Return 404 if contact not found
        if (contacts.empty()) {
            DEBUG_LOG("Contact not found: " << decodedName);
            crow::response res(404);  // Not Found
            res.set_header("Content-Type", "application/json");
            nlohmann::json error = {{"error", "Contact with this name not found"}};
            res.write(error.dump());
            return res;
        }
        
        // Convert contacts to JSON and return
        nlohmann::json result = nlohmann::json::array();
        for (const auto& contact : contacts) {
            nlohmann::json j;
            j["name"] = contact.getName();
            j["phone"] = contact.getPhone();
            j["email"] = contact.getEmail();
            j["address"] = contact.getAddress();
            result.push_back(j);
        }
        
        crow::response res(result.dump(4));
        res.set_header("Content-Type", "application/json");
        return res;
    });
    
    // "/api/contacts/{name}" path PUT request handler (update contact)
    CROW_ROUTE(app, "/api/contacts/<string>")
    .methods("PUT"_method)
    ([&addressBook](const crow::request& req, const std::string& name){
        // Decode URL to handle spaces and special characters
        std::string decodedName = urlDecode(name);
        
        DEBUG_LOG("PUT /api/contacts/" << name << " request received");
        DEBUG_LOG("Decoded name: '" << decodedName << "'");
        
        try {
            // Parse request body as JSON
            auto reqJson = nlohmann::json::parse(req.body);
            DEBUG_LOG("Request data: " << reqJson.dump());
            
            // Find contact by name
            Contact* contactToEdit = addressBook.findContactToEdit(decodedName);
            
            // Return 404 if contact not found
            if (contactToEdit == nullptr) {
                crow::response res(404);  // Not Found
                res.set_header("Content-Type", "application/json");
                nlohmann::json error = {{"error", "Contact with this name not found"}};
                res.write(error.dump());
                return res;
            }
            
            // Update fields (only those provided)
            if (reqJson.contains("phone")) {
                contactToEdit->setPhone(reqJson["phone"].get<std::string>());
            }
            if (reqJson.contains("email")) {
                contactToEdit->setEmail(reqJson["email"].get<std::string>());
            }
            if (reqJson.contains("address")) {
                contactToEdit->setAddress(reqJson["address"].get<std::string>());
            }
            
            DEBUG_LOG("Contact updated: " << contactToEdit->getName());
            
            // Return success response
            crow::response res(200);  // OK
            res.set_header("Content-Type", "application/json");
            nlohmann::json success = {
                {"message", "Contact successfully updated"},
                {"contact", {
                    {"name", contactToEdit->getName()},
                    {"phone", contactToEdit->getPhone()},
                    {"email", contactToEdit->getEmail()},
                    {"address", contactToEdit->getAddress()}
                }}
            };
            res.write(success.dump(4));
            return res;
        }
        catch (const std::exception& e) {
            // Exception handling
            crow::response res(400);  // Bad Request
            res.set_header("Content-Type", "application/json");
            nlohmann::json error = {{"error", std::string("Error processing request: ") + e.what()}};
            res.write(error.dump());
            return res;
        }
    });
    
    // "/api/contacts/{name}" path DELETE request handler (delete contact)
    CROW_ROUTE(app, "/api/contacts/<string>")
    .methods("DELETE"_method)
    ([&addressBook](const std::string& name){
        // Decode URL to handle spaces and special characters
        std::string decodedName = urlDecode(name);
        
        DEBUG_LOG("DELETE /api/contacts/" << name << " request received");
        DEBUG_LOG("Decoded name: '" << decodedName << "'");
        
        // Check if contact exists before deletion
        auto contacts = addressBook.findContactByName(decodedName);
        if (contacts.empty()) {
            crow::response res(404);  // Not Found
            res.set_header("Content-Type", "application/json");
            nlohmann::json error = {{"error", "Contact with this name not found"}};
            res.write(error.dump());
            return res;
        }
        
        // Delete contact
        addressBook.deleteContactByName(decodedName);
        DEBUG_LOG("Contact deleted: " << decodedName);
        
        // Return success response
        crow::response res(200);  // OK
        res.set_header("Content-Type", "application/json");
        nlohmann::json success = {{"message", "Contact successfully deleted"}};
        res.write(success.dump());
        return res;
    });

    // Run server on port 18080
    DEBUG_LOG("Server starting at http://localhost:18080");
    app.port(18080).multithreaded().run();

    return 0;
} 