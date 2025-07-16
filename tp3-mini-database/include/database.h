#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>
#include <memory>
#include "table.h"

class Database {
private:
    std::string name;
    std::unordered_map<std::string, std::unique_ptr<Table>> tables;

public:
    Database(const std::string& name);
    ~Database();

    // 테이블 생성
    bool createTable(const std::string& tableName, const std::vector<std::string>& columnNames);
    
    // 테이블 가져오기
    Table* getTable(const std::string& tableName);
    
    // 테이블 삭제
    bool dropTable(const std::string& tableName);
    
    // 데이터베이스 이름 가져오기
    std::string getName() const;
    
    // 테이블 목록 가져오기
    std::vector<std::string> getTableNames() const;
};

#endif // DATABASE_H