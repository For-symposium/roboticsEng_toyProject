#pragma once
#include <string>
#include <nlohmann/json.hpp>  // JSON 라이브러리 헤더 추가

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
    
    // JSON 변환 메서드 추가
    nlohmann::json toJson() const;
}; 