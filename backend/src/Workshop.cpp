#include <iostream>
#include "../include/Workshop.hpp" 

Workshop::Workshop(std::string t, std::string d, std::string di, std::string df, int cap, std::string mat, std::string req, string h, string l, string dur)
    : Atividade(t, d, di, df, cap, h, l, dur), materiais(mat), requisitos(req) {} 

void Workshop::exibirDetalhes() const {
    std::cout << "Workshop: " << std::endl;
    std::cout << "T�tulo: " << titulo << std::endl;
    std::cout << "Data: " << data << std::endl;
    std::cout << "Capacidade: " << capacidadeMaxima << std::endl;
    std::cout << "Materiais: " << materiais << std::endl;
    std::cout << "Requisitos: " << requisitos << std::endl;
}