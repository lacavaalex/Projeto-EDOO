#ifndef ATIVIDADE_HPP
#define ATIVIDADE_HPP

#include <iostream>
#include <string>
#include <vector>

// Classe abstrata
class Atividade {
protected:
    std::string titulo;
    std::string data;
    int capacidadeMaxima;

public:
    Atividade(std::string t, std::string d, int cap) 
        : titulo(t), data(d), capacidadMaxima(cap) {}

    // Destrutor virtual 
    virtual ~Atividade() {}

    // Métodos Virtuais Puros
    virtual void exibirDetalhes() = 0; 
    virtual std::string getTipo() = 0;

    // Getters
    std::string getTitulo() const { return titulo; }
};

#endif