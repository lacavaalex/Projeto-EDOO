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
    string getTipo() const override;
    bool seInscrever(Participante* p);
};

#endif