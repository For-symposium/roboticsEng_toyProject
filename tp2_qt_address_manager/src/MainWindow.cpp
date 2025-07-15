#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QDebug>

// MainWindow의 생성자: MainWindow 객체가 처음 생성될 때 단 한 번 호출됩니다.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) { // 부모 클래스(QMainWindow)의 생성자를 호출합니다.
    
    // 1. UI를 초기화하고 위젯들을 배치합니다.
    setupUI();

    // 2. 시그널-슬롯 연결: 사용자의 행동(시그널)과 처리할 함수(슬롯)를 짝지어줍니다.
    // '추가' 버튼이 클릭되면(clicked 시그널), addContact 함수(슬롯)를 실행합니다.
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addContact);
    // '삭제' 버튼이 클릭되면, deleteContact 함수를 실행합니다.
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteContact);
    // '검색' 버튼이 클릭되면, searchContact 함수를 실행합니다.
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::searchContact);
    // 연락처 목록의 항목이 클릭되면, showContactDetails 함수를 실행합니다.
    connect(contactListWidget, &QListWidget::itemClicked, this, &MainWindow::showContactDetails);
    
    // 3. 프로그램 시작 시 주소록 목록을 화면에 표시합니다.
    refreshContactList();
}

// 소멸자: 객체가 메모리에서 해제될 때 호출됩니다.
MainWindow::~MainWindow() {
    // Qt는 부모-자식 관계에 따라 위젯들의 메모리를 자동으로 관리해주므로,
    // 여기서 'delete'를 일일이 호출할 필요가 없습니다.
}

// UI를 설정하는 헬퍼 함수입니다. 생성자에서 호출됩니다.
void MainWindow::setupUI() {
    // 윈도우의 제목을 설정합니다.
    setWindowTitle("Address Book");
    
    // 중앙 위젯과 메인 레이아웃을 생성합니다.
    // 모든 UI 요소들은 중앙 위젯 위에 배치되고, 레이아웃이 그 배치를 관리합니다.
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget); // 수평 레이아웃

    // 왼쪽 영역: 검색창과 연락처 목록
    QVBoxLayout *leftLayout = new QVBoxLayout(); // 수직 레이아웃
    
    QGroupBox *searchGroup = new QGroupBox("Search Contact"); // 검색 부분을 그룹으로 묶습니다.
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchInput = new QLineEdit();
    searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);
    searchGroup->setLayout(searchLayout);

    contactListWidget = new QListWidget();
    deleteButton = new QPushButton("Delete Selected");
    
    leftLayout->addWidget(searchGroup);
    leftLayout->addWidget(contactListWidget);
    leftLayout->addWidget(deleteButton);

    // 오른쪽 영역: 연락처 상세 정보 입력 폼
    QGroupBox *formGroup = new QGroupBox("Contact Details");
    QFormLayout *formLayout = new QFormLayout(); // '레이블: 입력창' 형태의 폼에 최적화된 레이아웃
    nameInput = new QLineEdit();
    phoneInput = new QLineEdit();
    emailInput = new QLineEdit();
    addressInput = new QLineEdit();
    addButton = new QPushButton("Add/Update Contact");

    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("Phone:", phoneInput);
    formLayout->addRow("Email:", emailInput);
    formLayout->addRow("Address:", addressInput);
    formLayout->addWidget(addButton);
    formGroup->setLayout(formLayout);

    // 메인 레이아웃에 왼쪽과 오른쪽 영역을 추가합니다. (1:2 비율로 공간 할당)
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addWidget(formGroup, 2);

    // 완성된 중앙 위젯을 메인 윈도우에 설정합니다.
    setCentralWidget(centralWidget);
}

// 주소록의 모든 연락처를 목록에 표시하기 위한 함수입니다.
void MainWindow::refreshContactList() {
    // getContacts()로 모든 연락처를 가져와서, 다른 버전의 refreshContactList에 넘겨줍니다.
    refreshContactList(addressBook.getContacts());
}

