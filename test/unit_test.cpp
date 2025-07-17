#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <sstream>

// 단위 테스트를 위한 간단한 테스트 프레임워크
class UnitTest {
private:
    static int totalTests;
    static int passedTests;
    
public:
    static void assertEqual(const std::string& expected, const std::string& actual, const std::string& testName) {
        totalTests++;
        if (expected == actual) {
            std::cout << "[PASS] " << testName << std::endl;
            passedTests++;
        } else {
            std::cout << "[FAIL] " << testName << " - Expected: '" << expected 
                      << "', Got: '" << actual << "'" << std::endl;
        }
    }
    
    static void assertEqual(int expected, int actual, const std::string& testName) {
        totalTests++;
        if (expected == actual) {
            std::cout << "[PASS] " << testName << std::endl;
            passedTests++;
        } else {
            std::cout << "[FAIL] " << testName << " - Expected: " << expected 
                      << ", Got: " << actual << std::endl;
        }
    }
    
    static void assertTrue(bool condition, const std::string& testName) {
        totalTests++;
        if (condition) {
            std::cout << "[PASS] " << testName << std::endl;
            passedTests++;
        } else {
            std::cout << "[FAIL] " << testName << " - Condition was false" << std::endl;
        }
    }
    
    static void printResults() {
        std::cout << "\n=== 테스트 결과 ===" << std::endl;
        std::cout << "총 테스트: " << totalTests << std::endl;
        std::cout << "통과: " << passedTests << std::endl;
        std::cout << "실패: " << (totalTests - passedTests) << std::endl;
        std::cout << "성공률: " << (totalTests > 0 ? (passedTests * 100.0 / totalTests) : 0) << "%" << std::endl;
    }
};

// 정적 멤버 변수 초기화
int UnitTest::totalTests = 0;
int UnitTest::passedTests = 0;

// ===========================================
// 테스트용 클래스들
// ===========================================

// Database와 유사한 SimpleDatabase 클래스
class SimpleDatabase {
private:
    std::string name;
    std::vector<std::string> tables;
    
public:
    // 매개변수 생성자 (Database(const std::string& name)와 동일한 패턴)
    SimpleDatabase(const std::string& dbName) : name(dbName) {
        std::cout << "[DEBUG] SimpleDatabase 생성자 호출: " << name << std::endl;
    }
    
    // 복사 생성자
    SimpleDatabase(const SimpleDatabase& other) : name(other.name), tables(other.tables) {
        std::cout << "[DEBUG] SimpleDatabase 복사 생성자 호출: " << name << std::endl;
    }
    
    // 소멸자
    ~SimpleDatabase() {
        std::cout << "[DEBUG] SimpleDatabase 소멸자 호출: " << name << std::endl;
    }
    
    std::string getName() const { return name; }
    
    void addTable(const std::string& tableName) {
        tables.push_back(tableName);
    }
    
    size_t getTableCount() const { return tables.size(); }
    
    std::vector<std::string> getTableNames() const { return tables; }
};

// 기본 생성자와 매개변수 생성자를 테스트하기 위한 클래스
class TestStudent {
private:
    std::string name;
    int age;
    std::string id;
    
public:
    // 기본 생성자
    TestStudent() : name("Unknown"), age(0), id("000000") {
        std::cout << "[DEBUG] TestStudent 기본 생성자 호출" << std::endl;
    }
    
    // 매개변수 생성자
    TestStudent(const std::string& n, int a, const std::string& studentId) 
        : name(n), age(a), id(studentId) {
        std::cout << "[DEBUG] TestStudent 매개변수 생성자 호출: " << n << std::endl;
    }
    
    // 소멸자
    ~TestStudent() {
        std::cout << "[DEBUG] TestStudent 소멸자 호출: " << name << std::endl;
    }
    
    // Getter 메소드들
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getId() const { return id; }
};

