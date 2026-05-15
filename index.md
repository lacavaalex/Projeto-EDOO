<div style="font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; max-width: 1100px; margin: 0 auto; color: #1a1a1a; background: #fff; line-height: 1.7;">

  <header style="text-align: center; padding: 100px 20px; background: linear-gradient(180deg, #f8f9fa 0%, #ffffff 100%); border-bottom: 5px solid #701c1c;">
    <img src="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/image_dcd3be.jpg" alt="Logo CIn-Events" style="width: 250px; margin-bottom: 30px; filter: drop-shadow(0 5px 15px rgba(0,0,0,0.1));">
    <h1 style="font-size: 4.5rem; font-weight: 900; color: #701c1c; margin: 0; letter-spacing: -3px; line-height: 1;">CIn-Events</h1>
    <p style="font-size: 1.6rem; color: #555; max-width: 850px; margin: 25px auto 45px; font-weight: 300;">
      Ecossistema de Alta Performance para Gestão de Atividades Acadêmicas no Centro de Informática da UFPE.
    </p>
    
    <div style="display: flex; justify-content: center; gap: 25px; flex-wrap: wrap;">
      <a href="https://github.com/lacavaalex/Projeto-EDOO" style="background: #1a1a1a; color: white; padding: 18px 35px; border-radius: 8px; text-decoration: none; font-weight: 700; transition: 0.3s;">REPOSITÓRIO GITHUB</a>
      <a href="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/Relat%C3%B3rio%20EDOO%20-%20CInEvents.pdf" style="background: #701c1c; color: white; padding: 18px 35px; border-radius: 8px; text-decoration: none; font-weight: 700; transition: 0.3s;">RELATÓRIO TÉCNICO (PDF)</a>
    </div>
  </header>

  <section style="padding: 90px 20px;">
    <h2 style="font-size: 2.8rem; color: #1a1a1a; margin-bottom: 40px; border-left: 12px solid #701c1c; padding-left: 25px; letter-spacing: -1px;">Arquitetura e Engenharia</h2>
    <p style="font-size: 1.3rem; color: #444; text-align: justify; margin-bottom: 50px; max-width: 900px;">
      O <strong>CIn-Events</strong> foi concebido sob uma arquitetura <strong>Client-Server</strong> robusta, focada em escalabilidade e baixa latência. O sistema integra um core de processamento em <strong>C++</strong> com uma interface de última geração em <strong>React</strong>, garantindo que as regras de negócio de POO sejam aplicadas com rigor matemático e performance nativa.
    </p>
    
    <div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(320px, 1fr)); gap: 35px;">
      <div style="background: #f8f9fa; padding: 40px; border-radius: 20px; border: 1px solid #eee; box-shadow: 0 10px 30px rgba(0,0,0,0.02);">
        <h3 style="color: #701c1c; font-size: 1.8rem; margin-top: 0; margin-bottom: 20px;">Backend Core (C++)</h3>
        <p style="color: #666;">Motor de processamento baseado em padrões de alta performance:</p>
        <ul style="color: #333; font-weight: 500;">
          <li><strong>Crow API:</strong> Framework para roteamento REST e manipulação de JSON em tempo real.</li>
          <li><strong>SQLite Engine:</strong> Persistência relacional para gestão de eventos e histórico.</li>
          <li><strong>Data Integrity:</strong> Validação de restrições de vagas e horários via C++.</li>
        </ul>
      </div>
      <div style="background: #f8f9fa; padding: 40px; border-radius: 20px; border: 1px solid #eee; box-shadow: 0 10px 30px rgba(0,0,0,0.02);">
        <h3 style="color: #701c1c; font-size: 1.8rem; margin-top: 0; margin-bottom: 20px;">Frontend & UX (React)</h3>
        <p style="color: #666;">Single Page Application focada na experiência do usuário:</p>
        <ul style="color: #333; font-weight: 500;">
          <li><strong>Roteamento Dinâmico:</strong> Navegação fluida entre perfis de Aluno e Admin.</li>
          <li><strong>Reatividade:</strong> Atualização imediata de vagas e status de atividades.</li>
          <li><strong>UI Term-Style:</strong> Design inspirado em terminais modernos com tipografia JetBrains Mono.</li>
        </ul>
      </div>
    </div>
  </section>

  <section style="background: #0a0a0a; padding: 100px 20px; color: #fff; text-align: center; border-radius: 50px; margin: 0 15px;">
    <h2 style="font-size: 3rem; margin-bottom: 20px;">Sistema em Operação</h2>
    <p style="color: #777; font-size: 1.2rem; margin-bottom: 80px;">Capturas reais da integração entre Interface e Servidor.</p>
    
    <div style="display: flex; flex-direction: column; gap: 100px; align-items: center;">
      <div style="max-width: 950px;">
        <p style="color: #701c1c; font-weight: 900; letter-spacing: 3px; margin-bottom: 25px; font-size: 1.2rem;">DASHBOARD DE CONTROLE - ADMIN</p>
        <img src="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/Captura%20de%20tela%20de%202026-05-14%2017-42-49.png" alt="Dashboard Admin" style="width: 100%; border-radius: 15px; border: 2px solid #333; box-shadow: 0 30px 80px rgba(112,28,28,0.2);">
        <p style="margin-top: 25px; color: #aaa; font-style: italic;">Interface Web: Gestão centralizada de Palestras, Workshops e Hackathons.</p>
      </div>

      <div style="max-width: 950px;">
        <p style="color: #701c1c; font-weight: 900; letter-spacing: 3px; margin-bottom: 25px; font-size: 1.2rem;">ARQUITETURA DE DADOS & API</p>
        <img src="https://raw.githubusercontent.com/lacavaalex/Projeto-EDOO/main/src/Captura%20de%20tela%20de%202026-05-14%2017-42-21.png" alt="Backend Code" style="width: 100%; border-radius: 15px; border: 2px solid #333; box-shadow: 0 30px 80px rgba(112,28,28,0.2);">
        <p style="margin-top: 25px; color: #aaa; font-style: italic;">Infraestrutura C++: Processamento de requisições e persistência SQLite.</p>
      </div>
    </div>
  </section>

  <section style="padding: 100px 20px;">
    <h2 style="text-align: center; font-size: 3rem; margin-bottom: 70px;">Fundamentos de POO</h2>
    <div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(220px, 1fr)); gap: 30px;">
      <div style="text-align: center; padding: 30px; border: 1px solid #eee; border-radius: 15px;">
        <h4 style="color: #701c1c; font-size: 1.4rem;">Polimorfismo</h4>
        <p style="font-size: 0.95rem; color: #666;">Implementação de métodos virtuais para tratamento genérico de diferentes categorias de eventos.</p>
      </div>
      <div style="text-align: center; padding: 30px; border: 1px solid #eee; border-radius: 15px;">
        <h4 style="color: #701c1c; font-size: 1.4rem;">Abstração</h4>
        <p style="font-size: 0.95rem; color: #666;">Classe base <code>Atividade</code> define o contrato essencial para todas as especializações do sistema.</p>
      </div>
      <div style="text-align: center; padding: 30px; border: 1px solid #eee; border-radius: 15px;">
        <h4 style="color: #701c1c; font-size: 1.4rem;">Encapsulamento</h4>
        <p style="font-size: 0.95rem; color: #666;">Controle rigoroso de visibilidade e estado para proteção da integridade dos registros.</p>
      </div>
      <div style="text-align: center; padding: 30px; border: 1px solid #eee; border-radius: 15px;">
        <h4 style="color: #701c1c; font-size: 1.4rem;">Herança</h4>
        <p style="font-size: 0.95rem; color: #666;">Especialização clara para Palestras, Workshops e Hackathons, otimizando o reuso de código.</p>
      </div>
    </div>
  </section>

  <section style="padding: 100px 20px; background: #fafafa; border-top: 1px solid #eee;">
    <h2 style="text-align: center; font-size: 2.8rem; margin-bottom: 60px;">Equipe de Desenvolvimento</h2>
    <div style="display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 30px; max-width: 1100px; margin: 0 auto;">
      <div style="text-align: center; background: #fff; padding: 30px; border-radius: 15px; box-shadow: 0 10px 20px rgba(0,0,0,0.05);">
        <strong style="display: block; font-size: 1.3rem; margin-bottom: 5px;">Alex Lacava</strong>
        <span style="color: #701c1c; font-weight: 800; font-size: 0.85rem; text-transform: uppercase; letter-spacing: 1px;">Product Owner & Back-End</span>
      </div>
      <div style="text-align: center; background: #fff; padding: 30px; border-radius: 15px; box-shadow: 0 10px 20px rgba(0,0,0,0.05);">
        <strong style="display: block; font-size: 1.3rem; margin-bottom: 5px;">Bruno Silva</strong>
        <span style="color: #701c1c; font-weight: 800; font-size: 0.85rem; text-transform: uppercase; letter-spacing: 1px;">Full-Stack Developer</span>
      </div>
      <div style="text-align: center; background: #fff; padding: 30px; border-radius: 15px; box-shadow: 0 10px 20px rgba(0,0,0,0.05);">
        <strong style="display: block; font-size: 1.3rem; margin-bottom: 5px;">Maria Cláudia</strong>
        <span style="color: #701c1c; font-weight: 800; font-size: 0.85rem; text-transform: uppercase; letter-spacing: 1px;">Full-Stack & Doc</span>
      </div>
      <div style="text-align: center; background: #fff; padding: 30px; border-radius: 15px; box-shadow: 0 10px 20px rgba(0,0,0,0.05);">
        <strong style="display: block; font-size: 1.3rem; margin-bottom: 5px;">Wallyson Silva</strong>
        <span style="color: #701c1c; font-weight: 800; font-size: 0.85rem; text-transform: uppercase; letter-spacing: 1px;">Back-End & DBA</span>
      </div>
      <div style="text-align: center; background: #fff; padding: 30px; border-radius: 15px; box-shadow: 0 10px 20px rgba(0,0,0,0.05);">
        <strong style="display: block; font-size: 1.3rem; margin-bottom: 5px;">José Romildo</strong>
        <span style="color: #701c1c; font-weight: 800; font-size: 0.85rem; text-transform: uppercase; letter-spacing: 1px;">Developer</span>
      </div>
    </div>
  </section>

  <footer style="text-align: center; padding: 60px; color: #999; font-size: 1rem; border-top: 1px solid #eee;">
    CIn-UFPE | Centro de Informática | Estrutura de Dados Orientada a Objetos 2026.1
  </footer>

</div>