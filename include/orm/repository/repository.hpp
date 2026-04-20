#pragma once
#include "../core/db.hpp"
#include "../query/query_builder.hpp"
#include <vector>

template <typename T>
class Repository {
private:
    DB& db;

public:
    Repository(DB& db) : db(db) {}

    void save(const T& obj) {
        auto data = obj.toMap();
        std::string query = QueryBuilder::buildInsert(obj.tableName(), data);
        db.execute(query);
    }

    std::vector<T> findAll() {
        Result result;

        std::string query = QueryBuilder::buildSelect(T(0, "").tableName());

        db.query(query, result);

        std::vector<T> objects;

        for (auto& row : result) {
            objects.push_back(T::fromMap(row));
        }

        return objects;
    }
    std::vector<T> where(const std::string& condition) {
        Result result;

        std::string query = QueryBuilder::buildSelectWhere(
        T(0, "").tableName(), condition
        );

        db.query(query, result);

        std::vector<T> objects;

        for (auto& row : result) {
            objects.push_back(T::fromMap(row));
        }

        return objects;
    }
    void update(const T& obj, const std::string& condition) {
        auto data = obj.toMap();

        std::string query = QueryBuilder::buildUpdate(
            obj.tableName(), data, condition
        );

        db.execute(query);
    }
    void remove(const std::string& condition) {
        std::string query = QueryBuilder::buildDelete(
            T(0, "").tableName(), condition
        );

        db.execute(query);
    }
};