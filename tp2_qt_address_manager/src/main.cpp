#include <QApplication> // 1. Qt 애플리케이션 클래스 포함
#include "MainWindow.h"  // 2. 우리가 만든 메인 윈도우 클래스 포함

int main(int argc, char *argv[])
{
    // 3. Qt 애플리케이션 객체 생성
    QApplication app(argc, argv);

    // 4. 메인 윈도우 객체 생성
    MainWindow window;

    // 5. 윈도우를 화면에 표시
    window.show();

    // 6. 애플리케이션의 이벤트 루프 시작
    return app.exec();
}