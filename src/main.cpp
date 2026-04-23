#include "crow_all.h"
#include "DatabaseManager.hpp"
#include "json_helper.hpp"
#include "Palestra.hpp"
#include "Hackathon.hpp"
#include <vector>

int main() {
    crow::SimpleApp app;
    
    // Inicializa o gestor do banco
    DatabaseManager dbManager("sistema.db");
    
    // Cria as tabelas
    dbManager.initDatabase();

    // Criando alguns dados reais para testar a exibição
    vector<Atividade*> listaAtividades;
    listaAtividades.push_back(new Palestra("Intro ao CIn", "22/04", 50, "Prof. Alex"));
    listaAtividades.push_back(new Hackathon("Vibe Coding", "25/04", 30, "Pizza", 5));

    CROW_ROUTE(app, "/api/atividades")([&listaAtividades](){
        string json = "[";
        for (size_t i = 0; i < listaAtividades.size(); ++i) {
            json += atividadeParaJSON(listaAtividades[i]);
            if (i < listaAtividades.size() - 1) json += ",";
        }
        json += "]";
        
        crow::response res(json);
        res.set_header("Access-Control-Allow-Origin", "*"); // Libera para o React ver
        return res;
    });

    std::cout << ">>> Servidor rodando em http://localhost:8080" << std::endl;
    app.port(8080).multithreaded().run();
}