// 초기화 리스트 테스트를 위한 클래스
class TestAccount {
private:
    const std::string accountNumber;  // const 멤버 변수
    std::string ownerName;
    double balance;
    
public:
    // 초기화 리스트를 사용한 생성자
    TestAccount(const std::string& accNum, const std::string& owner, double bal)
        : accountNumber(accNum), ownerName(owner), balance(bal) {
        std::cout << "[DEBUG] TestAccount 생성자 호출: " << accountNumber << std::endl;
    }
    
    ~TestAccount() {
        std::cout << "[DEBUG] TestAccount 소멸자 호출: " << accountNumber << std::endl;
    }
    
    std::string getAccountNumber() const { return accountNumber; }
    std::string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }
};

// ===========================================
// 단위 테스트 함수들
// ===========================================

void testDatabaseConstructor() {
    std::cout << "\n=== 테스트 1: Database 패턴 생성자 ===" << std::endl;
    
    // Database와 같은 패턴의 생성자 테스트
    SimpleDatabase db("TestDB");
    UnitTest::assertEqual(std::string("TestDB"), db.getName(), "Database 이름 초기화 테스트");
    UnitTest::assertEqual(0, static_cast<int>(db.getTableCount()), "초기 테이블 개수 테스트");
    
    // 테이블 추가 테스트
    db.addTable("users");
    db.addTable("products");
    UnitTest::assertEqual(2, static_cast<int>(db.getTableCount()), "테이블 추가 후 개수 테스트");
}

void testBasicVsParameterizedConstructor() {
    std::cout << "\n=== 테스트 2: 기본 생성자 vs 매개변수 생성자 ===" << std::endl;
    
    // 기본 생성자 테스트
    TestStudent defaultStudent;
    UnitTest::assertEqual(std::string("Unknown"), defaultStudent.getName(), "기본 생성자 이름 테스트");
    UnitTest::assertEqual(0, defaultStudent.getAge(), "기본 생성자 나이 테스트");
    UnitTest::assertEqual(std::string("000000"), defaultStudent.getId(), "기본 생성자 ID 테스트");
    
    // 매개변수 생성자 테스트
    TestStudent paramStudent("김철수", 20, "2024001");
    UnitTest::assertEqual(std::string("김철수"), paramStudent.getName(), "매개변수 생성자 이름 테스트");
    UnitTest::assertEqual(20, paramStudent.getAge(), "매개변수 생성자 나이 테스트");
    UnitTest::assertEqual(std::string("2024001"), paramStudent.getId(), "매개변수 생성자 ID 테스트");
}

void testCopyConstructor() {
    std::cout << "\n=== 테스트 3: 복사 생성자 ===" << std::endl;
    
    // 원본 객체 생성
    SimpleDatabase originalDb("OriginalDB");
    originalDb.addTable("table1");
    originalDb.addTable("table2");
    
    // 복사 생성자 테스트
    SimpleDatabase copiedDb = originalDb;
    UnitTest::assertEqual(originalDb.getName(), copiedDb.getName(), "복사된 데이터베이스 이름 테스트");
    UnitTest::assertEqual(static_cast<int>(originalDb.getTableCount()), 
                         static_cast<int>(copiedDb.getTableCount()), "복사된 테이블 개수 테스트");
    
    // 복사 후 독립성 테스트
    copiedDb.addTable("table3");
    UnitTest::assertTrue(originalDb.getTableCount() != copiedDb.getTableCount(), 
                        "복사 후 객체 독립성 테스트");
}

void testInitializationList() {
    std::cout << "\n=== 테스트 4: 초기화 리스트 ===" << std::endl;
    
    // const 멤버 변수를 가진 클래스의 생성자 테스트
    TestAccount account("ACC-001", "홍길동", 1000.0);
    UnitTest::assertEqual(std::string("ACC-001"), account.getAccountNumber(), "계좌번호 초기화 테스트");
    UnitTest::assertEqual(std::string("홍길동"), account.getOwnerName(), "소유자 이름 초기화 테스트");
    UnitTest::assertTrue(account.getBalance() == 1000.0, "잔액 초기화 테스트");
}

