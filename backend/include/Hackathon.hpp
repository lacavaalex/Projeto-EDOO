#ifndef HACKATHON_HPP
#define HACKATHON_HPP

#include "Atividade.hpp"
#include <vector>
#include <string>

class Hackathon : public Atividade {
private:
    std::string premiacao;
    int tamanhoEquipe;
    std::vector<std::string> stackTecnologica;

public:
    Hackathon(std::string t, std::string d, int cap, std::string prem, int tam);

    void exibirDetalhes() const override;

    void adicionarTecnologia(std::string tech);
    bool ehEventoPro() const; 
    
    std::string getDescricaoExtra() const override { return premiacao; }
    std::string getTipo() const override { return "Hackathon";}
};

#endif