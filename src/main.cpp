#include <iostream>
#include "../include/DatabaseManager.hpp"
#include "../include/Participante.hpp"

using namespace std;

int main() {
    // Inicializa o gestor do banco
    DatabaseManager dbManager("sistema.db");
    
    // Cria as tabelas
    dbManager.initDatabase();

    cout << "\n=== SISTEMA DE ESTOQUE DE OPORTUNIDADES ===" << endl;
    cout << "Aguardando novos comandos de interacao..." << endl;

    return 0;
}