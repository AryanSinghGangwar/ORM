#pragma once
#include "../include/orm/model/model.hpp"

class User : public Model {
public:
    int id;
    std::string name;

    User(int id, const std::string& name) : id(id), name(name) {}

    std::string tableName() const override {
        return "users";
    }

    std::map<std::string, std::string> toMap() const override {
        return {
            {"id", std::to_string(id)},
            {"name", name}
        };
    }

    static User fromMap(const std::map<std::string, std::string>& row) {
        return User(
            std::stoi(row.at("id")),
            row.at("name")
        );
    }
};