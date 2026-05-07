#include "../include/DatabaseManager.hpp"
#include "../include/Atividade.hpp"
#include "../include/Participante.hpp"
#include "../include/Workshop.hpp"
#include "../include/Hackathon.hpp"
#include "../include/Palestra.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    cout << endl;
    return 0;
}

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
        "tipo TEXT NOT NULL,"
        "descricao_extra TEXT);" 

        "CREATE TABLE IF NOT EXISTS inscricoes ("
        "id_participante INTEGER,"
        "id_atividade INTEGER,"
        "FOREIGN KEY(id_participante) REFERENCES participantes(id),"
        "FOREIGN KEY(id_atividade) REFERENCES atividades(id));";

    if (executarSQL(sql)) {
        cout << ">>> Tabelas verificadas/criadas com sucesso!" << endl;
    }
}

void DatabaseManager::listarParticipantes() {
    string sql = "SELECT * FROM participantes;";
    char* zErrMsg = 0;
    cout << "\n--- LISTA DE PARTICIPANTES NO BANCO ---" << endl;
    if (sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg) != SQLITE_OK) {
        cerr << "Erro ao listar: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }
    cout << "---------------------------------------" << endl;
}

bool DatabaseManager::salvarParticipante(Participante* p) { 
    string sql = "INSERT INTO participantes (nome, email, curso) VALUES ('" 
                 + p->getNome() + "', '" 
                 + p->getEmail() + "', '"
                 + p->getCurso() + "');";
    return executarSQL(sql);
}

bool DatabaseManager::salvarAtividade(Atividade* a) {
    string sql = "INSERT INTO atividades (titulo, data, capacidade, tipo, descricao_extra) VALUES ('" 
                 + a->getTitulo() + "', '" 
                 + a->getData() + "', " 
                 + to_string(a->getCapacidade()) + ", '" 
                 + a->getTipo() + "', '"
                 + a->getDescricaoExtra() + "');"; 
    return executarSQL(sql);
}

std::vector<Atividade*> DatabaseManager::listarAtividades() {
    std::vector<Atividade*> lista;
    string sql = "SELECT * FROM atividades;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << endl;
        return lista;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        
        int id = sqlite3_column_int(stmt, 0); 
        string titulo = (const char*)sqlite3_column_text(stmt, 1);
        string data = (const char*)sqlite3_column_text(stmt, 2);
        int capacidade = sqlite3_column_int(stmt, 3);
        string tipo = (const char*)sqlite3_column_text(stmt, 4);
        string descExtra = (const char*)sqlite3_column_text(stmt, 5);

        Atividade* a = nullptr;
        
        if (tipo == "Workshop") {
        a = new Workshop(titulo, data, capacidade, descExtra, "");
        } else if (tipo == "Hackathon") {
            a = new Hackathon(titulo, data, capacidade, descExtra, 0, "");
        } else if (tipo == "Palestra") {
            a = new Palestra(titulo, data, capacidade, descExtra, "");
        }

        if (a) {
            a->setId(id); 
            a->setDescricao(descExtra);
            lista.push_back(a);
        }
    }

    sqlite3_finalize(stmt);
    return lista;
}

bool DatabaseManager::inscreverParticipante(int idParticipante, int idAtividade) {
    string sql = "INSERT INTO inscricoes (id_participante, id_atividade) VALUES (" 
                 + to_string(idParticipante) + ", " 
                 + to_string(idAtividade) + ");";
    if (executarSQL(sql)) {
        cout << ">>> Vinculo salvo no banco de dados!" << endl;
        return true;
    }
    return false;
}

bool DatabaseManager::atualizarCapacidade(int id, int novaCap) {
    string sql = "UPDATE atividades SET capacidade = " + to_string(novaCap) + 
                 " WHERE id = " + to_string(id) + ";";
    if (executarSQL(sql)) {
        cout << ">>> Capacidade da oportunidade " << id << " atualizada!" << endl;
        return true;
    }
    return false;
}

bool DatabaseManager::excluirAtividade(int id) {
    string sql = "DELETE FROM atividades WHERE id = " + to_string(id) + ";";
    if (executarSQL(sql)) {
        cout << ">>> Oportunidade " << id << " removida do sistema." << endl;
        return true;
    }
    return false;
}