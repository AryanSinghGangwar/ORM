#pragma once
#include "../core/db.hpp"
#include "../query/query_builder.hpp"
#include "../model/dynamic_model.hpp"
#include <vector>

class DynamicRepository {
private:
    DB& db;

public:
    DynamicRepository(DB& db) : db(db) {}

    void save(const DynamicModel& obj) {
        auto data = obj.toMap();

        std::string query = QueryBuilder::buildInsert(
            obj.tableName(), data
        );

        db.execute(query);
    }

    std::vector<DynamicModel> findAll(const std::string& table) {
        Result result;

        std::string query = QueryBuilder::buildSelect(table);

        db.query(query, result);

        std::vector<DynamicModel> objects;

        for (auto& row : result) {
            objects.emplace_back(table, row);
        }

            return objects;
    }
};