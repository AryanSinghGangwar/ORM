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

    // =========================
    // 🔹 STEP 1: BASIC CRUD
    // =========================
    std::cout << "\n===== STEP 1: BASIC CRUD =====\n";

    db.execute("DROP TABLE IF EXISTS users;");
    db.execute("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);");

    Repository<User> userRepo(db);

    userRepo.save(User(1, "Aryan"));
    userRepo.save(User(2, "Singh"));

    auto users = userRepo.findAll();

    std::cout << "All Users:\n";
    for (auto& u : users) {
        std::cout << u.id << " " << u.name << "\n";
    }

    // =========================
    // 🔹 STEP 2: WHERE FILTER
    // =========================
    std::cout << "\n===== STEP 2: WHERE FILTER =====\n";

    auto filtered = userRepo.where("name = 'Aryan'");

    for (auto& u : filtered) {
        std::cout << "Filtered: " << u.id << " " << u.name << "\n";
    }

    // =========================
    // 🔹 STEP 3: UPDATE + DELETE
    // =========================
    std::cout << "\n===== STEP 3: UPDATE + DELETE =====\n";

    userRepo.update(User(1, "UpdatedName"), "id = 1");

    users = userRepo.findAll();
    std::cout << "After Update:\n";
    for (auto& u : users) {
        std::cout << u.id << " " << u.name << "\n";
    }

    userRepo.remove("id = 2");

    users = userRepo.findAll();
    std::cout << "After Delete:\n";
    for (auto& u : users) {
        std::cout << u.id << " " << u.name << "\n";
    }

    // =========================
    // 🔹 STEP 4: DYNAMIC ORM
    // =========================
    std::cout << "\n===== STEP 4: DYNAMIC ORM =====\n";

    std::vector<std::pair<std::string, std::string>> cols = {
        {"rollno", "INTEGER PRIMARY KEY"},
        {"name", "TEXT"},
        {"age", "INTEGER"}
    };

    db.execute("DROP TABLE IF EXISTS students;");
    db.execute(QueryBuilder::buildCreateTable("students", cols));

    DynamicRepository dynamicRepo(db);

    DynamicModel student("students");

    student.set("rollno", "12");
    student.set("name", "sin");
    student.set("age", "34");

    dynamicRepo.save(student);

    auto students = dynamicRepo.findAll("students");

    std::cout << "Dynamic Data:\n";
    for (auto& s : students) {
        std::cout << s.get("rollno") << " "
                  << s.get("name") << " "
                  << s.get("age") << "\n";
    }

    // =========================
    // 🔹 STEP 5: FLUENT API
    // =========================
    std::cout << "\n===== STEP 5: FLUENT QUERY API =====\n";

    auto results = dynamicRepo
                    .query()
                    .table("students")
                    .where("age > 20")
                    .orderBy("name")
                    .limit(10)
                    .get();

    for (auto& s : results) {
        std::cout << s.get("rollno") << " "
                  << s.get("name") << " "
                  << s.get("age") << "\n";
    }

    return 0;
}