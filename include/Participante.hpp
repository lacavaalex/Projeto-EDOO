#ifndef PARTICIPANTE_HPP
#define PARTICIPANTE_HPP

#include <string>

using namespace std;

class Participante {
private:
    string nome;
    string email;
    string curso;

public:
    Participante(string n, string e, string c);
    string getNome();
    string getEmail();
};

#endif