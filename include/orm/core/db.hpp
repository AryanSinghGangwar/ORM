#pragma once
#include <string>
#include <vector>
#include <map>
#include "sqlite_driver.hpp"

using Row = std::map<std::string, std::string>;
using Result = std::vector<Row>;

class DB {
private:
    SQLiteDriver driver;

public:
    bool connect(const std::string& db_name) {
        return driver.connect(db_name);
    }

    bool execute(const std::string& query) {
        return driver.execute(query);
    }

    bool query(const std::string& query, Result& result) {
        return driver.executeQuery(query, result);
    }
};