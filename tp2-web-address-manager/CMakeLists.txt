# 1. CMake 최소 버전 설정
cmake_minimum_required(VERSION 3.10)

# 2. 프로젝트 이름 설정
project(Web_AddressBook_Server)

# 3. C++ 표준 버전 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------- vcpkg 및 외부 라이브러리 설정 -----------------
# find_package는 vcpkg 툴체인에 의해 지정된 경로에서 라이브러리를 찾습니다.
find_package(crow REQUIRED)  # 소문자 'crow'가 정확한 패키지명
find_package(nlohmann_json CONFIG REQUIRED)
# -------------------------------------------------------------------

# 4. 실행 파일 생성 위치 설정
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

# ----------------- 라이브러리 링크 설정 (수정) -----------------
# find_package가 성공하면 Crow::Crow 와 같은 IMPORTED 타겟이 생성됩니다.
# 이 타겟을 사용해 라이브러리를 연결합니다.
target_link_libraries(address_manager PUBLIC 
    Crow::Crow  # 실제 타겟명은 'Crow::Crow'
    nlohmann_json::nlohmann_json
)
# ------------------------------------------------------------