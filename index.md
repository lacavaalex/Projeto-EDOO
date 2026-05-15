---
layout: default
title: CIn-Events — Gestão de Eventos do CIn/UFPE
description: Sistema full-stack para gerenciamento de eventos acadêmicos do Centro de Informática da UFPE, desenvolvido com C++ e React.
---

<style>
  /* Reset e Base */
  * { box-sizing: border-box; margin: 0; padding: 0; }
  body {
    font-family: 'Segoe UI', system-ui, -apple-system, sans-serif;
    background: #0d1117;
    color: #e6edf3;
    line-height: 1.7;
  }
  a { color: #58a6ff; text-decoration: none; }
  a:hover { text-decoration: underline; }

  /* ── Hero ── */
  .hero {
    background: linear-gradient(135deg, #0d1117 0%, #1a2234 50%, #0d2137 100%);
    border-bottom: 1px solid #21262d;
    padding: 80px 24px 60px;
    text-align: center;
    position: relative;
  }
  .hero-logo {
    width: 220px;
    max-width: 65vw;
    margin: 0 auto 30px;
    display: block;
    filter: drop-shadow(0 4px 24px rgba(31,111,235,0.3));
    border-radius: 12px;
  }
  .hero-badge {
    display: inline-block;
    background: rgba(31,111,235,0.15);
    border: 1px solid rgba(31,111,235,0.4);
    color: #58a6ff;
    font-size: 0.75rem;
    font-weight: 700;
    letter-spacing: 0.1em;
    text-transform: uppercase;
    padding: 5px 15px;
    border-radius: 20px;
    margin-bottom: 25px;
  }
  .hero h1 {
    font-size: clamp(2.5rem, 6vw, 4rem);
    font-weight: 800;
    letter-spacing: -0.03em;
    margin-bottom: 20px;
    background: linear-gradient(135deg, #fff 0%, #58a6ff 100%);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
  }
  .hero-subtitle {
    font-size: 1.2rem;
    color: #8b949e;
    max-width: 700px;
    margin: 0 auto 40px;
    font-weight: 300;
  }

  /* ── Buttons ── */
  .cta-group { display: flex; flex-wrap: wrap; gap: 15px; justify-content: center; }
  .btn {
    padding: 14px 28px;
    border-radius: 8px;
    font-size: 0.95rem;
    font-weight: 700;
    transition: all 0.2s ease;
    border: 1px solid transparent;
    display: flex;
    align-items: center;
    gap: 10px;
  }
  .btn-primary { background: #1f6feb; color: #fff; }
  .btn-primary:hover { background: #388bfd; text-decoration: none; transform: translateY(-2px); }
  .btn-pdf { background: #701c1c; color: #fff; }
  .btn-pdf:hover { background: #a02828; text-decoration: none; transform: translateY(-2px); }

  /* ── Sections ── */
  .section { max-width: 1000px; margin: 0 auto; padding: 80px 24px; }
  .section-dark { background: #161b22; border-top: 1px solid #21262d; border-bottom: 1px solid #21262d; }
  .section-title { font-size: 2rem; font-weight: 800; color: #fff; margin-bottom: 10px; letter-spacing: -1px; }
  .section-subtitle { color: #8b949e; margin-bottom: 40px; font-size: 1.1rem; }

  /* ── Screenshots ── */
  .screenshot-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; }
  .screenshot-card { background: #0d1117; border: 1px solid #30363d; border-radius: 12px; overflow: hidden; transition: 0.3s; }
  .screenshot-card:hover { border-color: #58a6ff; }
  .screenshot-card img { width: 100%; display: block; border-bottom: 1px solid #30363d; }
  .screenshot-label { padding: 15px; font-size: 0.85rem; color: #8b949e; font-weight: 600; text-align: center; }

  /* ── Features ── */
  .features-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(280px, 1fr)); gap: 20px; }
  .feature-card { background: #161b22; border: 1px solid #30363d; border-radius: 12px; padding: 30px; transition: 0.3s; }
  .feature-card:hover { border-color: #58a6ff; background: #1c2333; }
  .feature-icon { font-size: 2rem; margin-bottom: 15px; display: block; }
  .feature-card h3 { color: #fff; margin-bottom: 10px; font-size: 1.1rem; }
  .feature-card p { font-size: 0.9rem; color: #8b949e; }

  /* ── Architecture Diagram ── */
  .arch-box {
    background: #0d1117;
    border: 1px solid #30363d;
    border-radius: 12px;
    padding: 30px;
    font-family: 'JetBrains Mono', monospace;
    font-size: 0.85rem;
    overflow-x: auto;
    color: #e6edf3;
    line-height: 1.6;
  }
  .blue { color: #58a6ff; }
  .green { color: #3fb950; }

  /* ── Team ── */
  .team-grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(200px, 1fr)); gap: 15px; margin-top: 30px; }
  .team-card { background: #0d1117; border: 1px solid #30363d; border-radius: 10px; padding: 20px; text-align: center; }
  .team-card strong { display: block; color: #fff; font-size: 1rem; }
  .team-card span { color: #701c1c; font-size: 0.75rem; font-weight: 800; text-transform: uppercase; }

  /* ── Footer ── */
  footer { text-align: center; padding: 60px 24px; color: #8b949e; font-size: 0.9rem; border-top: 1px solid #21262d; }

  @media (max-width: 600px) {
    .btn { width: 100%; justify-content: center; }
  }
</style>

<div class="hero">
  <img class="hero-logo" src="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/WhatsApp%20Image%202026-05-07%20at%2016.35.57.jpeg" alt="CIn-Events Logo">
  <div class="hero-badge">CIn / UFPE · EDOO · 2026.1</div>
  <h1>CIn-Events</h1>
  <p class="hero-subtitle">
    O ecossistema definitivo para gestão de eventos acadêmicos. Robustez <strong>C++ nativa</strong> integrada à experiência reativa do <strong>React.js</strong>.
  </p>
  <div class="cta-group">
    <a class="btn btn-primary" href="https://github.com/lacavaalex/Projeto-EDOO">GitHub Repository</a>
    <a class="btn btn-pdf" href="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/Relat%C3%B3rio%20EDOO%20-%20CInEvents.pdf">Relatório Técnico (PDF)</a>
  </div>
</div>

<div class="section">
  <h2 class="section-title">🖥️ Demonstração Visual</h2>
  <p class="section-subtitle">Interface administrativa e core de processamento.</p>
  
  <div class="screenshot-grid">
    <div class="screenshot-card">
      <img src="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/Captura%20de%20tela%20de%202026-05-14%2017-42-49.png" alt="Admin Dashboard">
      <div class="screenshot-label">Painel Admin — Gestão de Atividades</div>
    </div>
    <div class="screenshot-card">
      <img src="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/Captura%20de%20tela%20de%202026-05-14%2017-42-21.png" alt="Backend Terminal">
      <div class="screenshot-label">Backend C++ — Motor de API Crow</div>
    </div>
  </div>
</div>

<div class="section-dark">
  <div class="section">
    <h2 class="section-title">🏗️ Arquitetura do Sistema</h2>
    <p class="section-subtitle">Separação de responsabilidades via API REST.</p>
    <div class="arch-box">
      <span class="blue">┌───────────────┐</span>          <span class="green">┌──────────────────┐</span><br>
      <span class="blue">│ React Frontend│</span> ◄──REST──► <span class="green">│ C++ Crow Backend │</span><br>
      <span class="blue">└───────────────┘</span>          <span class="green">└─────────┬────────┘</span><br>
                                           │<br>
                                 <span class="blue">┌─────────┴────────┐</span><br>
                                 <span class="blue">│ SQLite3 Engine   │</span><br>
                                 <span class="blue">└──────────────────┘</span>
    </div>
  </div>
</div>

<div class="section">
  <h2 class="section-title">🚀 Funcionalidades</h2>
  <div class="features-grid">
    <div class="feature-card">
      <span class="feature-icon">⚡</span>
      <h3>Performance Nativa</h3>
      <p>Backend em C++ utilizando o framework Crow para garantir respostas imediatas às requisições.</p>
    </div>
    <div class="feature-card">
      <span class="feature-icon">💾</span>
      <h3>Persistência SQLite</h3>
      <p>Armazenamento relacional robusto para eventos, palestras e hackathons.</p>
    </div>
    <div class="feature-card">
      <span class="feature-icon">🔐</span>
      <h3>Auth Flexível</h3>
      <p>Sistema de login que aceita Nome ou E-mail, com permissões distintas de Admin/User.</p>
    </div>
    <div class="feature-card">
      <span class="feature-icon">🧩</span>
      <h3>Conceitos POO</h3>
      <p>Uso rigoroso de Polimorfismo, Herança e Abstração (Classe Atividade).</p>
    </div>
  </div>
</div>

<div class="section-dark">
  <div class="section">
    <h2 class="section-title">👥 Equipe de Desenvolvimento</h2>
    <div class="team-grid">
      <div class="team-card"><strong>Alex Lacava</strong><span>PO & Backend</span></div>
      <div class="team-card"><strong>Bruno Silva</strong><span>Full-Stack</span></div>
      <div class="team-card"><strong>Maria Cláudia</strong><span>Full-Stack & Docs</span></div>
      <div class="team-card"><strong>José Romildo</strong><span>Developer</span></div>
      <div class="team-card"><strong>Wallyson Silva</strong><span>Backend & DBA</span></div>
    </div>
  </div>
</div>

<footer>
  <p>© 2026 CIn-Events | Centro de Informática - UFPE</p>
</footer>