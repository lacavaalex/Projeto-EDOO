#include "../include/Palestra.hpp"

Palestra::Palestra(string t, string d, string di, string df, int cap, string pal, string tem, string h, string l, string dur)
    : Atividade(t, d, di, df, cap, h, l, dur), palestrante(pal), tema(tem) {}
