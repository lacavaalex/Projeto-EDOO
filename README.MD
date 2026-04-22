# CIn-Events - Gestão de Eventos do CIn/UFPE

Este projeto consiste em um sistema desenvolvido para a disciplina de **Estrutura de Dados Orientada a Objetos (EDOO)** do Centro de Informática da UFPE. O objetivo é gerenciar os eventos realizados no centro, aplicando conceitos de POO e estruturas de dados eficientes em C++.

## 🚀 Funcionalidades

### Gestão de Atividades
O sistema utiliza uma estrutura de herança para suportar diferentes tipos de eventos acadêmicos:
* **Palestras:** Foco em apresentações com palestrantes convidados.
* **Workshops:** Atividades práticas com lista de materiais e requisitos de software.
* **Hackathons:** Competições de programação com gestão de premiação e validação de vagas por equipe.

### Inscrições e Controle
* **Gerenciamento de Participantes:** Cadastro e associação de participantes a atividades específicas.
* **Lógica de Inscrição:** Sistema que valida se há vagas disponíveis antes de confirmar a participação.
* **Persistência (Prevista):** Conexão com banco de dados para salvar os registros.

## 🛠️ Tecnologias e Conceitos de EDOO Aplicados

O projeto demonstra a aplicação prática dos pilares de Programação Orientada a Objetos:

1. **Abstração:** Uso da classe abstrata `Atividade` como interface comum.
2. **Herança:** Especialização das subclasses `Palestra`, `Workshop` e `Hackathon`.
3. **Polimorfismo Dinâmico:** Sobrescrita de métodos virtuais puros (`exibirDetalhes`), permitindo o processamento genérico de eventos via ponteiros da classe base.
4. **Encapsulamento:** Proteção de dados sensíveis através de modificadores de acesso (`private` e `protected`).
5. **Gestão de Memória:** Uso de vetores dinâmicos (`std::vector`) e destrutores virtuais para garantir a integridade da memória.

## 📂 Estrutura do Projeto

* **Linguagem:** C++
* **Ferramentas:** VS Code, Git/GitHub (Fluxo de trabalho via Branches e Pull Requests).
* **Organização:**
    * `include/`: Ficheiros de cabeçalho (`.hpp`).
    * `src/`: Implementações (`.cpp`).

## 👥 Equipe
* Alex Lacava
* Bruno Silva
* José Romildo
* Maria Cláudia
* Wallyson Silva

---
*Projeto desenvolvido como parte da avaliação da disciplina CIN0135 - EDOO.*