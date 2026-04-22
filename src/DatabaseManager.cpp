#include "../include/DatabaseManager.hpp"

DatabaseManager::DatabaseManager(string path) {
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        cout << "!!! Erro ao abrir o banco: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << ">>> Banco conectado localmente." << endl;
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
}

bool DatabaseManager::executarSQL(string sql) {
    char* zErrMsg = 0;
    if (sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg) != SQLITE_OK) {
        cerr << "SQL Error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

void DatabaseManager::initDatabase() {
    // Script para criar as tabelas
    string sql = 
        "CREATE TABLE IF NOT EXISTS participantes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome TEXT NOT NULL,"
        "email TEXT NOT NULL,"
        "curso TEXT);"

        "CREATE TABLE IF NOT EXISTS atividades ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "titulo TEXT NOT NULL,"
        "data TEXT NOT NULL,"
        "capacidade INTEGER NOT NULL,"
        "tipo TEXT NOT NULL);"

        "CREATE TABLE IF NOT EXISTS inscricoes ("
        "id_participante INTEGER,"
        "id_atividade INTEGER,"
        "FOREIGN KEY(id_participante) REFERENCES participantes(id),"
        "FOREIGN KEY(id_atividade) REFERENCES atividades(id));";

    if (executarSQL(sql)) {
        cout << ">>> Tabelas verificadas/criadas com sucesso!" << endl;
    }
}