#ifndef HACKATHON_HPP
#define HACKATHON_HPP

#include "Atividade.hpp"
#include <vector>
#include <string>

class Hackathon : public Atividade {
private:
    std::string premiacao;
    int tamanhoEquipe;
    std::string linkEdital;
    std::vector<std::string> stackTecnologica;

public:
    Hackathon(std::string t, std::string d, int cap, std::string prem, int tam, std::string edital);

    void exibirDetalhes() const override;

    void adicionarTecnologia(std::string tech);
    bool ehEventoPro() const; 
    
    std::string getDescricaoExtra() const override { 
    if (premiacao.find("Premiação:") != std::string::npos) {
        return premiacao; 
    }
    return "Premiação: " + premiacao + " | Equipe: " + std::to_string(tamanhoEquipe) + 
           " pessoas | Edital: " + linkEdital; 
    }
    std::string getTipo() const override { return "Hackathon";}
};

#endif