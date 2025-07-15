#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <thread>
#include <chrono>
#include <functional>

// 클래스 정의
class Calculator {
private:
    std::string name;
    
public:
    Calculator(const std::string& n) : name(n) {}
    
    template<typename T>
    T add(T a, T b) {
        return a + b;
    }
    
    template<typename T>
    T multiply(T a, T b) {
        return a * b;
    }
    
    void printInfo() const {
        std::cout << "계산기: " << name << std::endl;
    }
};

// 람다 함수와 스마트 포인터 테스트
void testModernCpp() {
    std::cout << "\n=== Modern C++ 기능 테스트 ===" << std::endl;
    
    // 람다 함수
    auto lambda = [](int x) { return x * x; };
    std::cout << "람다 함수 테스트: 5^2 = " << lambda(5) << std::endl;
    
    // 스마트 포인터
    auto calc = std::make_unique<Calculator>("고급 계산기");
    calc->printInfo();
    
    // 벡터와 알고리즘
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    std::sort(numbers.begin(), numbers.end());
    
    std::cout << "정렬된 숫자: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 함수 객체
    std::function<int(int, int)> add = [](int a, int b) { return a + b; };
    std::cout << "함수 객체 테스트: 10 + 20 = " << add(10, 20) << std::endl;
}

// 멀티스레딩 테스트
void testThreading() {
    std::cout << "\n=== 멀티스레딩 테스트 ===" << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::thread t1([]() {
        std::cout << "스레드 1 실행 중..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });
    
    std::thread t2([]() {
        std::cout << "스레드 2 실행 중..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });
    
    t1.join();
    t2.join();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "스레드 실행 완료 (소요시간: " << duration.count() << "ms)" << std::endl;
}

int main() {
    std::cout << "=== M1 MacBook 고급 C++ 개발 환경 테스트 ===" << std::endl;
    
    // 기본 기능 테스트
    Calculator calc("기본 계산기");
    calc.printInfo();
    
    std::cout << "템플릿 함수 테스트:" << std::endl;
    std::cout << "정수 덧셈: " << calc.add(10, 20) << std::endl;
    std::cout << "실수 곱셈: " << calc.multiply(3.14, 2.0) << std::endl;
    
    // Modern C++ 기능 테스트
    testModernCpp();
    
    // 멀티스레딩 테스트
    testThreading();
    
    std::cout << "\n=== 모든 테스트 완료 ===" << std::endl;
    std::cout << "M1 MacBook에서 C++ 개발 환경이 완벽하게 작동합니다!" << std::endl;
    
    return 0;
} 