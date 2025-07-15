#include "Contact.h"
#include <iostream>

Contact::Contact(const std::string& name, const std::string& phone,
                 const std::string& email, const std::string& address)
    : name(name), phone(phone), email(email), address(address) {}

void Contact::printInfo() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Address: " << address << std::endl;
}

void Contact::setName(const std::string& name) {
    std::cout << "** Name changed : " << this->name << " -> " << name << std::endl;
    this->name = name;
}

std::string Contact::getName() const {
    return name;
}