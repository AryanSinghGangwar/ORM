#pragma once
#include <string>
#include <map>
#include <sstream>

class QueryBuilder {
public:
    static std::string buildInsert(
        const std::string& table,
        const std::map<std::string, std::string>& data
    ) {
        std::stringstream ss;

        ss << "INSERT INTO " << table << " (";

        bool first = true;
        for (auto& [k, v] : data) {
            if (!first) ss << ", ";
            ss << k;
            first = false;
        }

        ss << ") VALUES (";

        first = true;
        for (auto& [k, v] : data) {
            if (!first) ss << ", ";
            ss << "'" << v << "'";
            first = false;
        }

        ss << ");";

        return ss.str();
        }

        static std::string buildSelect(const std::string& table) {
                return "SELECT * FROM " + table + ";";
        }
        static std::string buildSelectWhere(
            const std::string& table,
            const std::string& condition){
                return "SELECT * FROM " + table + " WHERE " + condition + ";";
            }
            static std::string buildUpdate(
                const std::string& table,
                const std::map<std::string, std::string>& data,
                const std::string& condition) {
            std::stringstream ss;

                ss << "UPDATE " << table << " SET ";

                bool first = true;
                for (auto& [k, v] : data) {
                    if (!first) ss << ", ";
                    ss << k << " = '" << v << "'";
                    first = false;
                }

                ss << " WHERE " << condition << ";";

            return ss.str();
        }
        static std::string buildDelete(
            const std::string& table,
            const std::string& condition) {

                return "DELETE FROM " + table + " WHERE " + condition + ";";
        }


        static std::string buildCreateTable(
            const std::string& table,
            const std::vector<std::pair<std::string, std::string>>& columns
        ) {

            std::stringstream ss;

            ss << "CREATE TABLE IF NOT EXISTS " << table << " (";

            bool first = true;
            for (auto& [name, type] : columns) {
                if (!first) ss << ", ";
                ss << name << " " << type;
                first = false;
            }

            ss << ");";

            return ss.str();
        }
};