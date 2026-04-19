#include "../include/Participante.hpp"

using namespace std;

Participante::Participante(string n, string e, string c) {
    nome = n;
    email = e;
    curso = c;
}

string Participante::getNome() {
    return nome;
}

string Participante::getEmail() {
    return email;
}