#include "Hackathon.hpp"
#include <iostream>

// Construtor: Inicializa a classe base Atividade e os atributos próprios
Hackathon::Hackathon(std::string t, std::string d, std::string di, std::string df, int cap, std::string prem, int tam, std::string edital)
    : Atividade(t, d, di, df, cap), premiacao(prem), tamanhoEquipe(tam), linkEdital(edital) {}

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
    std::cout << "Data: " << data << std::endl;
    std::cout << "Capacidade: " << capacidadeMaxima << " vagas" << std::endl;
    std::cout << "Tamanho da Equipe: " << (tamanhoEquipe > 0 ? std::to_string(tamanhoEquipe) : "Não definido") << std::endl;
    std::cout << "Premiação: " << premiacao << std::endl;
    
    if (!linkEdital.empty()) {
        std::cout << "Edital: " << linkEdital << std::endl;
    }

    if (ehEventoPro()) {
        std::cout << ">>> CATEGORIA: COMPETIÇÃO AVANÇADA <<<" << std::endl;
    }
}