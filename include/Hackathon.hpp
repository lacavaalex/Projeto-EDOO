#ifndef HACKATHON_HPP
#define HACKATHON_HPP

#include "Atividade.hpp"
#include <vector>
#include <string>

class Hackathon : public Atividade {
private:
    std::string premiacao;
    int tamanhoEquipe;
    std::vector<std::string> stackTecnologica; // EXTRA: Agregação de dados

public:
    // Construtor seguindo o padrão da base
    Hackathon(std::string t, std::string d, int cap, std::string prem, int tam);

    // ESSENCIAL: Sobrescrita do método virtual puro
    void exibirDetalhes() const override;

    // EXTRA: Métodos de lógica de negócio para destaque
    void adicionarTecnologia(std::string tech);
    bool ehEventoPro() const; // Diferencial: Lógica baseada em critérios
};

#endif