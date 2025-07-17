# C++ 생성자 학습 프로그램

Database.h의 생성자 개념을 연습하고 익힐 수 있도록 만든 종합 학습 프로그램입니다.

## 📚 학습 목표

1. **Database 클래스의 생성자 패턴 이해**
   - `Database(const std::string& name)` 패턴 완전 마스터
   - 실제 소프트웨어 개발에서 사용되는 생성자 패턴

2. **C++ 생성자의 다양한 종류 학습**
   - 기본 생성자 (Default Constructor)
   - 매개변수 생성자 (Parameterized Constructor)
   - 복사 생성자 (Copy Constructor)
   - 이동 생성자 (Move Constructor)
   - 위임 생성자 (Delegating Constructor)

3. **모듈화된 코드 구조**
   - 단계별 학습이 가능한 구조
   - 실무에서 사용하는 베스트 프랙티스 적용

## 📁 파일 구조

```
test/
├── test.cpp                # 기본 예시와 연습 문제
├── unit_test.cpp          # 체계적인 단위 테스트
├── practice_solutions.cpp # 연습 문제 해답 및 심화 학습
└── README.md             # 이 파일
```

## 🚀 단계별 학습 가이드

### 1단계: 기본 예시 학습 (test.cpp)

```bash
g++ -std=c++17 -Wall -Wextra -o test_constructor test.cpp
./test_constructor
```

**학습 내용:**
- 예시 1: 기본 생성자 vs 매개변수 생성자
- 예시 2: 복사 생성자와 이동 생성자
- 예시 3: Database와 유사한 컨테이너 클래스
- 3개의 연습 문제 (TODO로 구현 필요)

### 2단계: 단위 테스트로 검증 (unit_test.cpp)

```bash
g++ -std=c++17 -Wall -Wextra -o unit_test unit_test.cpp
./unit_test
```

**학습 내용:**
- 자동화된 테스트로 생성자 동작 검증
- Database 패턴 테스트
- 메모리 관리 테스트
- 생성자/소멸자 호출 순서 학습

### 3단계: 완전한 해답과 심화 학습 (practice_solutions.cpp)

```bash
g++ -std=c++17 -Wall -Wextra -o practice_solutions practice_solutions.cpp
./practice_solutions
```

**학습 내용:**
- 모든 연습 문제의 완전한 해답
- 심화 문제: 다양한 생성자 패턴
- 위임 생성자 (C++11)
- 실무에서 사용되는 패턴들

## 🎯 핵심 학습 포인트

### Database 생성자 패턴
```cpp
class Database {
private:
    std::string name;
    
public:
    Database(const std::string& name) : name(name) {
        // 디버그 출력과 초기화 로직
    }
    
    ~Database() {
        // 정리 작업
    }
};
```

### 초기화 리스트의 중요성
```cpp
// ✅ 올바른 방법 (초기화 리스트 사용)
class BankAccount {
private:
    const std::string accountNumber;
    
public:
    BankAccount(const std::string& acc) : accountNumber(acc) {}
};

// ❌ 잘못된 방법 (const 멤버 변수는 초기화 리스트 필수)
```

### 디버그 출력 패턴
```cpp
Constructor() {
    std::cout << "[DEBUG] 생성자 호출: " << 정보 << std::endl;
}

~Destructor() {
    std::cout << "[DEBUG] 소멸자 호출: " << 정보 << std::endl;
}
```

## 🔧 실무 베스트 프랙티스

### 1. RAII (Resource Acquisition Is Initialization)
```cpp
class FileManager {
public:
    FileManager(const std::string& filename) {
        // 생성자에서 파일 열기
    }
    
    ~FileManager() {
        // 소멸자에서 파일 닫기
    }
};
```

### 2. 스마트 포인터 활용
```cpp
class School {
private:
    std::vector<std::unique_ptr<Student>> students;
    
public:
    void addStudent(const std::string& name) {
        students.push_back(std::make_unique<Student>(name));
    }
};
```

### 3. 초기화 리스트 사용
```cpp
// 성능상 이점 + const 멤버 변수 필수
MyClass(const std::string& name) : memberName(name) {}
```

## 🧪 테스트 결과 예시

```
=== 테스트 결과 ===
총 테스트: 20
통과: 20
실패: 0
성공률: 100%
```

## 📋 연습 문제 목록

### 기본 문제
1. **Car 클래스** - 기본 생성자와 매개변수 생성자 구현
2. **BankAccount 클래스** - 초기화 리스트 사용 (const 멤버 변수)
3. **School 클래스** - Database 패턴과 동일한 구조

### 심화 문제
1. **Vehicle 클래스** - 다양한 생성자 오버로딩
2. **Rectangle 클래스** - 위임 생성자 (C++11)

## 🎓 학습 완료 체크리스트

- [ ] Database(const std::string& name) 패턴 이해
- [ ] 기본 생성자와 매개변수 생성자의 차이점 파악
- [ ] 초기화 리스트의 중요성 (const 멤버 변수)
- [ ] 복사 생성자와 이동 생성자 동작 원리
- [ ] 생성자/소멸자 호출 순서 이해
- [ ] 스마트 포인터와 컨테이너에서의 객체 관리
- [ ] 디버그 출력을 통한 생명주기 추적
- [ ] 단위 테스트 작성 방법
- [ ] 실무에서 사용되는 생성자 패턴들

## 🔍 추가 학습 리소스

### C++ 생성자 관련 고급 주제
1. **Rule of Three/Five**
   - 소멸자, 복사 생성자, 복사 대입 연산자
   - 이동 생성자, 이동 대입 연산자

2. **Explicit 키워드**
   ```cpp
   explicit Database(const std::string& name);
   ```

3. **Factory 패턴**
   ```cpp
   static std::unique_ptr<Database> create(const std::string& name);
   ```

4. **Builder 패턴**
   ```cpp
   DatabaseBuilder().setName("test").setPath("/tmp").build();
   ```

## 💡 문제 해결 팁

### 컴파일 에러 해결
```bash
# C++17 표준 사용
g++ -std=c++17 -Wall -Wextra -o program file.cpp

# 디버그 정보 포함
g++ -g -std=c++17 -Wall -Wextra -o program file.cpp
```

### 일반적인 실수들
1. **const 멤버 변수** - 반드시 초기화 리스트 사용
2. **메모리 누수** - 스마트 포인터 사용 권장
3. **복사 vs 이동** - 성능 최적화를 위해 이동 생성자 활용

---

**작성자:** AI 코딩 어시스턴트  
**마지막 업데이트:** 2024년  
**C++ 표준:** C++17 이상 권장 