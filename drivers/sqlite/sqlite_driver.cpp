#include "sqlite_driver.hpp"
#include <iostream>

SQLiteDriver::SQLiteDriver() : db(nullptr) {}

SQLiteDriver::~SQLiteDriver() {
    if (db) sqlite3_close(db);
}

bool SQLiteDriver::connect(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &db) == 0) {
        std::cout << "Connected to DB\n";
        return true;
    }
    std::cout << "Failed to connect\n";
    return false;
}

bool SQLiteDriver::execute(const std::string& query) {
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
        return false;
    }

    std::cout << "Query executed successfully\n";
    return true;
}

static int callback(void* data, int argc, char** argv, char** colNames) {
    Result* result = static_cast<Result*>(data);

    Row row;
    for (int i = 0; i < argc; i++) {
        row[colNames[i]] = (argv[i] ? argv[i] : "NULL");
    }

    result->push_back(row);
    return 0;
}

bool SQLiteDriver::executeQuery(const std::string& query, Result& result) {
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), callback, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}