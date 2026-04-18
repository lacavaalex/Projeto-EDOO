#ifndef HACKATHON_HPP
#define HACKATHON_HPP

#include "Atividade.hpp"

// Hackathon herdando de Atividade (Herança)
class Hackathon : public Atividade {
private:
    string premiacao;
    int tamanhoEquipe;

public:
    // Construtor: Chama o construtor da classe Base (Atividade)
    Hackathon(string t, string d, int cap, string prem, int tam)
        : Atividade(t, d, cap), premiacao(prem), tamanhoEquipe(tam) {}

    // Implementação do método virtual puro (Polimorfismo)
    // O 'const' aqui é essencial para bater com a assinatura da base!
    void exibirDetalhes() const override {
        cout << "[HACKATHON] " << titulo << endl;
        cout << "Data: " << data << " | Equipes: " << tamanhoEquipe << " pessoas" << endl;
        cout << "Premio: " << premiacao << endl;
        cout << "Vagas: " << inscritos.size() << "/" << capacidadeMaxima << endl;
        cout << "------------------------------------------" << endl;
    }
};

#endif