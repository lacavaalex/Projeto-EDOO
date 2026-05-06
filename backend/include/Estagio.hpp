#ifndef ESTAGIO_HPP
#define ESTAGIO_HPP

#include "Atividade.hpp"
#include <iostream>
#include <string>

using namespace std;

class Estagio : public Atividade {
private:
    double valorBolsa;
    string local;

public:
    Estagio(string t, string d, int cap, double b, string l) 
        : Atividade(t, d, cap), valorBolsa(b), local(l) {}

    // Implementação dos métodos da Atividade
    string getTipo() const override { return "Estagio"; }

    string getDescricaoExtra() const override {
        return "Local: " + local + " | Bolsa: R$ " + to_string(valorBolsa);
    }

    void exibirDetalhes() const override {
        cout << "[ESTÁGIO] " << titulo << " | Local: " << local << endl;
        cout << "Bolsa: R$ " << valorBolsa << " | Vagas: " << capacidadeMaxima << endl;
    }

    // Getters específicos
    double getBolsa() const { return valorBolsa; }
    string getLocal() const { return local; }
}; 

#endif