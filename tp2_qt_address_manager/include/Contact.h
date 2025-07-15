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
    void setPhone(const std::string& phone);
    void setEmail(const std::string& email);
    void setAddress(const std::string& address);
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getAddress() const;
};
