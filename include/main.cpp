#include <iostream>
#include <vector>
#include "include/Palestra.hpp"
#include "include/Hackathon.hpp" // Adicione esta linha

int main() {
    std::vector<Atividade*> eventos;

    eventos.push_back(new Palestra("Futuro da IA", "15/05/2026", 100, "Dr. Turing"));
    
    Hackathon* h = new Hackathon("CIn Code", "22/05/2026", 50, "R$ 2000", 5);
    h->adicionarTecnologia("C++");
    h->adicionarTecnologia("Git");
    eventos.push_back(h); 

    std::cout << "--- LISTA DE EVENTOS DO CIN ---\n" << std::endl;

    for (auto e : eventos) {
        e->exibirDetalhes(); // O Polimorfismo decide qual exibirDetalhes chamar!
    }

    // Limpeza de memória
    for (auto e : eventos) {
        delete e;
    }

    return 0;
}