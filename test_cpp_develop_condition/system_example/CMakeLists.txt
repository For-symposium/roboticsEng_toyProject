cmake_minimum_required(VERSION 3.16)
project(MySystem VERSION 1.0.0)

# C++17 표준 사용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 컴파일러 플래그 설정
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif()

# 헤더 파일 경로 추가
include_directories(include)

# 소스 파일들 찾기
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/core/*.cpp"
    "src/ui/*.cpp"
    "src/backend/*.cpp"
)

# 테스트 파일들 찾기
file(GLOB_RECURSE TESTS "tests/*.cpp")

# 메인 실행 파일 생성
add_executable(my_system ${SOURCES})

# 테스트 실행 파일 생성
add_executable(system_tests ${TESTS})

# 외부 라이브러리 링크 (예시)
# find_package(Boost REQUIRED)
# target_link_libraries(my_system Boost::boost)

# 설치 규칙
install(TARGETS my_system
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 문서 생성 (선택사항)
# find_package(Doxygen)
# if(DOXYGEN_FOUND)
#     add_custom_target(docs
#         ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
#         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
#         COMMENT "Generating API documentation with Doxygen"
#         VERBATIM
#     )
# endif() 