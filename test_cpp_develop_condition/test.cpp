#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cout << "=== M1 MacBook C++ 개발 환경 테스트 ===" << std::endl;
    std::cout << "Hello, C++ World!" << std::endl;
    
    // 벡터 사용 테스트
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "벡터 테스트: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 문자열 테스트
    std::string message = "C++ 컴파일러가 정상적으로 작동합니다!";
    std::cout << message << std::endl;
    
    std::cout << "=== 테스트 완료 ===" << std::endl;
    return 0;
} 