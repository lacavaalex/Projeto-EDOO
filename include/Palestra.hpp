#ifndef PALESTRA_HPP
#define PALESTRA_HPP

#include "Atividade.hpp"

class Palestra : public Atividade {
private:
    std::string palestrante;

public:
    Palestra(std::string t, std::string d, int cap, std::string p) 
        : Atividade(t, d, cap), palestrante(p) {}

    void exibirDetalhes() override {
        std::cout << "[PALESTRA] " << titulo << " | Palestrante: " << palestrante 
                  << " | Data: " << data << std::endl;
    }

    std::string getTipo() override { return "Palestra"; }
};

#endif