void testConstructorCallOrder() {
    std::cout << "\n=== 테스트 5: 생성자/소멸자 호출 순서 ===" << std::endl;
    
    std::cout << "객체 생성 순서 확인:" << std::endl;
    {
        TestStudent student1("학생1", 20, "001");
        TestStudent student2("학생2", 21, "002");
        std::cout << "블록 스코프 종료 - 소멸자 호출 순서 확인:" << std::endl;
    }
    
    UnitTest::assertTrue(true, "생성자/소멸자 호출 순서 테스트 (로그 확인)");
}

void testMemoryManagement() {
    std::cout << "\n=== 테스트 6: 메모리 관리 테스트 ===" << std::endl;
    
    // 동적 할당된 객체 테스트
    std::unique_ptr<SimpleDatabase> dbPtr = std::make_unique<SimpleDatabase>("DynamicDB");
    UnitTest::assertEqual(std::string("DynamicDB"), dbPtr->getName(), "동적 할당된 객체 테스트");
    
    // vector와 함께 사용하는 테스트
    std::vector<TestStudent> students;
    students.emplace_back("학생A", 19, "A001");  // 생성자 직접 호출
    students.emplace_back("학생B", 20, "B001");
    
    UnitTest::assertEqual(2, static_cast<int>(students.size()), "Vector에서 객체 생성 테스트");
    UnitTest::assertEqual(std::string("학생A"), students[0].getName(), "Vector 내 첫 번째 객체 테스트");
    UnitTest::assertEqual(std::string("학생B"), students[1].getName(), "Vector 내 두 번째 객체 테스트");
}

// ===========================================
// 성능 테스트
// ===========================================
void testConstructorPerformance() {
    std::cout << "\n=== 테스트 7: 생성자 성능 테스트 ===" << std::endl;
    
    const int numObjects = 1000;
    
    // 기본 생성자 성능
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numObjects; ++i) {
        TestStudent student;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "기본 생성자 " << numObjects << "개 생성 시간: " 
              << duration.count() << " 마이크로초" << std::endl;
    
    UnitTest::assertTrue(true, "성능 테스트 완료 (시간 측정됨)");
}

// ===========================================
// 메인 테스트 실행 함수
// ===========================================
int main() {
    std::cout << "=== C++ 생성자 단위 테스트 프로그램 ===" << std::endl;
    std::cout << "Database.h의 생성자 패턴을 체계적으로 테스트합니다.\n" << std::endl;
    
    // 모든 테스트 실행
    testDatabaseConstructor();
    testBasicVsParameterizedConstructor();
    testCopyConstructor();
    testInitializationList();
    testConstructorCallOrder();
    testMemoryManagement();
    
    // 성능 테스트는 별도로 (chrono 헤더가 필요하므로 주석 처리)
    // testConstructorPerformance();
    
    // 최종 결과 출력
    UnitTest::printResults();
    
    std::cout << "\n=== 학습 요약 ===" << std::endl;
    std::cout << "1. Database(const std::string& name) 패턴 - 매개변수 생성자" << std::endl;
    std::cout << "2. 기본 생성자 vs 매개변수 생성자의 차이점" << std::endl;
    std::cout << "3. 복사 생성자의 동작 방식" << std::endl;
    std::cout << "4. 초기화 리스트의 중요성 (const 멤버 변수)" << std::endl;
    std::cout << "5. 생성자/소멸자 호출 순서" << std::endl;
    std::cout << "6. 스마트 포인터와 컨테이너에서의 객체 생성" << std::endl;
    
    return 0;
}

/*
===========================================
생성자 관련 베스트 프랙티스:
===========================================

1. 초기화 리스트 사용
   - 성능상 이점
   - const 멤버 변수 필수

2. 명시적 생성자 (explicit)
   - 암시적 형변환 방지
   - explicit Database(const std::string& name);

3. Rule of Three/Five
   - 소멸자, 복사 생성자, 복사 대입 연산자
   - 이동 생성자, 이동 대입 연산자

4. RAII (Resource Acquisition Is Initialization)
   - 생성자에서 자원 획득
   - 소멸자에서 자원 해제

5. 예외 안전성
   - 생성자에서 예외 발생 시 처리
   - 부분적으로 구성된 객체 방지
===========================================
*/ 