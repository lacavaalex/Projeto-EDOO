#ifndef PARTICIPANTE_HPP
#define PARTICIPANTE_HPP

#include <string>
#include <algorithm> // Para transformar o texto
#include <cctype>    // Para lidar com caracteres

using namespace std;

class Participante {
private:
    string nome;
    string email;
    string curso;

    // Métodos auxiliares de validação e formatação
    bool emailEhValido(string e);
    string formatarNome(string n);

public:
    Participante(string n, string e, string c);
    string getNome();
    string getEmail();
};

#endif