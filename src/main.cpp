#include <iostream>
#include <string>
#include <vector>
#include "../include/DatabaseManager.hpp"
#include "../include/Participante.hpp"
#include "../include/Workshop.hpp"
#include "../include/Estagio.hpp"
#include "../include/Clube.hpp"
#include "../include/Palestra.hpp"
#include "../include/Hackathon.hpp"
#include "crow_all.h"
#include "json_helper.hpp"

using namespace std;

int main() {
    DatabaseManager dbManager("sistema.db");
    dbManager.initDatabase();

    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
      .global()
      .origin("*")
      .methods("POST"_method, "GET"_method, "OPTIONS"_method)
      .headers("Content-Type", "Authorization");


    CROW_ROUTE(app, "/api/atividades")
    ([&dbManager](){
        auto atividades = dbManager.listarAtividades(); 
        string json_output = "[";
        for (size_t i = 0; i < atividades.size(); ++i) {
            json_output += atividadeParaJSON(atividades[i]);
            if (i < atividades.size() - 1) json_output += ",";
        }
        json_output += "]";
        
        crow::response res(json_output);
        res.set_header("Content-Type", "application/json");
        

        for (auto a : atividades) delete a;
        return res;
    });


    auto cadastrar = [&](const crow::request& req, string tipo) {
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400, "JSON Invalido");

        try {
            Atividade* novo = nullptr;
            if (tipo == "Workshop") novo = new Workshop(x["titulo"].s(), x["data"].s(), x["vagas"].i(), x["materiais"].s(), x["requisitos"].s());
            else if (tipo == "Clube") novo = new Clube(x["titulo"].s(), x["data"].s(), x["vagas"].i(), x["area"].s(), x["edital"].s());
            else if (tipo == "Estagio") novo = new Estagio(x["titulo"].s(), x["data"].s(), x["vagas"].i(), x["bolsa"].d(), x["local"].s());
            else if (tipo == "Hackathon") novo = new Hackathon(x["titulo"].s(), x["data"].s(), x["vagas"].i(), x["premiacao"].s(), x["tamanho_equipe"].i());
            else if (tipo == "Palestra") novo = new Palestra(x["titulo"].s(), x["data"].s(), x["vagas"].i(), x["palestrante"].s(), x["tema"].s());

            if (novo) {
                dbManager.salvarAtividade(novo);
                delete novo;
                return crow::response(200, "OK");
            }
        } catch (...) { 
            return crow::response(500, "Erro ao processar objeto"); 
        }
        return crow::response(404);
    };


    CROW_ROUTE(app, "/api/cadastrar_workshop").methods("POST"_method)([&](const crow::request& req){ return cadastrar(req, "Workshop"); });
    CROW_ROUTE(app, "/api/cadastrar_clube").methods("POST"_method)([&](const crow::request& req){ return cadastrar(req, "Clube"); });
    CROW_ROUTE(app, "/api/cadastrar_estagio").methods("POST"_method)([&](const crow::request& req){ return cadastrar(req, "Estagio"); });
    CROW_ROUTE(app, "/api/cadastrar_hackathon").methods("POST"_method)([&](const crow::request& req){ return cadastrar(req, "Hackathon"); });
    CROW_ROUTE(app, "/api/cadastrar_palestra").methods("POST"_method)([&](const crow::request& req){ return cadastrar(req, "Palestra"); });

    int opcao;
    do {
        cout << "\n========== SISTEMA CIn-EVENTS (BACKEND) ==========" << endl;
        cout << "9. INICIAR SERVIDOR WEB" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha: ";
        
        if (!(cin >> opcao)) {
            cin.clear(); cin.ignore(1000, '\n'); opcao = -1;
        } else { cin.ignore(); }

        if (opcao == 9) {
            cout << ">>> SERVIDOR ATIVO em http://localhost:8080" << endl;
            app.port(8080).multithreaded().run();
        }
    } while (opcao != 0);

    return 0;
}