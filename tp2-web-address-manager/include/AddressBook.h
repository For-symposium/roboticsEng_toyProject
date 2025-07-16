#pragma once
#include "Contact.h"
#include <vector>
#include <nlohmann/json.hpp>  // JSON 라이브러리 헤더 추가

class AddressBook {
    std::vector<Contact> contacts;
public:
    void addContact(const Contact& contact);
    void printAllContacts() const;
    std::vector<Contact> findContactByName(const std::string& keyword) const;
    Contact* findContactToEdit(const std::string& name);
    void deleteContactByName(const std::string& name);
    const std::vector<Contact>& getContacts() const;
    
    // JSON 변환 메서드 추가
    nlohmann::json toJson() const;
}; 