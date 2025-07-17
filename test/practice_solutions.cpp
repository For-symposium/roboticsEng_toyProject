#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ===========================================
// 연습 문제 해답
// ===========================================

// 문제 1 해답: 기본 생성자와 매개변수 생성자 구현
class Car {
private:
    std::string brand;
    std::string model;
    int year;
    
public:
    // 해답 1: 기본 생성자
    Car() {
        std::cout << "[DEBUG] Car 기본 생성자 호출" << std::endl;
        brand = "Unknown";
        model = "Unknown";
        year = 2000;
    }
    
    // 해답 2: 매개변수 생성자
    Car(const std::string& b, const std::string& m, int y) {
        std::cout << "[DEBUG] Car 매개변수 생성자 호출: " << b << " " << m << std::endl;
        brand = b;
        model = m;
        year = y;
    }
    
    // 소멸자
    ~Car() {
        std::cout << "[DEBUG] Car 소멸자 호출: " << brand << " " << model << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "브랜드: " << brand << ", 모델: " << model 
                  << ", 연도: " << year << std::endl;
    }
    
    // Getter 메소드들 (테스트용)
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
};

// 문제 2 해답: 초기화 리스트를 사용한 생성자
class BankAccount {
private:
    const std::string accountNumber; // const 멤버 변수
    std::string ownerName;
    double balance;
    
public:
    // 해답: 초기화 리스트를 사용한 생성자
    BankAccount(const std::string& accNum, const std::string& owner, double bal)
        : accountNumber(accNum), ownerName(owner), balance(bal) {
        std::cout << "[DEBUG] BankAccount 생성자 호출: " << accountNumber << std::endl;
        
        // 여기서 추가적인 유효성 검사를 할 수 있습니다
        if (balance < 0) {
            std::cout << "[WARNING] 음수 잔액으로 계좌가 생성되었습니다!" << std::endl;
        }
    }
    
    // 기본 생성자 (초기화 리스트 필수)
    BankAccount() : accountNumber("000000"), ownerName("Unknown"), balance(0.0) {
        std::cout << "[DEBUG] BankAccount 기본 생성자 호출" << std::endl;
    }
    
    // 소멸자
    ~BankAccount() {
        std::cout << "[DEBUG] BankAccount 소멸자 호출: " << accountNumber << std::endl;
    }
    
    void displayAccount() const {
        std::cout << "계좌번호: " << accountNumber << ", 소유자: " << ownerName 
                  << ", 잔액: " << balance << std::endl;
    }
    
    // Getter 메소드들
    std::string getAccountNumber() const { return accountNumber; }
    std::string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }
};

// 문제 3 해답: Database 클래스와 유사한 클래스 설계
class Student {
private:
    std::string name;
    int age;
    std::string studentId;
    
public:
    Student(const std::string& n, int a, const std::string& id) 
        : name(n), age(a), studentId(id) {
        std::cout << "[DEBUG] Student 생성자 호출: " << name << std::endl;
    }
    
    ~Student() {
        std::cout << "[DEBUG] Student 소멸자 호출: " << name << std::endl;
    }
    
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getStudentId() const { return studentId; }
};

class School {
private:
    std::string schoolName;
    std::vector<std::unique_ptr<Student>> students;
    
public:
    // 해답 1: 매개변수 생성자 (Database 패턴과 동일)
    School(const std::string& name) : schoolName(name) {
        std::cout << "[DEBUG] School 생성자 호출: " << schoolName << std::endl;
        std::cout << "학교 '" << schoolName << "'이 설립되었습니다." << std::endl;
    }
    
    // 해답 2: 소멸자 (적절한 정리 작업)
    ~School() {
        std::cout << "[DEBUG] School 소멸자 호출: " << schoolName << std::endl;
        std::cout << "학교 '" << schoolName << "'이 폐교되었습니다." << std::endl;
        // unique_ptr이 자동으로 학생들을 정리해줍니다
    }
    
    // 해답 3: 학생 추가 메소드
    void addStudent(const std::string& name, int age, const std::string& studentId) {
        students.push_back(std::make_unique<Student>(name, age, studentId));
        std::cout << "학생 추가: " << name << " (학번: " << studentId << ")" << std::endl;
    }
    
    // 해답 4: 학교 이름 반환 메소드
    std::string getName() const { 
        return schoolName; 
    }
    
    // 추가 메소드들
    size_t getStudentCount() const { 
        return students.size(); 
    }
    
