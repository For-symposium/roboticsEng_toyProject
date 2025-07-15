#include <iostream>

// 함수 선언 (헤더 파일 역할)
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
double divide(double a, double b);

int main() {
    std::cout << "=== 수학 함수 테스트 ===" << std::endl;
    
    int a = 10, b = 3;
    
    std::cout << a << " + " << b << " = " << add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << subtract(a, b) << std::endl;
    std::cout << a << " * " << b << " = " << multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << divide(a, b) << std::endl;
    
    return 0;
} 