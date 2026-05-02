#include "Hackathon.hpp"
#include <iostream>

// Construtor: Inicializa a classe base Atividade e os atributos próprios
Hackathon::Hackathon(std::string t, std::string d, int cap, std::string prem, int tam)
    : Atividade(t, d, cap), premiacao(prem), tamanhoEquipe(tam) {}

void Hackathon::adicionarTecnologia(std::string tech) {
    stackTecnologica.push_back(tech);
}

// Lógica Extra: Hackathons com prêmios em dinheiro ou equipes grandes são "Pro"
bool Hackathon::ehEventoPro() const {
    return (tamanhoEquipe >= 5 || premiacao.find("R$") != std::string::npos);
}

void Hackathon::exibirDetalhes() const {
    std::cout << "\n========== [ HACKATHON ] ==========" << std::endl;
    std::cout << "Título: " << titulo << std::endl;
    std::cout << "Data: " << data << " | Equipes: " << tamanhoEquipe << " pessoas" << std::endl;
    std::cout << "Premiação: " << premiacao << std::endl;

    if (!stackTecnologica.empty()) {
        std::cout << "Tecnologias: ";
        for (const auto& tech : stackTecnologica) {
            std::cout << "[" << tech << "] ";
        }
        std::cout << std::endl;
    }

    if (ehEventoPro()) {
        std::cout << ">>> CATEGORIA: COMPETIÇÃO AVANÇADA <<<" << std::endl;
    }
    
    std::cout << "Inscritos: " << inscritos.size() << "/" << capacidadeMaxima << std::endl;
    std::cout << "===================================\n" << std::endl;
}