    void displaySchoolInfo() const {
        std::cout << "=== " << schoolName << " 정보 ===" << std::endl;
        std::cout << "총 학생 수: " << students.size() << "명" << std::endl;
        for (const auto& student : students) {
            std::cout << "- " << student->getName() << " (나이: " << student->getAge() 
                      << ", 학번: " << student->getStudentId() << ")" << std::endl;
        }
    }
};

// ===========================================
// 심화 문제들
// ===========================================

// 심화 문제 1: 다양한 생성자를 가진 클래스
class Vehicle {
private:
    std::string type;
    std::string brand;
    int year;
    double price;
    
public:
    // 기본 생성자
    Vehicle() : type("Unknown"), brand("Unknown"), year(2000), price(0.0) {
        std::cout << "[DEBUG] Vehicle 기본 생성자" << std::endl;
    }
    
    // 부분 매개변수 생성자 1
    Vehicle(const std::string& t) : type(t), brand("Unknown"), year(2000), price(0.0) {
        std::cout << "[DEBUG] Vehicle 타입 생성자: " << type << std::endl;
    }
    
    // 부분 매개변수 생성자 2
    Vehicle(const std::string& t, const std::string& b) 
        : type(t), brand(b), year(2000), price(0.0) {
        std::cout << "[DEBUG] Vehicle 타입+브랜드 생성자: " << type << " " << brand << std::endl;
    }
    
    // 전체 매개변수 생성자
    Vehicle(const std::string& t, const std::string& b, int y, double p)
        : type(t), brand(b), year(y), price(p) {
        std::cout << "[DEBUG] Vehicle 전체 매개변수 생성자: " 
                  << type << " " << brand << " " << year << std::endl;
    }
    
    // 복사 생성자
    Vehicle(const Vehicle& other) 
        : type(other.type), brand(other.brand), year(other.year), price(other.price) {
        std::cout << "[DEBUG] Vehicle 복사 생성자: " << type << " " << brand << std::endl;
    }
    
    ~Vehicle() {
        std::cout << "[DEBUG] Vehicle 소멸자: " << type << " " << brand << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "차종: " << type << ", 브랜드: " << brand 
                  << ", 연도: " << year << ", 가격: " << price << std::endl;
    }
};

// 심화 문제 2: 위임 생성자 (Delegating Constructor)
class Rectangle {
private:
    double width;
    double height;
    std::string color;
    
public:
    // 기본 생성자 (위임 생성자 사용)
    Rectangle() : Rectangle(1.0, 1.0, "black") {
        std::cout << "[DEBUG] Rectangle 기본 생성자 (위임)" << std::endl;
    }
    
    // 크기만 지정하는 생성자 (위임 생성자 사용)
    Rectangle(double w, double h) : Rectangle(w, h, "black") {
        std::cout << "[DEBUG] Rectangle 크기 생성자 (위임)" << std::endl;
    }
    
    // 메인 생성자 (모든 매개변수)
    Rectangle(double w, double h, const std::string& c) 
        : width(w), height(h), color(c) {
        std::cout << "[DEBUG] Rectangle 메인 생성자: " << width << "x" << height 
                  << " " << color << std::endl;
    }
    
    ~Rectangle() {
        std::cout << "[DEBUG] Rectangle 소멸자: " << width << "x" << height << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "사각형 - 너비: " << width << ", 높이: " << height 
                  << ", 색상: " << color << std::endl;
    }
    
    double getArea() const { return width * height; }
};

// ===========================================
// 테스트 함수들
// ===========================================

void testProblem1Solutions() {
    std::cout << "\n=== 문제 1 해답 테스트: Car 클래스 ===" << std::endl;
    
    // 기본 생성자 테스트
    Car defaultCar;
    defaultCar.displayInfo();
    
    // 매개변수 생성자 테스트
    Car specificCar("토요타", "캠리", 2023);
    specificCar.displayInfo();
    
    std::cout << "--- 문제 1 완료 ---\n" << std::endl;
}

void testProblem2Solutions() {
    std::cout << "\n=== 문제 2 해답 테스트: BankAccount 클래스 ===" << std::endl;
    
    // 기본 생성자 테스트
    BankAccount defaultAccount;
    defaultAccount.displayAccount();
    
    // 매개변수 생성자 테스트
    BankAccount userAccount("12345", "김은행", 50000.0);
    userAccount.displayAccount();
    
    // 음수 잔액 테스트
    BankAccount debtAccount("99999", "빚쟁이", -1000.0);
    debtAccount.displayAccount();
    
    std::cout << "--- 문제 2 완료 ---\n" << std::endl;
}