// 주어진 연락처 목록(검색 결과 등)을 화면에 새로 고쳐주는 함수입니다.
void MainWindow::refreshContactList(const std::vector<Contact>& contacts) {
    contactListWidget->clear(); // 목록을 새로 채우기 전에 기존 내용을 모두 지웁니다.
    for (const auto& contact : contacts) {
        // 리스트 위젯에 표시할 새 항목을 생성합니다.
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(contact.getName()), contactListWidget);
        // 나중에 항목을 클릭했을 때 이름을 쉽게 가져올 수 있도록 데이터를 저장해둡니다.
        item->setData(Qt::UserRole, QVariant::fromValue(QString::fromStdString(contact.getName())));
    }
}


// '추가/수정' 버튼에 연결된 슬롯 함수입니다.
void MainWindow::addContact() {
    // 1. 입력창(QLineEdit)에서 사용자가 입력한 텍스트를 가져옵니다.
    std::string name = nameInput->text().toStdString();
    std::string phone = phoneInput->text().toStdString();
    std::string email = emailInput->text().toStdString();
    std::string address = addressInput->text().toStdString();

    // 이름이 비어있으면 경고 메시지를 띄우고 함수를 종료합니다.
    if (name.empty()) {
        QMessageBox::warning(this, "Input Error", "Name cannot be empty.");
        return;
    }

    // 2. 입력된 이름으로 기존 연락처가 있는지 확인합니다.
    Contact* contactToEdit = addressBook.findContactToEdit(name);
    if (contactToEdit != nullptr) {
        // 3a. 이미 존재하면, 해당 연락처의 정보를 수정합니다.
        contactToEdit->setPhone(phone);
        contactToEdit->setEmail(email);
        contactToEdit->setAddress(address);
    } else {
        // 3b. 존재하지 않으면, 새로운 Contact 객체를 만들어 주소록에 추가합니다.
        addressBook.addContact(Contact(name, phone, email, address));
    }

    // 4. 변경된 내용을 화면 목록에 반영합니다.
    refreshContactList();
    
    // 5. 다음 입력을 위해 입력창들을 깨끗이 비웁니다.
    nameInput->clear();
    phoneInput->clear();
    emailInput->clear();
    addressInput->clear();
}

// '삭제' 버튼에 연결된 슬롯 함수입니다.
void MainWindow::deleteContact() {
    // 현재 목록에서 선택된 항목을 가져옵니다.
    QListWidgetItem *selectedItem = contactListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Selection Error", "Please select a contact to delete.");
        return;
    }

    // 선택된 항목의 이름을 가져와서 주소록에서 삭제합니다.
    std::string name = selectedItem->text().toStdString();
    addressBook.deleteContactByName(name);
    
    // 변경 내용을 화면에 반영합니다.
    refreshContactList();
}

// '검색' 버튼에 연결된 슬롯 함수입니다.
void MainWindow::searchContact() {
    std::string searchText = searchInput->text().toStdString();
    if (searchText.empty()) {
        // 검색어가 없으면 전체 목록을 보여줍니다.
        refreshContactList();
        return;
    }

    // 검색어를 포함하는 연락처를 찾아서 그 결과만 목록에 표시합니다.
    auto results = addressBook.findContactByName(searchText);
    refreshContactList(results);
}

// 목록의 항목이 클릭되었을 때 연결된 슬롯 함수입니다.
void MainWindow::showContactDetails(QListWidgetItem *item) {
    if (!item) return;

    // 클릭된 항목의 이름을 가져옵니다.
    std::string name = item->text().toStdString();
    // 해당 이름의 연락처 정보를 찾습니다.
    auto contacts = addressBook.findContactByName(name);
    
    if (!contacts.empty()) {
        // (이름이 고유하다고 가정하고) 찾은 첫 번째 연락처의 상세 정보를
        // 오른쪽 입력창들에 채워넣습니다.
        const Contact& contact = contacts[0];
        nameInput->setText(QString::fromStdString(contact.getName()));
        phoneInput->setText(QString::fromStdString(contact.getPhone()));
        emailInput->setText(QString::fromStdString(contact.getEmail()));
        addressInput->setText(QString::fromStdString(contact.getAddress()));
    }
} 