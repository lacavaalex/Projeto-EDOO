#ifndef PALESTRA_HPP
#define PALESTRA_HPP

#include "Atividade.hpp"

class Palestra : public Atividade {
private:
    string palestrante;
    string tema;

public:
    Palestra(string t, string d, string di, string df, int cap, string pal, string tem, string h = "", string l = "", string dur = "");

    string getTipo() const override { return "Palestra"; }
    
    string getDescricaoExtra() const override { 
        if (palestrante.find("Palestrante:") != string::npos) {
        return palestrante;
    }
        return "Palestrante: " + palestrante + " | Tema: " + tema + " | Horário: " + getHorario() + " | Duração: " + getDuracao() + " | Local: " + getLocal();
    }  
    
    bool seInscrever(Participante* p);
};

#endif