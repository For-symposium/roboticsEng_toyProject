#include "Contact.h"

Contact::Contact(const std::string& name, const std::string& phone,
                 const std::string& email, const std::string& address)
    : name(name), phone(phone), email(email), address(address) {}

void Contact::printInfo() const {
    // This function is for console output, so we leave it empty
    // or remove it entirely in a web application.
}

void Contact::setName(const std::string& name) {
    this->name = name;
}

void Contact::setPhone(const std::string& phone) {
    this->phone = phone;
}

void Contact::setEmail(const std::string& email) {
    this->email = email;
}

void Contact::setAddress(const std::string& address) {
    this->address = address;
}

std::string Contact::getName() const {
    return name;
}

std::string Contact::getPhone() const {
    return phone;
}

std::string Contact::getEmail() const {
    return email;
}

std::string Contact::getAddress() const {
    return address;
} 