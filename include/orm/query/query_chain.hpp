#pragma once
#include <string>
#include <vector>
#include "../core/db.hpp"
#include "../model/dynamic_model.hpp"

class QueryChain {
private:
    DB& db;
    std::string tableName_;
    std::string whereClause;
    std::string orderClause;
    std::string limitClause;

public:
    QueryChain(DB& database) : db(database) {}

    QueryChain& table(const std::string& name) {
        tableName_ = name;
        return *this;
    }

    QueryChain& where(const std::string& condition) {
        whereClause = " WHERE " + condition;
        return *this;
    }

    QueryChain& orderBy(const std::string& col) {
        orderClause = " ORDER BY " + col;
        return *this;
    }

    QueryChain& limit(int n) {
        limitClause = " LIMIT " + std::to_string(n);
        return *this;
    }

    std::vector<DynamicModel> get() {
        Result result;

        std::string query = "SELECT * FROM " + tableName_
                          + whereClause
                          + orderClause
                          + limitClause + ";";

        db.query(query, result);

        std::vector<DynamicModel> objects;

        for (auto& row : result) {
            objects.emplace_back(tableName_, row);
        }

        return objects;
    }
};