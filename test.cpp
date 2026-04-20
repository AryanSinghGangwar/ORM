#include <sqlite3.h>
#include <iostream>
using namespace std;


int main() {
    sqlite3* db;
    if (sqlite3_open("test.db", &db) == 0) {
        cout << "DB connected\n";
    } else {
        cout << "DB failed\n";
    }
    sqlite3_close(db);
}