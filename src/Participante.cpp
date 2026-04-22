#include "../include/Participante.hpp"
#include "../include/Atividade.hpp" 
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

// Lógica de validação de e-mail
bool Participante::emailEhValido(string e) {
    size_t atPos = e.find('@');
    return (atPos != string::npos && atPos > 0 && atPos < e.length() - 1);
}

// Implementação da formatação do nome (Ex: "wallyson rodrigues" -> "Wallyson Rodrigues")
string Participante::formatarNome(string n) {
    if (n.empty()) return n;
    bool novoTermo = true;
    for (size_t i = 0; i < n.length(); i++) {
        if (isspace(n[i])) novoTermo = true;
        else if (novoTermo) { n[i] = toupper(n[i]); novoTermo = false; }
        else n[i] = tolower(n[i]);
    }
    return n;
}

// Construtor 
Participante::Participante(string n, string e, string c) {
    nome = formatarNome(n);
    curso = c;
    // Se o e-mail for válido, salva. Se não, coloca um padrão de erro.
    email = emailEhValido(e) ? e : "erro.email@cin.ufpe.br";
}

// Implementação das funções de lista
void Participante::adicionarAtividade(Atividade* a) {
    atividadesInscritas.push_back(a);
}

void Participante::listarMinhasAtividades() {
    cout << "\n>>> Agenda de: " << nome << endl;
    if (atividadesInscritas.empty()) {
        cout << "Nenhuma atividade encontrada." << endl;
    } else {
        for (auto a : atividadesInscritas) {
            // Chamamos o getTitulo que está na Atividade.hpp
            cout << "- " << a->getTitulo() << endl;
        }
    }
}

string Participante::getNome() { return nome; }
string Participante::getEmail() { return email; }