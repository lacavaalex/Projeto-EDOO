#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../include/DatabaseManager.hpp"
#include "../include/Participante.hpp"
#include "../include/Workshop.hpp"
#include "../include/Palestra.hpp"
#include "../include/Hackathon.hpp"
#include "../include/crow_all.h"
#include "json_helper.hpp"

using namespace std;

struct CORSMiddleware {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Accept, Authorization");
        res.add_header("Access-Control-Max-Age", "86400");

        if (req.method == crow::HTTPMethod::Options) {
            res.code = 204;
            res.end();
        }
    }

    void after_handle(crow::request&, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Accept, Authorization");
    }
};

int main() {
    DatabaseManager dbManager("./data/sistema.db");
    dbManager.initDatabase();

    crow::App<CORSMiddleware> app;


    CROW_ROUTE(app, "/api/auth/registrar").methods("POST"_method)
    ([](const crow::request& req){
    auto novo_user = crow::json::load(req.body);
    if (!novo_user) return crow::response(400);

    crow::json::wvalue usuarios_lista;
    ifstream i("./data/usuarios.json");
    if (i.is_open()) {
        string conteudo((istreambuf_iterator<char>(i)), istreambuf_iterator<char>());
        i.close();
        if (!conteudo.empty()) {
            auto atual = crow::json::load(conteudo);
            if (atual) usuarios_lista = std::move(atual);
        }
    }

    int size = usuarios_lista.size();
    usuarios_lista[size]["nome"] = string(novo_user["nome"].s());
    usuarios_lista[size]["email"] = string(novo_user["email"].s());
    usuarios_lista[size]["curso"] = string(novo_user["curso"].s());
    usuarios_lista[size]["senha"] = string(novo_user["senha"].s()); // SALVANDO A SENHA

    ofstream o("./data/usuarios.json");
    o << usuarios_lista.dump();
    o.close();

    return crow::response(200, "{\"status\":\"sucesso\"}");
});

    CROW_ROUTE(app, "/api/auth/login").methods("POST"_method)
    ([](const crow::request& req){
    auto login_data = crow::json::load(req.body);
    if (!login_data) return crow::response(400);

    string identificador = string(login_data["email"].s());
    string senha_digitada = string(login_data["senha"].s());

    ifstream i("./data/usuarios.json");
    if (!i.is_open()) return crow::response(401, "{\"erro\":\"Banco de usuarios offline\"}");
    
    string conteudo((istreambuf_iterator<char>(i)), istreambuf_iterator<char>());
    i.close();

    auto usuarios = crow::json::load(conteudo);
    for (auto& u : usuarios) {
        bool matchIdentificador = (u["email"].s() == identificador || u["nome"].s() == identificador);
        
        if (matchIdentificador && u["senha"].s() == senha_digitada) {
            crow::json::wvalue res;
            res["nome"] = string(u["nome"].s());
            res["email"] = string(u["email"].s());
            res["curso"] = string(u["curso"].s());
            return crow::response(200, res);
        }
    }
    return crow::response(401, "{\"erro\":\"Usuario ou senha incorretos\"}");
});

    CROW_ROUTE(app, "/api/atividades").methods("GET"_method)
    ([&dbManager](){
        crow::response res;
        auto atividades = dbManager.listarAtividades();
        string json_output = "[";
        for (size_t i = 0; i < atividades.size(); ++i) {
            json_output += atividadeParaJSON(atividades[i]);
            if (i < atividades.size() - 1) json_output += ",";
        }
        json_output += "]";
        res.body = json_output;
        res.set_header("Content-Type", "application/json");
        for (auto a : atividades) delete a;
        return res;
    });

    CROW_ROUTE(app, "/api/atualizar_atividade/<int>").methods("PUT"_method)
    ([&dbManager](const crow::request& req, int id){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400, "{\"erro\":\"JSON invalido\"}");

        // Captura os dados que vem do seu 'editando' do React
        string titulo = x.has("titulo") ? string(x["titulo"].s()) : "";
        string data = x.has("data") ? string(x["data"].s()) : "";
        int vagas = x.has("vagas") ? x["vagas"].i() : 0;
        
        // Para o resto (horario, local, etc), como eles estao na descricao_extra:
        // Voce pode montar a string aqui ou receber a 'descricao' ja formatada do React
        string desc = x.has("descricao") ? string(x["descricao"].s()) : "";

        // Precisamos de um método que atualize múltiplos campos
        if (dbManager.atualizarAtividadeCompleta(id, titulo, data, vagas, desc)) {
            return crow::response(200, "{\"status\":\"sucesso\"}");
        } else {
            return crow::response(500, "{\"erro\":\"Falha ao atualizar no banco\"}");
        }
    });

    CROW_ROUTE(app, "/api/deletar_atividade/<int>").methods("DELETE"_method)
    ([&dbManager](const crow::request&, int id){
        crow::response res;
        res.code = dbManager.excluirAtividade(id) ? 200 : 404;
        return res;
    });

    auto cadastrar = [&](const crow::request& req, string tipo) {
        crow::response res;
        auto x = crow::json::load(req.body);
        if (!x) { res.code = 400; return res; }

        try {
            string titulo = x.has("titulo") ? string(x["titulo"].s()) : "Sem Titulo";
            string data   = x.has("data")   ? string(x["data"].s())   : "Sem Data";
            string dataInicio = x.has("data_inicio") ? string(x["data_inicio"].s()) : "00/00/0000";
            string dataFim    = x.has("data_fim")    ? string(x["data_fim"].s())    : "00/00/0000";
            string horario    = x.has("horario")    ? string(x["horario"].s())    : "00:00";
            string local      = x.has("local")      ? string(x["local"].s())      : "Sem local";
            string duracao    = x.has("duracao")    ? string(x["duracao"].s())    : "00:00";
            int vagas     = x.has("vagas")  ? x["vagas"].i()          : 0;

            Atividade* novo = nullptr;

            if (tipo == "Workshop") {
                string mat  = x.has("materiais")  ? string(x["materiais"].s())  : "";
                string reqs = x.has("requisitos") ? string(x["requisitos"].s()) : "";
                novo = new Workshop(titulo, data, dataInicio, dataFim, vagas, mat, reqs, horario, local, duracao);
            } else if (tipo == "Palestra") {
                string pal = x.has("palestrante") ? string(x["palestrante"].s()) : "Convidado";
                string tem = x.has("tema") ? string(x["tema"].s()) : "Sem tema";
                novo = new Palestra(titulo, data, dataInicio, dataFim, vagas, pal, tem, horario, local, duracao);
            } else if (tipo == "Hackathon") {
                string prem = x.has("premiacao") ? string(x["premiacao"].s()) : "";
                int tam = x.has("tamanho_equipe") ? x["tamanho_equipe"].i() : 5;
                string edital = x.has("edital") ? string(x["edital"].s()) : "Sem edital";
                novo = new Hackathon(titulo, data, dataInicio, dataFim, vagas, prem, tam, edital); 
            }

            if (novo) {
                bool ok = dbManager.salvarAtividade(novo);
                delete novo;
                res.code = ok ? 200 : 500;
                return res;
            }
        } catch (const std::exception& e) {
            cout << "[ERRO C++] " << e.what() << endl;
            res.code = 500;
            return res;
        }

        res.code = 400;
        return res;
    };

    CROW_ROUTE(app, "/api/cadastrar_workshop").methods("POST"_method)  ([&](const crow::request& req){ return cadastrar(req, "Workshop");  });
    CROW_ROUTE(app, "/api/cadastrar_hackathon").methods("POST"_method) ([&](const crow::request& req){ return cadastrar(req, "Hackathon"); });
    CROW_ROUTE(app, "/api/cadastrar_palestra").methods("POST"_method)  ([&](const crow::request& req){ return cadastrar(req, "Palestra");  });

    cout << ">>> SERVIDOR ATIVO em http://localhost:8080" << endl;
    cout << ">>> Pressione Ctrl+C para encerrar." << endl;
    app.port(8080).multithreaded().run();

    return 0;
}