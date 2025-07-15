#pragma once
#include <string>

class Contact {
private:
    std::string name;
    std::string phone;
    std::string email;
    std::string address;
public:
    Contact(const std::string& name, const std::string& phone,
            const std::string& email, const std::string& address);
    void printInfo() const;
    // getter/setter 함수들
    void setName(const std::string& name);
    std::string getName() const;
};
