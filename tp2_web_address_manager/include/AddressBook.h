#pragma once
#include "Contact.h"
#include <vector>

class AddressBook {
    std::vector<Contact> contacts;
public:
    void addContact(const Contact& contact);
    void printAllContacts() const;
    void findContactByName(const std::string& keyword);
    void deleteContactByName(const std::string& name);
};