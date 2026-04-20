#include <iostream>
#include "../include/orm/core/db.hpp"
#include "../models/user.hpp"
#include "../include/orm/repository/repository.hpp"
#include "../include/orm/model/dynamic_model.hpp"
#include "../include/orm/repository/dynamic_repository.hpp"
#include "../include/orm/query/query_builder.hpp"

int main() {
    DB db;

    if (!db.connect("test.db")) return 1;

    // reset table
    db.execute("DROP TABLE IF EXISTS users;");
    // db.execute("CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT);");
    db.execute("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);");

    Repository<User> repo(db);

    repo.save(User(1, "Aryan"));
    repo.save(User(2, "Singh"));

    auto users = repo.findAll();

    for (auto& u : users) {
        std::cout << u.id << " " << u.name << "\n";
    }
    auto filtered = repo.where("name = 'Aryan'");

    for (auto& u : filtered) {
        std::cout << "Filtered: " << u.id << " " << u.name << "\n";
    }
    repo.update(User(1, "UpdatedName"), "id = 1");

    users = repo.findAll();

    for (auto& u : users) {
        std::cout << u.id << " " << u.name << "\n";
    }
    repo.remove("id = 2");
    users = repo.findAll();

    for (auto& u : users) {
        std::cout << u.id << " " << u.name << "\n";
    }
    std::vector<std::pair<std::string, std::string>> cols = {

        {"rollno", "INTEGER PRIMARY KEY"},
        {"name", "TEXT"},
        {"age", "INTEGER"}
    };

    db.execute(QueryBuilder::buildCreateTable("students", cols));

    // Create dynamic repo
    DynamicRepository repody(db);

    // Create dynamic model
    DynamicModel student("students");

    student.set("rollno", "12");
    student.set("name", "sin");
    student.set("age", "34");

    // Save
    repody.save(student);
    auto students = repody.findAll("students");

    for (auto& s : students) {
        std::cout << s.get("rollno") << " "
                << s.get("name") << " "
                << s.get("age") << "\n";
    }

        // Fetch
        

    return 0;
}