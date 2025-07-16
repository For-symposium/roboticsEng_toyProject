# 미니 데이터베이스 프로젝트

C++로 구현한 간단한 인메모리 데이터베이스 시스템입니다.

## 기능
- 테이블 생성 및 관리
- 데이터 삽입/조회/수정/삭제
- 간단한 SQL 파서

## 빌드 방법
```bash
mkdir build
cd build
cmake ..
make
```

## 실행 방법
```bash
./minidb
```

## 사용 예시
SQL> CREATE TABLE users (id, name, email)
SQL> INSERT INTO users VALUES (1, "John", "john@example.com")
SQL> SELECT * FROM users
SQL> UPDATE users SET name = "John Doe" WHERE id = 1
SQL> DELETE FROM users WHERE id = 1

```