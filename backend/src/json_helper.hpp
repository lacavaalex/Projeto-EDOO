#ifndef JSON_HELPER_HPP
#define JSON_HELPER_HPP

#include <string>
#include "../include/Atividade.hpp"

inline std::string escapeJSON(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (c == '"')  out += "\\\"";
        else if (c == '\\') out += "\\\\";
        else out += c;
    }
    return out;
}

inline std::string atividadeParaJSON(Atividade* a) {
    std::string json = "{";
    json += "\"id\":"         + std::to_string(a->getId())            + ",";
    json += "\"titulo\":\""   + escapeJSON(a->getTitulo())            + "\",";
    json += "\"data\":\""     + escapeJSON(a->getData())              + "\",";
    json += "\"dataInicio\":\"" + a->getDataInicio() + "\",";
    json += "\"dataFim\":\"" + a->getDataFim() + "\",";
    json += "\"horario\":\"" + a->getHorario() + "\",";
    json += "\"local\":\"" + a->getLocal() + "\",";
    json += "\"duracao\":\"" + a->getDuracao() + "\",";
    json += "\"vagas\":"      + std::to_string(a->getCapacidade())    + ",";
    json += "\"tipo\":\""     + escapeJSON(a->getTipo())              + "\",";
    json += "\"descricao\":\"" + escapeJSON(a->getDescricaoExtra())   + "\"";
    json += "}";
    return json;
}

#endif