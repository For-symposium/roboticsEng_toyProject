#include "crow.h"
#include "AddressBook.h"
#include <iostream>

int main()
{
    // Crow 앱 객체 생성
    crow::SimpleApp app;

    // AddressBook 객체 생성 (나중에 사용)
    AddressBook addressBook;

    // "/" 경로 (루트 URL)에 대한 GET 요청 처리
    CROW_ROUTE(app, "/")([](){
        // 응답으로 문자열을 보냄
        return "Hello, C++ Web!";
    });

    // 18080 포트에서 서버 실행
    // .multithreaded() : 여러 요청을 동시에 처리 가능하게 함
    app.port(18080).multithreaded().run();

    return 0;
} 