#ifndef ATIVIDADE_HPP
#define ATIVIDADE_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Atividade {
protected:
    string titulo;
    string data;
    int capacidadeMaxima;
    // esse array dinamico vai interagir com o participante atual (usa o endereço pra otimizacao de memoria)
    vector<Participante*> inscritos;

public:
    // construtor
    Atividade(string t, string d, int cap) 
        : titulo(t), data(d), capacidadeMaxima(cap) {}

    // destrutor
    virtual ~Atividade() {
      
    }

    // abstração: metodos virtuais puros para serem herdados
    virtual void exibirDetalhes() const = 0;
    
    // metodo que verifica se a inscricao pode ser feita
    virtual bool validarVaga() const {
    // size_t vai garantir que o número é comparavel com o tipo retornado por um vetor
        return inscritos.size() < (size_t)capacidadeMaxima;
    }

    // metodo de validacao da inscricao
    void seInscrever(Participante* p) {
        if (validarVaga()) {
            inscritos.push_back(p);
            cout << "Inscricao realizada com sucesso!" << endl;
        } else {
            cout << "Inscricao cancelada: capacidade maxima do evento atingida." << endl;
        }
    }

    // Getters básicos
    string getTitulo() const { return titulo; }
};

#endif
