#include "Hackathon.hpp"
#include <iostream>

// Construtor: Inicializa a classe base Atividade e os atributos próprios
Hackathon::Hackathon(std::string t, std::string d, std::string di, std::string df, int cap, std::string prem, int tam, std::string edital)
    : Atividade(t, d, di, df, cap), premiacao(prem), tamanhoEquipe(tam), linkEdital(edital) {}