# M1 MacBook C++ 개발 환경 설정 가이드

## 🎯 개요
이 프로젝트는 M1 MacBook에서 C++ 개발 환경을 설정하고 테스트하는 가이드입니다.

## ✅ 현재 설정된 환경

### 기본 도구들
- **컴파일러**: Apple Clang 16.0.0 (gcc/g++)
- **빌드 도구**: make, cmake
- **아키텍처**: ARM64 (Apple Silicon 최적화)

### 설치된 도구들
```bash
# 확인된 도구들
gcc --version          # Apple Clang 16.0.0
g++ --version          # Apple Clang 16.0.0  
make --version         # GNU Make
cmake --version        # CMake 4.0.3
```

## 🚀 빠른 시작

### 1. 기본 컴파일
```bash
# 단일 파일 컴파일
g++ -std=c++17 -o program source.cpp

# 실행
./program
```

### 2. Makefile 사용
```bash
# 모든 프로그램 빌드
make all

# 빌드 후 테스트 실행
make test

# 정리
make clean

# 도움말
make help
```

### 3. CMake 사용
```bash
# 빌드 디렉토리 생성
mkdir build && cd build

# CMake 설정
cmake ..

# 빌드
make

# 실행
./cmake_test
```

## 📁 프로젝트 구조
```
roboticsEng_toyProject/
├── test.cpp              # 기본 C++ 테스트
├── advanced_test.cpp     # 고급 C++ 기능 테스트
├── CMakeLists.txt        # CMake 설정
├── Makefile             # Make 빌드 스크립트
└── build/               # CMake 빌드 디렉토리
```

## 🔧 컴파일러 옵션

### 기본 옵션
```bash
g++ -std=c++17 -Wall -Wextra -O2 source.cpp -o program
```

### 멀티스레딩 지원
```bash
g++ -std=c++17 -pthread source.cpp -o program
```

### 디버그 정보 포함
```bash
g++ -std=c++17 -g -Wall source.cpp -o program
```

## 🧪 테스트된 기능들

### ✅ 기본 기능
- C++17 표준 지원
- STL 컨테이너 (vector, string 등)
- 템플릿 함수
- 클래스와 객체

### ✅ Modern C++ 기능
- 람다 함수
- 스마트 포인터 (unique_ptr)
- auto 키워드
- 범위 기반 for 루프
- std::function

### ✅ 고급 기능
- 멀티스레딩 (std::thread)
- 시간 측정 (chrono)
- 알고리즘 (sort, for_each 등)

## 🛠️ 추가 설정 (선택사항)

### 1. 추가 라이브러리 설치
```bash
# Boost 라이브러리
brew install boost

# OpenMP (병렬 처리)
brew install libomp

# Eigen (수치 계산)
brew install eigen
```

### 2. IDE 설정
- **Xcode**: Apple의 공식 IDE
- **CLion**: JetBrains의 C++ IDE
- **VS Code**: 확장 프로그램 설치
  - C/C++ Extension
  - CMake Tools
  - C++ TestMate

### 3. 디버거 설정
```bash
# LLDB 사용 (기본 설치됨)
lldb ./program

# GDB 설치 (선택사항)
brew install gdb
```

## 📊 성능 정보

### M1 MacBook 최적화
- ARM64 아키텍처에 최적화된 컴파일러
- Apple Silicon 전용 최적화
- 네이티브 성능으로 실행

### 컴파일 시간
- 기본 프로그램: ~0.1초
- 복잡한 프로젝트: ~1-5초

## 🐛 문제 해결

### 일반적인 문제들

1. **컴파일러를 찾을 수 없음**
   ```bash
   # Xcode Command Line Tools 설치
   xcode-select --install
   ```

2. **헤더 파일을 찾을 수 없음**
   ```bash
   # 시스템 헤더 경로 확인
   g++ -v -E -x c++ /dev/null
   ```

3. **라이브러리 링크 오류**
   ```bash
   # pkg-config로 라이브러리 경로 확인
   pkg-config --cflags --libs library_name
   ```

## 📚 추가 리소스

### 학습 자료
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [cppreference.com](https://en.cppreference.com/)
- [Modern C++ Tutorial](https://github.com/changkun/modern-cpp-tutorial)

### 도구들
- [Clang Format](https://clang.llvm.org/docs/ClangFormat.html) - 코드 포맷팅
- [Clang Tidy](https://clang.llvm.org/extra/clang-tidy/) - 정적 분석
- [Valgrind](https://valgrind.org/) - 메모리 디버깅

## 🎉 결론

M1 MacBook에서 C++ 개발 환경이 완벽하게 설정되었습니다! 

**주요 특징:**
- ✅ Apple Silicon 최적화
- ✅ C++17 표준 완전 지원
- ✅ Modern C++ 기능 모두 사용 가능
- ✅ 멀티스레딩 지원
- ✅ CMake 빌드 시스템
- ✅ 빠른 컴파일 속도

이제 C++ 프로젝트를 자유롭게 개발하실 수 있습니다! 🚀
