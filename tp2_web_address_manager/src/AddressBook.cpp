#include "AddressBook.h"
#include <iostream>

void AddressBook::addContact(const Contact& contact) {
    contacts.push_back(contact);
}
void AddressBook::printAllContacts() const {
    for (const auto& contact : contacts) {
        contact.printInfo();
        std::cout << "--------------------" << std::endl;
    }
}
// findContact와 deleteContact는 네가 직접 구현해볼 것!

// 이름을 활용한 부분 검색 및 출력
// std::vector<std::string> AddressBook::findContactByName(const std::string& keyword) {
//     std::vector<std::string> foundContacts; 
//     for (const auto& contact : contacts) {
//         // 1. contact.getName()으로 이름을 가져옴
//         std::string name = contact.getName();
//         // 2. 이름 안에 keyword가 포함되어 있는지 .find()로 확인
//         if (name.find(keyword) != std::string::npos) {
//             // 3. 포함되어 있으면, foundContacts에 push_back
//             foundContacts.push_back(name);
//         }
//     }
//     return foundContacts;
// }

void AddressBook::findContactByName(const std::string& keyword) {
    for (const auto& contact : contacts) {
        if (contact.getName().find(keyword) != std::string::npos) {
            // contact.printInfo();
            std::cout << "Found: " << contact.getName() << std::endl;
        }
    }
    std::cout << "--------------------------------" << std::endl;
}

// 이름이 정확히 일치해야 삭제 가능
void AddressBook::deleteContactByName(const std::string& name) {
    for (auto it = contacts.begin(); it != contacts.end(); ) {
        if (it->getName() == name) {
            it = contacts.erase(it); // erase는 다음 유효한 반복자를 반환
            std::cout << "Deleted: " << name << std::endl;
        } else {
            ++it;
        }
    }
    std::cout << "--------------------------------" << std::endl;
}