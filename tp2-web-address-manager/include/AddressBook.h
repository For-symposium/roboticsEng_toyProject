#pragma once
#include "Contact.h"
#include <vector>

class AddressBook {
    std::vector<Contact> contacts;
public:
    void addContact(const Contact& contact);
    void printAllContacts() const;
    std::vector<Contact> findContactByName(const std::string& keyword) const;
    Contact* findContactToEdit(const std::string& name);
    void deleteContactByName(const std::string& name);
    const std::vector<Contact>& getContacts() const;
}; 