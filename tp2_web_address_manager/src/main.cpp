#include "Contact.h"
#include "AddressBook.h"
#include <iostream>

int main() {
    Contact contact1("John", "+1 10 1234 5678", "john@example.com", "123 Main St");
    Contact contact2("Augustine", "+1 10 1234 5678", "augustine@example.com", "456 Main St");
    Contact contact3("John", "+1 10 1234 5678", "john@example.com", "123 Main St");
    Contact contact4("John", "+1 10 1234 5678", "john@example.com", "123 Main St");
    // contact1.printInfo();
    contact1.setName("John A");
    contact3.setName("John B");
    contact4.setName("John C");
    // contact1.printInfo();

    AddressBook addressBook;
    addressBook.addContact(contact1);
    addressBook.addContact(contact2);
    addressBook.addContact(contact3);
    addressBook.addContact(contact4);
    addressBook.printAllContacts();
    
    addressBook.findContactByName("John");
    addressBook.deleteContactByName("John A");
    addressBook.printAllContacts();
}