#pragma once
#include <string>
#include <vector>
#include <map>
#include <sqlite3.h>

using Row = std::map<std::string, std::string>;
using Result = std::vector<Row>;

class SQLiteDriver {
private:
    sqlite3* db;

public:
    SQLiteDriver();
    ~SQLiteDriver();

    bool connect(const std::string& db_name);
    bool execute(const std::string& query);
    bool executeQuery(const std::string& query, Result& result);
};