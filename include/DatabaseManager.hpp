#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "sqlite3.h"
#include <string>
#include <iostream>

using namespace std;

class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager(string path);
    ~DatabaseManager();

    bool executarSQL(string sql);
    
    // Cria as tabelas iniciais se elas não existirem
    void initDatabase(); 
};

#endif