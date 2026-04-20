#ifndef WORKSHOP_HPP
#define WORKSHOP_HPP

#include "Atividade.hpp"
#include <string>

class Workshop : public Atividade {
private:
    std::string listaMateriais;
    std::string requisitosSoftware;
public:
    Workshop(std::string t, std::string d, int cap, std::string mat, std::string req);
    void exibirDetalhes() const override;

    string getTipo() const override { return "Workshop"; }
};
#endif 