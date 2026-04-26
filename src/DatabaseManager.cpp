#include "../include/DatabaseManager.hpp"
#include "../include/Atividade.hpp"
#include "../include/Participante.hpp"

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        // Aqui eu fiz pra imprimir o nome da coluna: valor
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
        "tipo TEXT NOT NULL);"
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

// Método que usa o callback para listar os alunos
void DatabaseManager::listarParticipantes() {
    string sql = "SELECT * FROM participantes;";
    char* zErrMsg = 0;

    cout << "\n--- LISTA DE PARTICIPANTES NO BANCO ---" << endl;
    
    // Aqui eu passo o nome da função callback como argumento
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

void DatabaseManager::listarAtividades() {
    string sql = "SELECT * FROM atividades;";
    char* zErrMsg = 0;
    cout << "\n--- OPORTUNIDADES DISPONIVEIS NO CIN ---" << endl;
    sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
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