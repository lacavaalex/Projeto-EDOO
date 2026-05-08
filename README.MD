# CIn-Events - Gestão de Eventos do CIn/UFPE

Este projeto é um sistema de gestão de eventos acadêmicos desenvolvido para a disciplina de **Estrutura de Dados Orientada a Objetos** no Centro de Informática da UFPE. O sistema utiliza uma arquitetura **Full-stack**, integrando um backend robusto em C++ com uma interface Single Page Application (SPA) em React. O objetivo do projeto foi treinar os conceitos do paradigma de Programação Orientada a Objeto aprendidos em sala.

## 💻 O Sistema

O **CIn-Events** permite que administradores gerenciem o ciclo de vida de eventos (Palestras, Workshops e Hackathons) e que alunos visualizem oportunidades de forma integrada.

### 🛠️ Funcionalidades Implementadas

* **Arquitetura Client-Server**: Comunicação via API REST utilizando o framework **Crow C++**.
* **Persistência de Dados**: Integração com **SQLite** para armazenamento de atividades e **JSON** para persistência de usuários.
* **Sistema de Autenticação**: 
    * Login flexível para usuários (aceita E-mail ou Nome).
    * **Modo Administrador**: Acesso restrito para criação, edição completa de todos os campos e exclusão de eventos.
* **Interface Web Moderna**: 
    * Desenvolvida em **React** com roteamento dinâmico via `react-router-dom`.
    * Estética inspirada em terminais (Fonte *JetBrains Mono*) e identidade visual do CIn/UFPE.
    * **Sistema de Notificações**: Pop-ups customizados (Modais e Toasts) para feedback de ações do sistema (CRUD e Auth).
* **Gestão Dinâmica (CRUD)**: Edição em tempo real de atributos como título, data, vagas, horário e local diretamente nos cards da interface.

## ⚙️ Tecnologias e Conceitos de EDOO

O projeto aplica os pilares fundamentais de POO em um cenário real:

1.  **Abstração**: Uso da classe abstrata `Atividade` como interface comum para todos os eventos.
2.  **Herança**: Especialização das subclasses `Palestra`, `Workshop` e `Hackathon`.
3.  **Polimorfismo Dinâmico**: Sobrescrita de métodos virtuais como `getDescricaoExtra()` e `getTipo()`, permitindo o processamento genérico de eventos via ponteiros da classe base.
4.  **Encapsulamento**: Proteção de dados através de modificadores de acesso e gerenciamento de estado no React.

## 📂 Estrutura de Pastas

* `include/`: Headers (`.hpp`) com as definições de classes.
* `src/`: Implementações (`.cpp`) da lógica de negócio e rotas da API.
* `data/`: Arquivos de persistência (`sistema.db` e `usuarios.json`).
* `frontend/`: Código fonte da interface em React/Vite.

## 🚀 Como Executar

### Backend (C++)
Na pasta `backend/`, abra um terminal e execute o seguinte comando:
```bash
g++ -I./include src/*.cpp -o cinevents -lsqlite3 && ./cinevents
```

### Frontend (React)
Na pasta `frontend/`, abra outro terminal e execute os seguintes comandos:
```bash
npm install
npm run dev
```

## 👥 Equipe
* Alex Lacava
* Bruno Silva
* José Romildo
* Maria Cláudia
* Wallyson Silva