#include "../include/Participante.hpp"
#include <iostream>

using namespace std;

// Implementação do validador de e-mail
bool Participante::emailEhValido(string e) {
    // Verifica se tem um '@' e se ele não está no começo ou no fim
    size_t atPos = e.find('@');
    return (atPos != string::npos && atPos > 0 && atPos < e.length() - 1);
}

// Implementação da formatação do nome (Ex: "wallyson rodrigues" -> "Wallyson Rodrigues")
string Participante::formatarNome(string n) {
    if (n.empty()) return n;
    
    bool novoTermo = true;
    for (size_t i = 0; i < n.length(); i++) {
        if (isspace(n[i])) {
            novoTermo = true;
        } else if (novoTermo) {
            n[i] = toupper(n[i]);
            novoTermo = false;
        } else {
            n[i] = tolower(n[i]);
        }
    }
    return n;
}

Participante::Participante(string n, string e, string c) {
    nome = formatarNome(n); 
    curso = c;

    if (emailEhValido(e)) {
        email = e;
    } else {
        email = "invalido@cin.ufpe.br"; // Valor padrão caso o e-mail seja ruim
        cout << "Aviso: E-mail invalido fornecido para " << nome << endl;
    }
}

string Participante::getNome() { return nome; }
string Participante::getEmail() { return email; }