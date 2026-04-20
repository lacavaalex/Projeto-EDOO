#include <iostream>
#include <vector>
#include "../include/Palestra.hpp"
#include "../include/Workshop.hpp"
#include "../include/Participante.hpp"

using namespace std;

int main() {
    // Cria o Participante 
    // Eu (Wallyson) escrevi tudo minúsculo e com e-mail estranho para testar o código
    Participante* usuario = new Participante("wallyson rodrigues", "wallyson@cin.ufpe.br", "Sistemas de Informacao");

    // Cria o "Estoque de Oportunidades" 
    vector<Atividade*> estoque;
    estoque.push_back(new Palestra("IA no CIn", "20/04/2026", 2, "Dr. Francisco Simoes"));
    estoque.push_back(new Workshop("Git Avancado", "22/04/2026", 20, "Monitoria EDOO", "VS Code instalado"));

    cout << "=== BEM-VINDO AO ESTOQUE DE OPORTUNIDADES DO CIN ===\n" << endl;
    cout << "Usuario logado: " << usuario->getNome() << " (" << usuario->getEmail() << ")" << endl;

    // Realizando Inscricoes
    cout << "\n--- Realizando Inscricoes ---" << endl;
    for (auto oportunidade : estoque) {
        oportunidade->seInscrever(usuario);
    }

    // Verifica o Cronograma do Aluno 
    cout << "\n--- Meu Cronograma de Atividades ---" << endl;
    usuario->listarMinhasAtividades();

    // Limpeza de Memoria 
    for (auto o : estoque) delete o;
    delete usuario;

    return 0;
}