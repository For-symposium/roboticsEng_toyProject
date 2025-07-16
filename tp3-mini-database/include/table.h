#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <unordered_map>

// 레코드를 표현하는 클래스
class Record {
private:
    std::vector<std::string> values;

public:
    Record(const std::vector<std::string>& values);
    
    std::string getValue(size_t columnIndex) const;
    void setValue(size_t columnIndex, const std::string& value);
    size_t size() const;
};

// 테이블을 표현하는 클래스
class Table {
private:
    std::string name;
    std::vector<std::string> columnNames;
    std::vector<std::unique_ptr<Record>> records;

public:
    Table(const std::string& name, const std::vector<std::string>& columnNames);
    ~Table();

    // 레코드 추가
    bool insertRecord(const std::vector<std::string>& values);
    
    // 레코드 조회 (모든 레코드)
    std::vector<Record*> selectAll() const;
    
    // 조건에 맞는 레코드 조회
    std::vector<Record*> select(size_t columnIndex, const std::string& value) const;
    
    // 레코드 업데이트
    bool update(size_t columnIndex, const std::string& value, 
                size_t targetColumnIndex, const std::string& newValue);
    
    // 레코드 삭제
    bool deleteRecords(size_t columnIndex, const std::string& value);
    
    // 테이블 이름 가져오기
    std::string getName() const;
    
    // 컬럼 이름 가져오기
    std::vector<std::string> getColumnNames() const;
    
    // 컬럼 인덱스 가져오기
    int getColumnIndex(const std::string& columnName) const;
    
    // 레코드 수 가져오기
    size_t getRecordCount() const;
};

#endif // TABLE_H