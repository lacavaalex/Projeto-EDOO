#include <iostream>
#include <vector>
#include "include/Palestra.hpp"

int main() {
    // Vetor de ponteiros para a classe base
    std::vector<Atividade*> eventos;

    // Adicionando eventos dinamicamente
    eventos.push_back(new Palestra("Futuro da IA", "15/05/2026", 100, "Dr. Turing"));
    eventos.push_back(new Palestra("Clean Code", "20/05/2026", 50, "Uncle Bob"));

    std::cout << "--- LISTA DE EVENTOS DO CIN ---\n" << std::endl;

    // Percorrendo a lista e exibindo detalhes usando polimorfismo 
    for (auto e : eventos) {
        e->exibirDetalhes();
    }

    // Limpeza de memória
    for (auto e : eventos) {
        delete e;
    }

    return 0;
}