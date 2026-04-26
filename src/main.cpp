#include <iostream>
#include <string>
#include "../include/DatabaseManager.hpp"
#include "../include/Participante.hpp"
#include "../include/Workshop.hpp"
#include "../include/Palestra.hpp"
#include "../include/Estagio.hpp"
#include "../include/Clube.hpp"

using namespace std;

int main() {
    DatabaseManager dbManager("sistema.db");
    dbManager.initDatabase();

    int opcao;
    do {
        cout << "\n========== ESTOQUE DE OPORTUNIDADES CIN ==========" << endl;
        cout << "1. Cadastrar Aluno (Participante)" << endl;
        cout << "2. Cadastrar Novo Workshop" << endl;
        cout << "3. Listar Todas as Oportunidades" << endl;
        cout << "4. Listar Alunos Cadastrados" << endl;
        cout << "5. Cadastrar Vaga de Estagio" << endl;
        cout << "6. Cadastrar Clube do CIn" << endl;
        cout << "0. Sair" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); 

        if (opcao == 1) {
            string nome, email, curso;
            cout << "Nome completo: "; getline(cin, nome);
            cout << "E-mail: "; getline(cin, email);
            cout << "Curso: "; getline(cin, curso);

            Participante* p = new Participante(nome, email, curso);
            dbManager.salvarParticipante(p);
            delete p;

        } else if (opcao == 2) {
            string titulo, data, materiais, requisitos;
            int cap;
            cout << "Titulo do Workshop: "; getline(cin, titulo);
            cout << "Data (dd/mm/aaaa): "; getline(cin, data);
            cout << "Capacidade: "; cin >> cap; cin.ignore();
            cout << "Materiais necessarios: "; getline(cin, materiais);
            cout << "Requisitos de Software: "; getline(cin, requisitos);

            Atividade* w = new Workshop(titulo, data, cap, materiais, requisitos);
            dbManager.salvarAtividade(w);
            delete w;

        } else if (opcao == 3) {
            dbManager.listarAtividades();

        } else if (opcao == 4) {
            dbManager.listarParticipantes();
        }

        else if (opcao == 5) {
            string titulo, data, local;
            int cap;
            double bolsa;

            cout << "Vaga de Estagio (ex: Desenvolvedor VLAB): "; getline(cin, titulo);
            cout << "Data de Inicio das Inscrições (formato DD/MM/AAAA): "; getline(cin, data);
            cout << "Vagas: "; cin >> cap; cin.ignore();
            cout << "Local (Laboratorio/Empresa): "; getline(cin, local);
            cout << "Valor da Bolsa: "; cin >> bolsa; cin.ignore();

            Atividade* e = new Estagio(titulo, data, cap, bolsa, local);
            dbManager.salvarAtividade(e);
            delete e;
        }
        else if (opcao == 6) {
            string titulo, data, area, link;
            int cap;

            cout << "\n--- CADASTRO DE CLUBE ACADEMICO ---" << endl;
            cout << "Nome do Clube (ex: SEAL, LIGIA): "; 
            getline(cin, titulo);
            
            cout << "Previsao da Selecao (dd/mm/aaaa): "; 
            getline(cin, data);
            
            cout << "Quantidade de Vagas: "; 
            cin >> cap; 
            cin.ignore(); 
            
            cout << "Area de Foco (IA, Eng. Software, Jogos): "; 
            getline(cin, area);
            
            cout << "Link do Edital ou Formulario: "; 
            getline(cin, link);

            // Criei um Clube, mas guardei em um ponteiro de Atividade
            Atividade* c = new Clube(titulo, data, cap, area, link);
            
            if (dbManager.salvarAtividade(c)) {
                cout << "\n>>> Clube '" << titulo << "' cadastrado com sucesso!" << endl;
            }
            
            delete c; // Limpando a memória
}

    } while (opcao != 0);

    cout << "Encerrando o sistema... Ate logo!" << endl;
    return 0;
}