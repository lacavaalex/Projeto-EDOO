#ifndef PALESTRA_HPP
#define PALESTRA_HPP

#include "Atividade.hpp"

class Palestra : public Atividade {
private:
    string palestrante;
    string tema;

public:
    Palestra(string t, string d, int cap, string pal, string tem);

    void exibirDetalhes() const override;
    string getTipo() const override { return "Palestra"; }
    
    string getDescricaoExtra() const override { 
        return palestrante + tema; 
    }  
    
    bool seInscrever(Participante* p);
};

#endif