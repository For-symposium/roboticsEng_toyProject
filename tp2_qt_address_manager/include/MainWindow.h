/*
 * #ifndef, #define, #endif : 헤더 가드(Header Guard)
 * 이 파일이 컴파일 과정에서 여러 번 포함(include)되는 것을 방지합니다.
 * 만약 MAINWINDOW_H가 아직 정의되지 않았다면(#ifndef), 아래 코드를 처리하고
 * MAINWINDOW_H를 정의(#define)합니다. 다음에 이 파일을 또 만나면
 * 이미 정의되어 있으므로 중복 처리를 건너뜁니다.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Qt의 기본 위젯 클래스들을 포함합니다.
 * QMainWindow: 메뉴바, 툴바, 상태바 등을 가질 수 있는 메인 윈도우의 뼈대
 * QListWidget: 항목들을 목록 형태로 보여주는 위젯
 * QPushButton: 사용자가 클릭할 수 있는 버튼 위젯
 * QLineEdit: 한 줄의 텍스트를 입력받는 위젯
 */
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "AddressBook.h" // 우리가 만든 주소록 관리 클래스
#include <vector>        // C++ 표준 라이브러리의 동적 배열(vector) 사용

/*
 * MainWindow 클래스 선언
 * ': public QMainWindow' -> QMainWindow 클래스의 모든 기능과 특징을 상속받습니다.
 * 즉, MainWindow는 QMainWindow의 특별한 버전입니다.
 */
class MainWindow : public QMainWindow {
    /*
     * Q_OBJECT 매크로: Qt의 핵심 기능인 시그널-슬롯 메커니즘, 국제화(번역) 등을
     * 사용하려면 반드시 클래스 선언 첫 부분에 추가해야 합니다.
     * 컴파일 과정에서 Qt의 moc(Meta-Object Compiler)가 이 매크로를 보고
     * 필요한 추가 C++ 코드를 생성해줍니다.
     */
    Q_OBJECT

public:
    /*
     * 생성자 (Constructor)
     * 'explicit' 키워드는 의도치 않은 형 변환을 방지하는 C++ 문법입니다.
     * QWidget *parent = nullptr: 이 윈도우를 담을 부모 위젯을 지정할 수 있습니다.
     * nullptr는 부모가 없다는 의미이며, 이 경우 최상위 윈도우가 됩니다.
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); // 소멸자 (Destructor): 객체가 사라질 때 호출됩니다.

/*
 * 'private slots:' 섹션
 * 슬롯(Slot)은 특정 신호(Signal)에 반응하여 실행되는 일반 C++ 함수입니다.
 * 예를 들어, 버튼이 '클릭되었다'는 신호에 '연락처를 추가하라'는 슬롯 함수를 연결합니다.
 * private으로 선언하여 클래스 내부에서만 이 함수들을 직접 호출하도록 제한합니다.
 */
private slots:
    void addContact();       // '추가/수정' 버튼 클릭에 연결될 슬롯
    void deleteContact();    // '삭제' 버튼 클릭에 연결될 슬롯
    void searchContact();    // '검색' 버튼 클릭에 연결될 슬롯
    void showContactDetails(QListWidgetItem *item); // 리스트 항목 클릭에 연결될 슬롯

/*
 * 'private:' 섹션
 * 클래스 외부에서는 접근할 수 없는 내부 데이터와 함수들을 정의합니다.
 * 이는 객체의 상태를 안전하게 보호하기 위함입니다 (캡슐화).
 */
private:
    // 멤버 함수
    void setupUI(); // UI 요소들을 생성하고 배치하는 내부 헬퍼 함수
    void refreshContactList(); // 주소록 리스트 위젯을 새로 고치는 함수
    void refreshContactList(const std::vector<Contact>& contacts); // 검색 결과를 리스트에 표시하는 함수

    // 데이터 멤버
    AddressBook addressBook; // 주소록 데이터를 실제로 관리하는 객체

    /*
     * UI 요소들을 가리키는 포인터 변수들입니다.
     * 헤더 파일에서는 '이러한 위젯을 가리킬 포인터가 있다'고 선언만 하고,
     * 실제 위젯 생성(메모리 할당)은 .cpp 파일의 생성자에서 'new' 키워드를 통해 이루어집니다.
     * 포인터(*)를 사용하는 이유는 위젯 객체들이 동적으로 생성되고, Qt의 부모-자식 관계에 의해
     * 메모리 관리가 자동으로 이루어지기 때문입니다.
     */
    QListWidget *contactListWidget;
    QLineEdit *nameInput;
    QLineEdit *phoneInput;
    QLineEdit *emailInput;
    QLineEdit *addressInput;
    QLineEdit *searchInput;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *searchButton;
};

#endif // MAINWINDOW_H 