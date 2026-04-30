#include <iostream>
#include <string>
#include <vector>
#include "../include/DatabaseManager.hpp"
#include "../include/Participante.hpp"
#include "../include/Workshop.hpp"
#include "../include/Estagio.hpp"
#include "../include/Clube.hpp"
#include "crow_all.h"
#include "json_helper.hpp"
#include "Hackathon.hpp" 

using namespace std;

int main() {
    // Inicializa o Banco de Dados
    DatabaseManager dbManager("sistema.db");
    dbManager.initDatabase();

    Configura o Servidor API (Crow)
    crow::SimpleApp app;
    CROW_ROUTE(app, "/api/atividades")([&dbManager](){

        return crow::response("{\"status\": \"Conectado ao Banco de Dados\"}");
    });

    int opcao;
    do {
        cout << "\n========== SISTEMA CIn - ESTOQUE DE OPORTUNIDADES ==========" << endl;
        cout << "1. Cadastrar Participante" << endl;
        cout << "2. Cadastrar Workshop" << endl;
        cout << "3. Cadastrar Clube do CIn" << endl;
        cout << "4. Cadastrar Vaga de Estagio do CIn" << endl;
        cout << "5. Listar Todas as Oportunidades" << endl;
        cout << "6. Listar Alunos Cadastrados" << endl;
        cout << "7. Editar Capacidade" << endl;
        cout << "8. Remover Oportunidade" << endl;
        cout << "9. INICIAR SERVIDOR API (WEB)" << endl;
        cout << "0. Sair" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        
        if (!(cin >> opcao)) {
            cin.clear(); cin.ignore(1000, '\n'); opcao = -1;
        } else { cin.ignore(); }

        if (opcao == 1) {
            string n, e, c;
            cout << "Nome: "; getline(cin, n);
            cout << "E-mail: "; getline(cin, e);
            cout << "Curso: "; getline(cin, c);
            Participante* p = new Participante(n, e, c);
            dbManager.salvarParticipante(p);
            delete p;
        } else if (opcao == 2) {
            string t, d, m, r; int cap;
            cout << "Titulo: "; getline(cin, t);
            cout << "Data: "; getline(cin, d);
            cout << "Vagas: "; cin >> cap; cin.ignore();
            cout << "Materiais: "; getline(cin, m);
            cout << "Requisitos: "; getline(cin, r);
            Atividade* w = new Workshop(t, d, cap, m, r);
            dbManager.salvarAtividade(w);
            delete w;
        } else if (opcao == 3) {
            string t, d, a, l; int cap;
            cout << "Clube: "; getline(cin, t);
            cout << "Selecao: "; getline(cin, d);
            cout << "Vagas: "; cin >> cap; cin.ignore();
            cout << "Area: "; getline(cin, a);
            cout << "Edital: "; getline(cin, l);
            Atividade* cl = new Clube(t, d, cap, a, l);
            dbManager.salvarAtividade(cl);
            delete cl;
        } else if (opcao == 4) {
            string t, d, loc; int cap; double b;
            cout << "Vaga: "; getline(cin, t);
            cout << "Inscricao: "; getline(cin, d);
            cout << "Vagas: "; cin >> cap; cin.ignore();
            cout << "Local: "; getline(cin, loc);
            cout << "Bolsa: "; while(!(cin >> b)){ cin.clear(); cin.ignore(1000, '\n'); cout << "Erro! Valor: "; }
            cin.ignore();
            Atividade* es = new Estagio(t, d, cap, b, loc);
            dbManager.salvarAtividade(es);
            delete es;
        } else if (opcao == 5) {
            dbManager.listarAtividades();
        } else if (opcao == 6) {
            dbManager.listarParticipantes();
        } else if (opcao == 7) {
            int id, cap;
            cout << "ID: "; cin >> id; cout << "Nova Cap: "; cin >> cap;
            dbManager.atualizarCapacidade(id, cap);
        } else if (opcao == 8) {
            int id; cout << "ID para remover: "; cin >> id;
            dbManager.excluirAtividade(id);
        } else if (opcao == 9) {
            cout << ">>> SERVIDOR WEB ATIVO em http://localhost:8080" << endl;
            app.port(8080).multithreaded().run();
        }

    } while (opcao != 0);

    cout << "Encerrando... Ate logo!" << endl;
    return 0;
}