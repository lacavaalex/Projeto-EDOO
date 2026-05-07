#ifndef WORKSHOP_HPP
#define WORKSHOP_HPP

#include "Atividade.hpp"
#include <string>

using namespace std; 

class Workshop : public Atividade {
private:
    string materiais;
    string requisitos;
public:
    Workshop(std::string t, std::string d, int cap, std::string mat, std::string req);
    void exibirDetalhes() const override;

    string getTipo() const override { return "Workshop"; }

    string getDescricaoExtra() const override {
    if (materiais.find("Materiais:") != string::npos) {
        return materiais; 
    }
    return "Materiais: " + materiais + " | Requisitos: " + requisitos;
}
};
#endif 