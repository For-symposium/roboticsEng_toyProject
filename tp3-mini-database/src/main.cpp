#include <iostream>
#include <string>
#include "../include/database.h"
#include "../include/parser.h"

int main() {
    // 데이터베이스 생성
    Database db("MyDB");
    Parser parser;
    
    std::cout << "미니 데이터베이스 시작 (종료하려면 'exit' 입력)" << std::endl;
    
    while (true) {
        std::string line;
        std::cout << "SQL> ";
        std::getline(std::cin, line);
        
        // 종료 명령 확인
        if (line == "exit") {
            break;
        }
        
        // SQL 파싱 및 실행
        try {
            SqlCommand command = parser.parse(line);
            parser.executeCommand(db, command);
        } catch (const std::exception& e) {
            std::cerr << "오류: " << e.what() << std::endl;
        }
    }
    
    std::cout << "데이터베이스 종료" << std::endl;
    return 0;
}