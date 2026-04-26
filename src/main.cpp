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
        cout << "3. Cadastrar Clube do CIn" << endl;
        cout << "4. Cadastrar Vaga de Estagio" << endl;
        cout << "5. Listar Todas as Oportunidades" << endl;
        cout << "6. Listar Alunos Cadastrados" << endl;
        cout << "7. Editar Capacidade de Oportunidade" << endl;
        cout << "8. Remover Oportunidade" << endl;
        cout << "0. Sair" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        

        if (!(cin >> opcao)) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(1000, '\n'); // Descarta o que foi digitado
            opcao = -1;
        } else {
            cin.ignore(); 
        }

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
            
            cout << "Capacidade: "; 
            while (!(cin >> cap)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "!!! Erro: Digite apenas numeros para a capacidade: ";
            }
            cin.ignore();

            cout << "Materiais necessarios: "; getline(cin, materiais);
            cout << "Requisitos de Software: "; getline(cin, requisitos);

            Atividade* w = new Workshop(titulo, data, cap, materiais, requisitos);
            dbManager.salvarAtividade(w);
            delete w;

        } else if (opcao == 3) { 
            string titulo, data, area, link;
            int cap;

            cout << "\n--- CADASTRO DE CLUBE ACADEMICO ---" << endl;
            cout << "Nome do Clube (ex: SEAL, LIGIA): "; getline(cin, titulo);
            cout << "Previsao da Selecao (dd/mm/aaaa): "; getline(cin, data);
            
            cout << "Quantidade de Vagas: "; 
            while (!(cin >> cap)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "!!! Erro: Digite apenas numeros para vagas: ";
            }
            cin.ignore(); 
            
            cout << "Area de Foco (IA, Eng. Software, Jogos): "; getline(cin, area);
            cout << "Link do Edital ou Formulario: "; getline(cin, link);

            Atividade* c = new Clube(titulo, data, cap, area, link);
            dbManager.salvarAtividade(c);
            delete c;

        } else if (opcao == 4) { 
            string titulo, data, local;
            int cap;
            double bolsa;

            cout << "Vaga de Estagio (ex: Desenvolvedor VLAB): "; getline(cin, titulo);
            cout << "Data de Inicio das Inscricoes (formato DD/MM/AAAA): "; getline(cin, data);
            
            cout << "Vagas: "; 
            while (!(cin >> cap)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "!!! Erro: Digite apenas numeros para vagas: ";
            }
            cin.ignore();

            cout << "Local (Laboratorio/Empresa): "; getline(cin, local);
            
            cout << "Valor da Bolsa (apenas numeros): "; 
            while (!(cin >> bolsa)) { 
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "!!! Erro: Digite apenas o valor numerico (Ex: 1500): ";
            }
            cin.ignore();

            Atividade* e = new Estagio(titulo, data, cap, bolsa, local);
            dbManager.salvarAtividade(e);
            delete e;

        } else if (opcao == 5) { 
            dbManager.listarAtividades();

        } else if (opcao == 6) { 
            dbManager.listarParticipantes();

        } else if (opcao == 7) {
            int id, novaCap;
            cout << "ID da oportunidade para editar: "; 
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "!!! Erro: Digite um ID numerico: ";
            }
            cout << "Nova capacidade: "; 
            while (!(cin >> novaCap)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "!!! Erro: Digite apenas numeros: ";
            }
            dbManager.atualizarCapacidade(id, novaCap);

        } else if (opcao == 8) {
            int id;
            cout << "ID da oportunidade para remover: "; 
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "!!! Erro: Digite um ID numerico: ";
            }
            dbManager.excluirAtividade(id);

        } else if (opcao != 0 && opcao != -1) {
            cout << "Opcao invalida! Tente novamente." << endl;
        }

    } while (opcao != 0);

    cout << "Encerrando o sistema... Ate logo!" << endl;
    return 0;
}