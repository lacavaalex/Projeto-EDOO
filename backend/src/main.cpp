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
        // Lendo o arquivo inteiro para uma string
        string conteudo((istreambuf_iterator<char>(i)), istreambuf_iterator<char>());
        i.close();

        if (!conteudo.empty()) {
            auto atual = crow::json::load(conteudo);
            if (atual) {
                usuarios_lista = std::move(atual);
            } else {
                usuarios_lista = crow::json::wvalue::list();
            }
        } else {
            usuarios_lista = crow::json::wvalue::list();
        }
    } else {
        usuarios_lista = crow::json::wvalue::list();
    }

    int size = usuarios_lista.size();
    usuarios_lista[size]["nome"] = string(novo_user["nome"].s());
    usuarios_lista[size]["email"] = string(novo_user["email"].s());
    usuarios_lista[size]["curso"] = string(novo_user["curso"].s());

    ofstream o("./data/usuarios.json");
    o << usuarios_lista.dump();
    o.close();

    return crow::response(200, "{\"status\":\"sucesso\"}");
});

    CROW_ROUTE(app, "/api/auth/login").methods("POST"_method)
([](const crow::request& req){
    auto login_data = crow::json::load(req.body);
    if (!login_data) return crow::response(400);

    ifstream i("./data/usuarios.json");
    if (!i.is_open()) return crow::response(401, "{\"erro\":\"Arquivo nao encontrado\"}");

    string conteudo((istreambuf_iterator<char>(i)), istreambuf_iterator<char>());
    i.close();

    if (conteudo.empty()) return crow::response(401, "{\"erro\":\"Nenhum usuario cadastrado\"}");

    auto usuarios = crow::json::load(conteudo);
    for (auto& u : usuarios) {
        if (u["email"].s() == login_data["email"].s()) {
            crow::json::wvalue res;
            res["nome"] = string(u["nome"].s());
            res["email"] = string(u["email"].s());
            res["curso"] = string(u["curso"].s());
            return crow::response(200, res);
        }
    }
    return crow::response(401, "{\"erro\":\"Usuario nao encontrado\"}");
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
        crow::response res;
        auto x = crow::json::load(req.body);
        if (!x || !x.has("vagas")) { res.code = 400; return res; }
        if (dbManager.atualizarCapacidade(id, x["vagas"].i())) {
            res.code = 200;
            res.body = "{\"ok\":true}";
        } else {
            res.code = 500;
        }
        return res;
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
            int vagas     = x.has("vagas")  ? x["vagas"].i()          : 0;

            Atividade* novo = nullptr;

            if (tipo == "Workshop") {
                string mat  = x.has("materiais")  ? string(x["materiais"].s())  : "";
                string reqs = x.has("requisitos") ? string(x["requisitos"].s()) : "";
                novo = new Workshop(titulo, data, vagas, mat, reqs);
            } else if (tipo == "Palestra") {
                string pal = x.has("palestrante") ? string(x["palestrante"].s()) : "Convidado";
                string tem = x.has("tema") ? string(x["tema"].s()) : "Sem tema";
                novo = new Palestra(titulo, data, vagas, pal, tem);
            } else if (tipo == "Hackathon") {
                string prem = x.has("premiacao") ? string(x["premiacao"].s()) : "";
                int tam = x.has("tamanho_equipe") ? x["tamanho_equipe"].i() : 5;
                string edital = x.has("edital") ? string(x["edital"].s()) : "Sem edital";
                novo = new Hackathon(titulo, data, vagas, prem, tam, edital); 
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