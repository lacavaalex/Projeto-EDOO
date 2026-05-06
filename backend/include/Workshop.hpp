#ifndef WORKSHOP_HPP
#define WORKSHOP_HPP

#include "Atividade.hpp"
#include <string>

using namespace std; 

class Workshop : public Atividade {
private:
    string materiais;
    string software;
public:
    Workshop(std::string t, std::string d, int cap, std::string mat, std::string req);
    void exibirDetalhes() const override;

    string getTipo() const override { return "Workshop"; }

    string getDescricaoExtra() const override {
    return "Materiais: " + materiais + " | Requisitos: " + software;
}
};
#endif 