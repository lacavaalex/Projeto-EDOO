#include <iostream>
#include "../include/Workshop.hpp" 

Workshop::Workshop(std::string t, std::string d, int cap, std::string mat, std::string req)
    : Atividade(t, d, cap), materiais(mat), software(req) {} 

void Workshop::exibirDetalhes() const {
    std::cout << "Workshop: " << std::endl;
    std::cout << "T�tulo: " << titulo << std::endl;
    std::cout << "Data: " << data << std::endl;
    std::cout << "Capacidade: " << capacidadeMaxima << std::endl;
    std::cout << "Materiais: " << materiais << std::endl;
    std::cout << "Requisitos: " << software << std::endl;
}