#ifndef PARTICIPANTE_HPP
#define PARTICIPANTE_HPP

#include <string>
#include <vector>

using namespace std;

// Forward Declaration. 
// Avisa ao C++ que a classe Atividade existe, evitando erro de loop nos arquivos.
class Atividade; 

class Participante {
private:
    string nome;
    string email;
    string curso;

    // Lista de ponteiros para as oportunidades onde o aluno se inscreveu
    vector<Atividade*> atividadesInscritas; 

    // Métodos de validação
    bool emailEhValido(string e);
    string formatarNome(string n);

public:
    Participante(string n, string e, string c);
    string getNome();
    string getEmail();
    
    // Novos métodos para gerenciar as inscrições do aluno
    void adicionarAtividade(Atividade* a);
    void listarMinhasAtividades();
};

#endif