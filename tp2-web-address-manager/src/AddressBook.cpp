#include "AddressBook.h"

void AddressBook::addContact(const Contact& contact) {
    contacts.push_back(contact);
}
void AddressBook::printAllContacts() const {
    // This function is for console output, so we leave it empty
    // or remove it entirely in a web application.
}

// 이름을 활용한 부분 검색 및 출력
std::vector<Contact> AddressBook::findContactByName(const std::string& keyword) const {
    std::vector<Contact> foundContacts;
    for (const auto& contact : contacts) {
        if (contact.getName().find(keyword) != std::string::npos) {
            foundContacts.push_back(contact);
        }
    }
    return foundContacts;
}

Contact* AddressBook::findContactToEdit(const std::string& name) {
    for (auto& contact : contacts) {
        if (contact.getName() == name) {
            return &contact;
        }
    }
    return nullptr;
}

// 이름이 정확히 일치해야 삭제 가능
void AddressBook::deleteContactByName(const std::string& name) {
    contacts.erase(
        std::remove_if(contacts.begin(), contacts.end(),
        [name](const Contact& contact) {
            return contact.getName() == name;
        }
    ));
}

const std::vector<Contact>& AddressBook::getContacts() const {
    return contacts;
}

// JSON 변환 메서드 구현
nlohmann::json AddressBook::toJson() const {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& contact : contacts) {
        j.push_back(contact.toJson());
    }
    return j;
} 