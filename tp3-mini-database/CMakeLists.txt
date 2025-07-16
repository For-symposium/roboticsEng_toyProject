cmake_minimum_required(VERSION 3.10)
project(MiniDatabase)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# 소스 파일 목록
set(SOURCES
    src/database.cpp
    src/table.cpp
    src/parser.cpp
    src/main.cpp
)

# 실행 파일 생성
add_executable(minidb ${SOURCES})