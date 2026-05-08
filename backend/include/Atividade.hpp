#ifndef ATIVIDADE_HPP
#define ATIVIDADE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Participante.hpp" 

using namespace std;

class Atividade {
protected:
    int id = 0; 
    string titulo;
    string data;
    string dataInicioInscricao;
    string dataFimInscricao;
    string horario;
    string local;
    string duracao;
    string descricao;
    int capacidadeMaxima;
    vector<Participante*> inscritos;

public:
    Atividade(string t, string d, string di, string df, int cap, string h = "", string l = "", string dur = "") 
        : titulo(t), data(d), dataInicioInscricao(di), dataFimInscricao(df), capacidadeMaxima(cap), horario(h), local(l), duracao(dur) {}

    virtual ~Atividade() {}

    // Métodos para gerenciar o ID do banco de dados
    void setId(int novoId) { id = novoId; }
    int getId() const { return id; }


    virtual string getDescricaoExtra() const = 0; // Método abstrato

    virtual void exibirDetalhes() const = 0;
    virtual string getTipo() const = 0; 

    virtual bool validarVaga() const {
        return inscritos.size() < (size_t)capacidadeMaxima;
    }

    void seInscrever(Participante* p) {
        if (validarVaga()) {
            inscritos.push_back(p);
            p->adicionarAtividade(this);
            cout << "Inscricao realizada com sucesso!" << endl;
        } else {
            cout << "Inscricao cancelada: capacidade maxima atingida." << endl;
        }
    }

    string getTitulo() const { return titulo; }
    string getData() const { return data; }
    string getDataInicio() const { return dataInicioInscricao; }
    string getDataFim() const { return dataFimInscricao; }
    string getHorario() const { return horario; }
    string getLocal() const { return local; }
    string getDuracao() const { return duracao; }
    int getCapacidade() const { return capacidadeMaxima; }
    void setDescricao(string d) { descricao = d; }
};

#endif