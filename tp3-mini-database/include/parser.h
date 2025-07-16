#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "database.h"

// SQL 명령 유형
enum class SqlCommandType {
    CREATE_TABLE,
    INSERT,
    SELECT,
    UPDATE,
    DELETE,
    DROP_TABLE,
    UNKNOWN
};

// SQL 명령 구조체
struct SqlCommand {
    SqlCommandType type;
    std::string tableName;
    std::vector<std::string> columnNames;
    std::vector<std::string> values;
    std::string whereColumn;
    std::string whereValue;
    std::string setColumn;
    std::string setValue;
};

class Parser {
public:
    Parser();
    ~Parser();
    
    // SQL 문자열 파싱
    SqlCommand parse(const std::string& sqlString);
    
    // 명령 실행
    bool executeCommand(Database& db, const SqlCommand& command);
    
private:
    // 문자열을 토큰으로 분리
    std::vector<std::string> tokenize(const std::string& sqlString);
    
    // CREATE TABLE 명령 파싱
    SqlCommand parseCreateTable(const std::vector<std::string>& tokens);
    
    // INSERT 명령 파싱
    SqlCommand parseInsert(const std::vector<std::string>& tokens);
    
    // SELECT 명령 파싱
    SqlCommand parseSelect(const std::vector<std::string>& tokens);
    
    // UPDATE 명령 파싱
    SqlCommand parseUpdate(const std::vector<std::string>& tokens);
    
    // DELETE 명령 파싱
    SqlCommand parseDelete(const std::vector<std::string>& tokens);
};

#endif // PARSER_H