#include <iostream>
#include "../include/DatabaseManager.hpp"
#include "../include/Participante.hpp"
#include "../include/Workshop.hpp"

using namespace std;

int main() {
    DatabaseManager dbManager("sistema.db");
    dbManager.initDatabase();

    // Criando uma oportunidade (ex: um Workshop de Git)
    Atividade* novoWorkshop = new Workshop("Git Avancado", "12/05/2026", 30, "Notebook", "Git instalado");

    // Salvando no banco
    if(dbManager.salvarAtividade(novoWorkshop)) {
        cout << "Oportunidade cadastrada com sucesso!" << endl;
    }

    // Mostrando o que tem lá
    dbManager.listarAtividades();

    delete novoWorkshop;
    return 0;
}