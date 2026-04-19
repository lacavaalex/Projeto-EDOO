#ifndef PALESTRA_HPP
#define PALESTRA_HPP

#include "Atividade.hpp"

class Palestra : public Atividade {
private:
    string palestrante;

public:
    Palestra(string t, string d, int cap, string p) 
        : Atividade(t, d, cap), palestrante(p) {}

    void exibirDetalhes() const override {
        cout << "[PALESTRA] " << titulo << " | Palestrante: " << palestrante 
             << " | Data: " << data << endl;
    }

    string getTipo() const override { return "Palestra"; }
};

#endif