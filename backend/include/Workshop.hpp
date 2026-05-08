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
    Workshop(std::string t, std::string d, std::string di, std::string df, int cap, std::string mat, std::string req, string h = "", string l = "", string dur = "");

    string getTipo() const override { return "Workshop"; }

    string getDescricaoExtra() const override {
    if (materiais.find("Materiais:") != string::npos) {
        return materiais; 
    }
    return "Materiais: " + materiais + " | Requisitos: " + requisitos + " | Horário: " + getHorario() + " | Duração: " + getDuracao() + " | Local: " + getLocal();
}
};
#endif 