#include "../include/Palestra.hpp"

Palestra::Palestra(string t, string d, string di, string df, int cap, string pal, string tem, string h, string l, string dur)
    : Atividade(t, d, di, df, cap, h, l, dur), palestrante(pal), tema(tem) {}

// Exibe os detalhes da palestra no console
void Palestra::exibirDetalhes() const {
    cout << "[PALESTRA] " << titulo
         << " | Palestrante: " << palestrante
         << " | Tema: " << tema
         << " | Data: " << data
         << " | Vagas: " << inscritos.size() << "/" << capacidadeMaxima
         << endl;
}

// Inscreve um participante na palestra
bool Palestra::seInscrever(Participante* p) {
    if (validarVaga()) {
        inscritos.push_back(p);
        p->adicionarAtividade(this);
        cout << "Inscricao na palestra '" << titulo << "' realizada com sucesso!" << endl;
        return true;
    }
    cout << "Inscricao cancelada: capacidade maxima atingida." << endl;
    return false;
}