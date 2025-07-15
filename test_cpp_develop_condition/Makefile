# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# 소스 파일들
SOURCES = main.cpp math.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = calculator

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성 (링킹)
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "빌드 완료: $(TARGET)"

# 오브젝트 파일 생성 (컴파일)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "컴파일 완료: $@"

# 정리
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "정리 완료"

# 도움말
help:
	@echo "사용 가능한 명령어:"
	@echo "  make all     - 프로그램 빌드"
	@echo "  make clean   - 빌드 파일들 정리"
	@echo "  make help    - 이 도움말 표시"

.PHONY: all clean help 