# 1. CMake 최소 버전 설정
cmake_minimum_required(VERSION 3.10)

# 2. 프로젝트 이름 설정
project(Web_AddressBook)

# 3. C++ 표준 버전 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 실행 파일 생성 위치 설정 (이 줄 추가!)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# src 폴더 안의 모든 .cpp 파일을 찾아서 SOURCES 변수에 저장
# 5. 실행 파일 생성 설정
# add_executable(address_manager 
#     src/main.cpp 
#     src/Contact.cpp 
#     src/AddressBook.cpp
# )
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 실행 파일 생성 설정
add_executable(address_manager ${SOURCES})

# 헤더 파일 검색 경로에 'include' 폴더를 추가
target_include_directories(address_manager PUBLIC include)