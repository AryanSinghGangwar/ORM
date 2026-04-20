# AtlasORM — Custom C++ ORM Engine

AtlasORM is a lightweight Object Relational Mapping (ORM) engine built from scratch in C++ using SQLite.

The goal of this project was to understand how ORMs work internally by implementing the core components manually — from query execution to object mapping and abstraction layers.

---

## Overview

AtlasORM provides a structured way to interact with a relational database without writing raw SQL in application code.

It includes:

- A database layer for managing SQLite connections  
- A model system for mapping objects to key-value data  
- A query builder for generating SQL dynamically  
- A repository layer to abstract database operations  
- A dynamic ORM for runtime-defined schemas  
- A fluent query API for building queries in a chainable format  

---

## Architecture

Model → Repository → QueryBuilder → DB → SQLite

Each layer has a clear responsibility:

- Model: Represents data structure  
- Repository: Handles operations like insert, update, delete  
- QueryBuilder: Generates SQL queries  
- DB: Executes queries  
- SQLite: Stores data  

---

##Features

#Static ORM
Type-based models using templates.
Example: Repository<User> repo(db); repo.save(User(1, "Aryan"));

#CRUD Operations
Supports insert, update, delete, and fetch.
Example: repo.save(User(1, "Aryan")); repo.update(User(1, "UpdatedName"), "id = 1"); repo.remove("id = 2"); auto users = repo.findAll();

#WHERE Queries
Supports filtering using conditions.
Example: auto filtered = repo.where("name = 'Aryan'");

#Dynamic ORM (Runtime Schema)
No predefined model required.
Example: DynamicModel student("students"); student.set("rollno", "12"); student.set("name", "Aryan"); student.set("age", "20");

#Dynamic Table Creation
Tables can be created at runtime.
Example: vector<pair<string, string>> cols = { {"rollno", "INTEGER PRIMARY KEY"}, {"name", "TEXT"}, {"age", "INTEGER"} }; db.execute(QueryBuilder::buildCreateTable("students", cols));

#Fluent Query API
Supports chainable queries.
Example: auto results = dynamicRepo.query().table("students").where("age > 20").orderBy("name").limit(10).get();

##Example Output

1 Aryan
2 Singh

Filtered:
1 Aryan

#After Update:
1 UpdatedName

#After Delete:
1 UpdatedName

#Dynamic:
12 Aryan 20

##Build and Run

#Requirements
C++17 or higher
SQLite3
g++ (MinGW / MSYS2 recommended)

##Compile
g++ examples/basic_usage.cpp drivers/sqlite/sqlite_driver.cpp -Iinclude -Idrivers/sqlite -lsqlite3 -o run.exe

##Run
./run.exe

##Project Structure

include/orm/core
include/orm/model
include/orm/query
include/orm/repository

drivers/sqlite
models
examples

##What I Learned

Designing layered architecture in C++
Mapping objects to relational data
Building abstractions over low-level database APIs
Handling both static and dynamic schema systems
Structuring a project beyond isolated functions

##Limitations

No relationship handling (joins)
No prepared statements yet
Basic error handling

##Author
Aryan Singh
