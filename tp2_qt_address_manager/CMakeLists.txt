# 1. CMake 최소 버전 설정
cmake_minimum_required(VERSION 3.10)

# 2. 프로젝트 이름 설정
project(QT_AddressBook)

# 3. C++ 표준 버전 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 관련 설정 추가
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt6 패키지 찾기
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

# 실행 파일 생성 위치 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# 소스 파일 목록을 각 폴더에서 가져옵니다.
file(GLOB CPP_SOURCES "src/*.cpp")
file(GLOB H_SOURCES "include/*.h")

# 실행 파일 생성
add_executable(address_manager ${CPP_SOURCES} ${H_SOURCES})

# 헤더 파일 검색 경로에 'include' 폴더를 추가
target_include_directories(address_manager PUBLIC "include")

# Qt6 라이브러리 링크
target_link_libraries(address_manager PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)