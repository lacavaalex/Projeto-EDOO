#include <iostream>
#include "Workshop.hpp"

Workshop::Workshop(std::string t, std::string d, int cap, std::string mat, std::string req)
    : Atividade(t, d, cap), listaMateriais(mat), requisitosSoftware(req) {} 


