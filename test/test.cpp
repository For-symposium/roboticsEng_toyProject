#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 생성자 연습을 위한 예시 클래스들

// ===========================================
// 예시 1: 기본 생성자와 매개변수 생성자
// ===========================================
class Student {
private:
    std::string name;
    int age;
    std::string studentId;

public:
    // 기본 생성자 (Default Constructor)
    Student() {
        std::cout << "[DEBUG] Student 기본 생성자 호출" << std::endl;
        name = "Unknown";
        age = 0;
        studentId = "000000";
    }
    
    // 매개변수 생성자 (Parameterized Constructor)
    Student(const std::string& n, int a, const std::string& id) {
        std::cout << "[DEBUG] Student 매개변수 생성자 호출: " << n << std::endl;
        name = n;
        age = a;
        studentId = id;
    }
    
    // 소멸자
    ~Student() {
        std::cout << "[DEBUG] Student 소멸자 호출: " << name << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "이름: " << name << ", 나이: " << age << ", 학번: " << studentId << std::endl;
    }
    
    std::string getName() const { return name; }
};

// ===========================================
// 예시 2: 복사 생성자와 이동 생성자
// ===========================================
class Book {
private:
    std::string title;
    std::string author;
    int* pageCount; // 동적 메모리 할당 예시

public:
    // 매개변수 생성자
    Book(const std::string& t, const std::string& a, int pages) {
        std::cout << "[DEBUG] Book 매개변수 생성자 호출: " << t << std::endl;
        title = t;
        author = a;
        pageCount = new int(pages);
    }
    
    // 복사 생성자 (Copy Constructor)
    Book(const Book& other) {
        std::cout << "[DEBUG] Book 복사 생성자 호출: " << other.title << std::endl;
        title = other.title;
        author = other.author;
        pageCount = new int(*other.pageCount); // 깊은 복사
    }
    
    // 이동 생성자 (Move Constructor)
    Book(Book&& other) noexcept {
        std::cout << "[DEBUG] Book 이동 생성자 호출: " << other.title << std::endl;
        title = std::move(other.title);
        author = std::move(other.author);
        pageCount = other.pageCount;
        other.pageCount = nullptr; // 원본 객체의 포인터를 무효화
    }
    
    // 소멸자
    ~Book() {
        std::cout << "[DEBUG] Book 소멸자 호출: " << title << std::endl;
        delete pageCount;
    }
    
    void displayInfo() const {
        if (pageCount) {
            std::cout << "제목: " << title << ", 저자: " << author 
                      << ", 페이지: " << *pageCount << std::endl;
        }
    }
};

// ===========================================
// 예시 3: Database와 유사한 컨테이너 클래스
// ===========================================
class Library {
private:
    std::string libraryName;
    std::vector<std::unique_ptr<Book>> books;

public:
    // 매개변수 생성자 (Database 클래스와 유사한 패턴)
    Library(const std::string& name) : libraryName(name) {
        std::cout << "[DEBUG] Library 생성자 호출: " << name << std::endl;
        std::cout << "도서관 '" << libraryName << "'이 생성되었습니다." << std::endl;
    }
    
    // 소멸자
    ~Library() {
        std::cout << "[DEBUG] Library 소멸자 호출: " << libraryName << std::endl;
        std::cout << "도서관 '" << libraryName << "'이 폐관되었습니다." << std::endl;
    }
    
    void addBook(const std::string& title, const std::string& author, int pages) {
        books.push_back(std::make_unique<Book>(title, author, pages));
        std::cout << "도서 추가: " << title << std::endl;
    }
    
    std::string getName() const { return libraryName; }
    
    size_t getBookCount() const { return books.size(); }
};

// ===========================================
// 테스트 함수들
// ===========================================

void testExample1() {
    std::cout << "\n=== 예시 1: 기본 생성자 vs 매개변수 생성자 ===" << std::endl;
    
    // 기본 생성자 사용
    Student student1;
    student1.displayInfo();
    
    // 매개변수 생성자 사용
    Student student2("김철수", 20, "2024001");
    student2.displayInfo();
    
    std::cout << "--- 예시 1 완료 ---\n" << std::endl;
}

