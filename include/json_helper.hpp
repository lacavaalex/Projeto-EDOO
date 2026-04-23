#ifndef JSON_HELPER_HPP
#define JSON_HELPER_HPP

#include "Atividade.hpp"
#include <sstream>

// Função simples para converter uma atividade em JSON manualmente
string atividadeParaJSON(Atividade* a) {
    stringstream ss;
    ss << "{"
       << "\"titulo\":\"" << a->getTitulo() << "\","
       << "\"tipo\":\"" << a->getTipo() << "\","
       << "\"vagas\":" << a->validarVaga() // Retorna 1 se tem vaga, 0 se não
       << "}";
    return ss.str();
}

#endif