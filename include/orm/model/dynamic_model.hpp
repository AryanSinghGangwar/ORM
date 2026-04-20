#pragma once
#include <string>
#include <map>

class DynamicModel {
private:
    std::string table;
    std::map<std::string, std::string> data;

public:
    DynamicModel(const std::string& tableName) : table(tableName) {}

    // NEW: construct from DB row
    DynamicModel(const std::string& tableName,
                 const std::map<std::string, std::string>& row)
        : table(tableName), data(row) {}

    void set(const std::string& key, const std::string& value) {
        data[key] = value;
    }

    std::string get(const std::string& key) const {
        return data.at(key);
    }

    std::string tableName() const {
        return table;
    }

    std::map<std::string, std::string> toMap() const {
        return data;
    }
};