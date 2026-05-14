#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "sqlite3.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Participante;
class Atividade;

class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager(string path);
    ~DatabaseManager();

    bool executarSQL(string sql);
    
    // Cria as tabelas iniciais se elas não existirem
    void initDatabase(); 

    bool salvarParticipante(Participante* p);

    bool salvarAtividade(Atividade* a);

    bool atualizarAtividadeCompleta(int id, string titulo, string data, int vagas, string desc);
    
    bool inscreverParticipante(int idParticipante, int idAtividade);

    void listarParticipantes();
    std::vector<Atividade*> listarAtividades();

    bool atualizarCapacidade(int id, int novaCap); // update
    bool excluirAtividade(int id);                // delete
};

#endif