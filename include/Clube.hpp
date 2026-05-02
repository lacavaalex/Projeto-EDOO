#ifndef CLUBE_HPP
#define CLUBE_HPP

#include "Atividade.hpp"

class Clube : public Atividade {
private:
    string areaEstudo; // Ex: Vibe Coding Girl, Maratona CIN, Vibe Hack
    string linkEdital; // Link para o formulário ou PDF do edital

public:
    // Construtor -> Repassa os dados para Atividade e salva os específicos do Clube
    Clube(string t, string d, int cap, string area, string link) 
        : Atividade(t, d, cap), areaEstudo(area), linkEdital(link) {}

    // Implementação dos métodos virtuais
    string getTipo() const override { return "Clube"; }

    string getDescricaoExtra() const override {
        return "Area: " + areaEstudo + " | Edital: " + linkEdital;
    }

    void exibirDetalhes() const override {
        cout << "[CLUBE ACADÊMICO] " << titulo << endl;
        cout << "Foco: " << areaEstudo << " | Vagas: " << capacidadeMaxima << endl;
        cout << "Inscricoes em: " << linkEdital << endl;
    }

    // Getters
    string getArea() const { return areaEstudo; }
    string getLink() const { return linkEdital; }
};

#endif