void testExample2() {
    std::cout << "\n=== 예시 2: 복사 생성자와 이동 생성자 ===" << std::endl;
    
    // 원본 객체 생성
    Book originalBook("C++ 프로그래밍", "홍길동", 500);
    originalBook.displayInfo();
    
    // 복사 생성자 사용
    Book copiedBook = originalBook;
    copiedBook.displayInfo();
    
    // 이동 생성자 사용 (임시 객체)
    Book movedBook = Book("Python 기초", "이영희", 300);
    movedBook.displayInfo();
    
    std::cout << "--- 예시 2 완료 ---\n" << std::endl;
}

void testExample3() {
    std::cout << "\n=== 예시 3: Database와 유사한 컨테이너 클래스 ===" << std::endl;
    
    // Library 객체 생성 (Database와 유사한 패턴)
    Library centralLibrary("중앙도서관");
    
    // 도서 추가
    centralLibrary.addBook("자료구조", "김교수", 400);
    centralLibrary.addBook("알고리즘", "박교수", 350);
    
    std::cout << "도서관 이름: " << centralLibrary.getName() << std::endl;
    std::cout << "보유 도서 수: " << centralLibrary.getBookCount() << std::endl;
    
    std::cout << "--- 예시 3 완료 ---\n" << std::endl;
}

// ===========================================
// 연습 문제들
// ===========================================

// 문제 1: 기본 생성자와 매개변수 생성자 구현
class Car {
private:
    std::string brand;
    std::string model;
    int year;
    
public:
    // TODO: 여기에 생성자들을 구현하세요
    // 1. 기본 생성자: brand="Unknown", model="Unknown", year=2000
    // 2. 매개변수 생성자: 모든 값을 매개변수로 받아 초기화
    
    void displayInfo() const {
        std::cout << "브랜드: " << brand << ", 모델: " << model 
                  << ", 연도: " << year << std::endl;
    }
};

// 문제 2: 초기화 리스트를 사용한 생성자
class BankAccount {
private:
    const std::string accountNumber; // const 멤버 변수
    std::string ownerName;
    double balance;
    
public:
    // TODO: 초기화 리스트를 사용한 생성자를 구현하세요
    // const 멤버 변수는 반드시 초기화 리스트에서 초기화해야 합니다
    
    void displayAccount() const {
        std::cout << "계좌번호: " << accountNumber << ", 소유자: " << ownerName 
                  << ", 잔액: " << balance << std::endl;
    }
};

// 문제 3: Database 클래스와 유사한 클래스 설계
class School {
private:
    std::string schoolName;
    std::vector<std::unique_ptr<Student>> students;
    
public:
    // TODO: Database 클래스의 생성자 패턴을 참고하여 구현하세요
    // 1. 매개변수 생성자: 학교 이름을 받아 초기화
    // 2. 소멸자: 적절한 정리 작업
    // 3. 학생 추가 메소드
    // 4. 학교 이름 반환 메소드
};

void testProblems() {
    std::cout << "\n=== 연습 문제 테스트 ===" << std::endl;
    std::cout << "위의 TODO 주석을 참고하여 생성자들을 구현해보세요!" << std::endl;
    std::cout << "구현 후 이 함수에서 테스트 코드를 작성해보세요." << std::endl;
}

// ===========================================
// 메인 함수
// ===========================================
int main() {
    std::cout << "=== C++ 생성자 학습 프로그램 ===" << std::endl;
    std::cout << "Database.h의 생성자 개념을 연습해봅시다!\n" << std::endl;
    
    // 예시들 실행
    testExample1();
    testExample2();
    testExample3();
    
    // 연습 문제
    testProblems();
    
    std::cout << "\n=== 프로그램 종료 ===" << std::endl;
    return 0;
}

/*
===========================================
학습 포인트 정리:
===========================================

1. 기본 생성자 (Default Constructor)
   - 매개변수가 없는 생성자
   - 객체를 기본값으로 초기화

2. 매개변수 생성자 (Parameterized Constructor)
   - Database(const std::string& name)와 같은 형태
   - 특정 값으로 객체를 초기화

3. 복사 생성자 (Copy Constructor)
   - 다른 객체를 복사하여 새 객체 생성
   - 깊은 복사 vs 얕은 복사 주의

4. 이동 생성자 (Move Constructor)
   - 임시 객체의 자원을 효율적으로 이동
   - 성능 최적화에 중요

5. 초기화 리스트 (Initialization List)
   - const 멤버 변수 초기화 필수
   - 성능상 이점

6. 소멸자 (Destructor)
   - 객체 소멸 시 자동 호출
   - 동적 메모리 정리 등
===========================================
*/
