#pragma once
#include <string>
#include <map>

class Model {
public:
    virtual std::string tableName() const = 0;
    virtual std::map<std::string, std::string> toMap() const = 0;
    virtual ~Model() {}
};