void testProblem3Solutions() {
    std::cout << "\n=== 문제 3 해답 테스트: School 클래스 ===" << std::endl;
    
    // School 객체 생성 (Database 패턴과 동일)
    School mySchool("한국대학교");
    
    // 학생 추가
    mySchool.addStudent("김학생", 20, "2024001");
    mySchool.addStudent("이학생", 19, "2024002");
    mySchool.addStudent("박학생", 21, "2024003");
    
    // 학교 정보 출력
    mySchool.displaySchoolInfo();
    
    std::cout << "학교 이름: " << mySchool.getName() << std::endl;
    std::cout << "총 학생 수: " << mySchool.getStudentCount() << "명" << std::endl;
    
    std::cout << "--- 문제 3 완료 ---\n" << std::endl;
}

void testAdvancedProblems() {
    std::cout << "\n=== 심화 문제 테스트 ===" << std::endl;
    
    // Vehicle 다양한 생성자 테스트
    std::cout << "\n--- Vehicle 클래스 (다양한 생성자) ---" << std::endl;
    Vehicle v1;                                          // 기본 생성자
    Vehicle v2("승용차");                                // 타입만
    Vehicle v3("트럭", "현대");                          // 타입+브랜드
    Vehicle v4("스포츠카", "페라리", 2023, 200000000.0); // 전체
    Vehicle v5 = v4;                                     // 복사 생성자
    
    v1.displayInfo();
    v2.displayInfo();
    v3.displayInfo();
    v4.displayInfo();
    v5.displayInfo();
    
    // Rectangle 위임 생성자 테스트
    std::cout << "\n--- Rectangle 클래스 (위임 생성자) ---" << std::endl;
    Rectangle r1;                              // 기본 생성자
    Rectangle r2(5.0, 3.0);                   // 크기만
    Rectangle r3(10.0, 8.0, "red");           // 전체
    
    r1.displayInfo();
    r2.displayInfo();
    r3.displayInfo();
    
    std::cout << "r3의 넓이: " << r3.getArea() << std::endl;
    
    std::cout << "--- 심화 문제 완료 ---\n" << std::endl;
}

// ===========================================
// 메인 함수
// ===========================================
int main() {
    std::cout << "=== 생성자 연습 문제 해답 및 심화 학습 ===" << std::endl;
    std::cout << "Database.h의 생성자 패턴을 완전히 마스터해봅시다!\n" << std::endl;
    
    // 기본 문제들의 해답 테스트
    testProblem1Solutions();
    testProblem2Solutions();
    testProblem3Solutions();
    
    // 심화 문제들 테스트
    testAdvancedProblems();
    
    std::cout << "\n=== 최종 학습 정리 ===" << std::endl;
    std::cout << "✅ Database(const std::string& name) 패턴 완전 이해" << std::endl;
    std::cout << "✅ 기본 생성자와 매개변수 생성자의 차이점 학습" << std::endl;
    std::cout << "✅ 초기화 리스트의 중요성 (const 멤버 변수)" << std::endl;
    std::cout << "✅ 복사 생성자와 소멸자의 올바른 구현" << std::endl;
    std::cout << "✅ 스마트 포인터와 컨테이너에서의 객체 관리" << std::endl;
    std::cout << "✅ 실제 소프트웨어 개발에서 사용되는 패턴들" << std::endl;
    
    std::cout << "\n=== 프로그램 종료 ===" << std::endl;
    return 0;
}

/*
===========================================
실무에서 사용되는 생성자 패턴 정리:
===========================================

1. Database 패턴 (우리가 학습한 것)
   Database(const std::string& name) : name(name) {}
   - 리소스 이름으로 초기화
   - 대부분의 매니저 클래스에서 사용

2. Factory 패턴과 생성자
   static std::unique_ptr<Database> create(const std::string& name);
   - 생성 로직을 캡슐화
   - 에러 처리가 용이

3. Builder 패턴과 생성자
   DatabaseBuilder().setName("test").setPath("/tmp").build();
   - 복잡한 객체 생성을 단계별로

4. RAII 패턴
   생성자에서 자원 획득, 소멸자에서 자원 해제
   - 파일, 네트워크 연결, 메모리 등

5. 단위 테스트에서의 생성자
   Mock 객체, Test Fixture 등에서 중요
===========================================
*/ 