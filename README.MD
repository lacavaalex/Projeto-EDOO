# Estoque de Oportunidades - CIn/UFPE

Este projeto é um sistema de gerenciamento de eventos e oportunidades desenvolvido para a disciplina de **Estrutura de Dados Orientada a Objetos (EDOO)** do Centro de Informática da UFPE. 

O sistema permite conectar alunos a palestras, workshops e outras atividades acadêmicas, utilizando uma arquitetura robusta em C++.

## 🚀 Status do Projeto: Em Desenvolvimento
- [x] Modelagem de Classes (Participante, Atividade, Palestra, Workshop).
- [x] Validação de dados (E-mail e Formatação de Nomes).
- [x] **Persistência de Dados:** Integração com SQLite3.
- [x] **Associação Bidirecional:** Vínculo automático entre Aluno e Evento.
- [ ] Interface de Usuário (Menu Interativo).
- [ ] CRUD completo via Terminal.

## 🛠️ Tecnologias e Conceitos
* **Linguagem:** C++ (Padrão C++17).
* **Banco de Dados:** SQLite3 (Local).
* **POO:** Herança, Polimorfismo (Classes Abstratas), Encapsulamento e Composição.
* **Ferramentas:** VS Code, Git/GitHub, Compilador GCC/G++.

## 📂 Estrutura de Pastas
- `/include`: Arquivos de cabeçalho (.hpp e .h).
- `/src`: Implementação das classes e motor do banco (.cpp e .c).
- `/database`: Local reservado para o arquivo `sistema.db`.

## ⚙️ Como Compilar e Rodar
Devido à integração com o SQLite (C puro), a compilação é feita em duas etapas para garantir a compatibilidade:

1. **Gerar o objeto do banco de dados:**
   ```bash
   gcc -c src/sqlite3.c -o src/sqlite3.o