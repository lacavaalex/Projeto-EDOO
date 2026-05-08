import { useEffect, useState } from 'react';
import { BrowserRouter as Router, Routes, Route, Link, useNavigate } from 'react-router-dom';

const API = '/api';
const CORES = { cin: '#9e1b32', texto: '#1e1e1e', fonte: '"JetBrains Mono", monospace' };

// --- COMPONENTE DE LOGIN/CADASTRO ---
function TelaLogin({ setUsuarioLogado }) {
  const [aba, setAba] = useState('escolha');
  const [form, setForm] = useState({ nome: '', email: '', curso: '', senha: '' });
  const navigate = useNavigate();

  const handleAuth = async (e, tipo) => {
    e.preventDefault();

    if (tipo === 'login' && form.email === 'admin' && form.senha === 'adminadmin') {
      const adminFake = { nome: 'Administrador', email: 'admin', curso: 'CIn' };
      setUsuarioLogado(adminFake);
      localStorage.setItem('sessao_ativa', JSON.stringify(adminFake));
      navigate('/');
      return;
    }

    const rota = tipo === 'cadastro' ? '/api/auth/registrar' : '/api/auth/login';
    
    try {
      const res = await fetch(rota, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(form)
      });

      if (res.ok) {
        const data = await res.json();
        if (tipo === 'cadastro') {
          mostrarAlerta("✅ USUÁRIO_REGISTRADO_COM_SUCESSO");
          setAba('login');
        } else {
          setUsuarioLogado(data);
          localStorage.setItem('sessao_ativa', JSON.stringify(data));
          navigate('/');
        }
      } else {
        mostrarAlerta("❌ ERRO_NA_AUTENTICAÇÃO");
      }
    } catch (err) {
      mostrarAlerta("⚠️ ERRO_DE_CONEXÃO_COM_SERVIDOR");
    }
  };

  const EstiloInput = { padding: '10px', fontFamily: CORES.fonte, border: `1px solid ${CORES.cin}` };

  return (
    <div style={{ maxWidth: '400px', margin: '40px auto', border: `2px solid ${CORES.cin}`, padding: '20px', boxShadow: '8px 8px 0px #000' }}>
      {aba === 'escolha' && (
        <div style={{ display: 'flex', flexDirection: 'column', gap: '15px' }}>
          <h2 style={{ fontSize: '16px' }}>{`> identificar_usuario.sh`}</h2>
          <button onClick={() => setAba('login')} style={{ padding: '15px', cursor: 'pointer', background: CORES.cin, color: '#fff', border: 'none', fontWeight: 'bold', fontFamily: CORES.fonte }}>LOG_IN</button>
          <button onClick={() => setAba('cadastro')} style={{ padding: '15px', cursor: 'pointer', background: '#fff', border: `2px solid ${CORES.cin}`, fontWeight: 'bold', fontFamily: CORES.fonte }}>CADASTRAR_NOVO</button>
        </div>
      )}

      {(aba === 'login' || aba === 'cadastro') && (
        <form onSubmit={(e) => handleAuth(e, aba)} style={{ display: 'flex', flexDirection: 'column', gap: '12px' }}>
          <h2>{aba === 'login' ? '> login.exe' : '> novo_user.conf'}</h2>
          
          {aba === 'cadastro' && (
            <>
              <input 
                placeholder="Nome Completo" 
                onChange={e => setForm({...form, nome: e.target.value})} 
                style={EstiloInput} 
                required 
              />
              <input 
                placeholder="E-mail @cin" 
                type="email" 
                onChange={e => setForm({...form, email: e.target.value})} 
                style={EstiloInput} 
                required 
              />
              <input 
                placeholder="Curso (Ex: Sistemas)" 
                onChange={e => setForm({...form, curso: e.target.value})} 
                style={EstiloInput} 
                required 
              />
              {/* NOVO CAMPO DE SENHA NO CADASTRO */}
              <input 
                placeholder="Crie uma Senha" 
                type="password" 
                onChange={e => setForm({...form, senha: e.target.value})} 
                style={EstiloInput} 
                required 
              />
            </>
          )}

          {aba === 'login' && (
            <>
              <input 
                placeholder="E-mail ou Login" 
                type="text" 
                onChange={e => setForm({...form, email: e.target.value})} 
                style={EstiloInput} 
                required 
              />
              <input 
                placeholder="Senha" 
                type="password" 
                onChange={e => setForm({...form, senha: e.target.value})} 
                style={EstiloInput} 
                required 
              />
            </>
          )}
          
          <button type="submit" style={{ background: CORES.cin, color: '#fff', padding: '10px', border: 'none', cursor: 'pointer', fontFamily: CORES.fonte, fontWeight: 'bold' }}>
            {aba === 'login' ? 'ENTRAR' : 'FINALIZAR_CADASTRO'}
          </button>
          
          <button type="button" onClick={() => setAba('escolha')} style={{ background: 'none', border: 'none', textDecoration: 'underline', fontSize: '12px', cursor: 'pointer', fontFamily: CORES.fonte }}>voltar</button>
        </form>
      )}
    </div>
  );
}

// --- APP PRINCIPAL ---
function App() {
  const [atividades, setAtividades] = useState([]);
  const [usuarioLogado, setUsuarioLogado] = useState(null);
  const [erro, setErro] = useState(null);
  const [tipo, setTipo] = useState('Workshop');
  const [editando, setEditando] = useState(null);
  const [formData, setFormData] = useState({ 
    titulo: '', data: '', data_inicio: '', data_fim: '', 
    horario: '', local: '', duracao: '', vagas: 0, 
    materiais: '', requisitos: '', premiacao: '', 
    tamanho_equipe: 5, palestrante: '', tema: '', edital: '' 
  });
  const [mensagem, setMensagem] = useState("");

  useEffect(() => {
    carregarAtividades();
    const sessao = localStorage.getItem('sessao_ativa');
    if (sessao) setUsuarioLogado(JSON.parse(sessao));
  }, []);

  const carregarAtividades = () => {
    fetch(`${API}/atividades`).then(res => res.json()).then(setAtividades).catch(() => setErro("⚠️ Servidor offline."));
  };

  const handleChange = (e) => {
    let { name, value } = e.target;
    if (name === "data" || name === "data_inicio" || name === "data_fim") {
      value = value.replace(/\D/g, ""); 
      if (value.length > 2 && value.length <= 4) value = `${value.slice(0, 2)}/${value.slice(2)}`;
      else if (value.length > 4) value = `${value.slice(0, 2)}/${value.slice(2, 4)}/${value.slice(4, 8)}`;
      value = value.slice(0, 10);
    }

    if (name === "horario" || name === "duracao") {
      value = value.replace(/\D/g, "");
      if (value.length > 2) value = `${value.slice(0, 2)}:${value.slice(2, 4)}`;
      value = value.slice(0, 5);
    }

    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    const rotas = { 'Workshop': 'cadastrar_workshop', 'Hackathon': 'cadastrar_hackathon', 'Palestra': 'cadastrar_palestra' };
    const payload = { ...formData, vagas: parseInt(formData.vagas), tamanho_equipe: parseInt(formData.tamanho_equipe) };

    fetch(`${API}/${rotas[tipo]}`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload),
    }).then(res => { 
      if (res.ok) { 
        mostrarAlerta("✅ EVENTO_GRAVADO_COM_SUCESSO");
        setTimeout(() => setMensagem(""), 3000);
        carregarAtividades(); 
      } 
    });
  };

  const handleDelete = (id) => {
    if (!window.confirm("Deseja apagar?")) return;
    
    fetch(`${API}/deletar_atividade/${id}`, { 
      method: 'DELETE' 
    }).then(res => { 
      if (res.ok) {
        carregarAtividades();
        setMensagem("🗑️ EVENTO_REMOVIDO_COM_SUCESSO");
        setTimeout(() => setMensagem(""), 3000);
      } else {
        setMensagem("❌ ERRO_AO_REMOVER_EVENTO");
        setTimeout(() => setMensagem(""), 3000);
      }
    }).catch(() => {
      setMensagem("⚠️ SERVIDOR_OFFLINE");
      setTimeout(() => setMensagem(""), 3000);
    });
  };

  const handleUpdate = (id) => {
    const payload = { ...editando };
    
    fetch(`${API}/atualizar_atividade/${id}`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload),
    }).then(res => { 
      if (res.ok) { 
          setEditando(null); 
          carregarAtividades();
          setMensagem("✅ EVENTO_ATUALIZADO_COM_SUCESSO");
        setTimeout(() => setMensagem(""), 3000);
      } else {
        setMensagem("❌ ERRO_AO_ATUALIZAR_EVENTO");
        setTimeout(() => setMensagem(""), 3000); 
        } 
    });
  };

  const logout = () => {
    localStorage.removeItem('sessao_ativa');
    setUsuarioLogado(null);
  };

  const mostrarAlerta = (texto) => {
    setMensagem(texto);
    setTimeout(() => setMensagem(""), 3000);
  };

  const handleInscricaoSimulada = (tituloEvento) => {
    window.alert(`
      Aqui ficaria o redirecionamento para a 
      página detalhada do evento: 
      "${tituloEvento}"

      Clique em OK para continuar.`);
  };

  return (
    <Router>
      <div style={{ padding: '20px', maxWidth: '1100px', margin: '0 auto', fontFamily: CORES.fonte }}>
        <nav style={{ marginBottom: '20px', display: 'flex', justifyContent: 'space-between', borderBottom: `2px solid ${CORES.cin}`, paddingBottom: '10px' }}>
          <div style={{ display: 'flex', gap: '15px' }}>
            <Link to="/" style={{ textDecoration: 'none', color: CORES.cin, fontWeight: 'bold' }}>{`> EVENTOS`}</Link>
            {usuarioLogado?.email === 'admin' && (
              <Link to="/cadastro" style={{ textDecoration: 'none', color: CORES.cin, fontWeight: 'bold' }}>{`> CADASTRAR`}</Link>
            )}
          </div>
          
          {usuarioLogado ? (
            <div style={{ fontSize: '12px' }}>
              <span>{`User: ${usuarioLogado.nome.split(' ')[0]} | `}</span>
              <button onClick={logout} style={{ background: 'none', border: 'none', color: CORES.cin, cursor: 'pointer', fontWeight: 'bold', textDecoration: 'underline' }}>LOGOUT</button>
            </div>
          ) : (
            <Link to="/login" style={{ textDecoration: 'none', color: CORES.cin, fontWeight: 'bold' }}>{`> LOGIN`}</Link>
          )}
        </nav>

        <h1 style={{ color: CORES.cin }}>{`// CIn-Events_`}</h1>

        {mensagem && ( <div style={{ position: 'fixed', top: '20px', right: '20px', background: CORES.cin, color: '#fff', padding: '15px 25px', border: '2px solid #fff', boxShadow: '8px 8px 0px #000', zIndex: 2000, fontFamily: CORES.fonte, fontWeight: 'bold', fontSize: '14px', letterSpacing: '1px' }}> {`> ${mensagem}`}
          </div>
        )}

        <Routes>
          <Route path="/login" element={<TelaLogin setUsuarioLogado={setUsuarioLogado} mostrarAlerta={mostrarAlerta} />} />
          
          <Route path="/" element={
            <div style={{ display: 'grid', gap: '20px', gridTemplateColumns: 'repeat(auto-fill, minmax(300px, 1fr))' }}>
              {atividades.map((atv) => (
                <div key={atv.id} style={{ border: `1px solid ${CORES.cin}`, padding: '15px', boxShadow: `6px 6px 0px ${CORES.cin}`, background: '#fff', display: 'flex', flexDirection: 'column', justifyContent: 'space-between' }}>
                  <div>
                    <span style={{ background: CORES.cin, color: '#fff', padding: '2px 8px', fontSize: '10px', textTransform: 'uppercase', fontWeight: 'bold' }}>{atv.tipo}</span>
                    <h3 style={{ margin: '10px 0 5px 0', borderBottom: '1px solid #eee' }}>{atv.titulo}</h3>
                    <div style={{ fontSize: '14px', marginBottom: '10px' }}>
                      <p style={{ margin: '3px 0' }}><strong>📅 Data do Evento:</strong> {atv.data}</p>
                      <p style={{ margin: '3px 0' }}><strong>🎯 Capacidade:</strong> {atv.vagas} vagas</p>
                    </div>

                    {atv.descricao && (
                      <div style={{ 
                        marginTop: '15px', padding: '15px', background: '#fcfcfc', 
                        border: `1px solid #eee`, borderLeft: `5px solid ${CORES.cin}`,
                        boxShadow: 'inset 2px 2px 5px rgba(0,0,0,0.02)'
                      }}>
                        <span style={{ color: CORES.cin, fontWeight: 'bold', display: 'block', marginBottom: '10px', fontSize: '11px', letterSpacing: '1px' }}>
                          {`// especificacoes_`}
                        </span>
                        
                        <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
                          {atv.descricao.split(' | ').map((info, index) => (
                            <div key={index} style={{ 
                              display: 'flex', alignItems: 'baseline', gap: '10px',
                              fontSize: '14px', color: '#333', borderBottom: '1px dashed #efefef',
                              paddingBottom: '4px'
                            }}>
                              <span style={{ color: CORES.cin, fontWeight: 'bold' }}>►</span>
                              <span>{info}</span>
                            </div>
                          ))}
                        </div>
                      </div>
                    )}
                  </div>

                  <div style={{ marginTop: '20px', display: 'flex', gap: '10px', borderTop: '1px solid #eee', paddingTop: '10px' }}>
                    {usuarioLogado?.email === 'admin' ? (
                      editando?.id === atv.id ? (
                        <div style={{ display: 'flex', flexDirection: 'column', gap: '8px', width: '100%', background: '#f0f0f0', padding: '10px', borderRadius: '4px' }}>
                          <span style={{fontSize: '10px', fontWeight: 'bold'}}>{`// EDITANDO_ID: ${atv.id}`}</span>
                          <input 
                            placeholder="Título"
                            value={editando.titulo} 
                            onChange={e => setEditando({...editando, titulo: e.target.value})} 
                            style={{fontFamily: CORES.fonte, padding: '5px', border: `1px solid ${CORES.cin}`}}
                          />
                          <div style={{ display: 'flex', gap: '5px' }}>
                            <input 
                              placeholder="Data Evento"
                              value={editando.data} 
                              onChange={e => {
                                let val = e.target.value.replace(/\D/g, "");
                                if (val.length > 2 && val.length <= 4) val = `${val.slice(0, 2)}/${val.slice(2)}`;
                                else if (val.length > 4) val = `${val.slice(0, 2)}/${val.slice(2, 4)}/${val.slice(4, 8)}`;
                                setEditando({...editando, data: val.slice(0, 10)});
                              }} 
                              style={{fontFamily: CORES.fonte, padding: '5px', flex: 1}}
                            />
                            <input 
                              type="number" 
                              placeholder="Vagas"
                              value={editando.vagas} 
                              onChange={e => setEditando({...editando, vagas: e.target.value})} 
                              style={{fontFamily: CORES.fonte, padding: '5px', width: '70px'}}
                            />
                          </div>
                          {atv.tipo !== 'Hackathon' && (
                            <input 
                              placeholder="Horário (hh:mm)"
                              value={editando.horario} 
                              onChange={e => {
                                let val = e.target.value.replace(/\D/g, "");
                                if (val.length > 2) val = `${val.slice(0, 2)}:${val.slice(2, 4)}`;
                                setEditando({...editando, horario: val.slice(0, 5)});
                              }} 
                              style={{fontFamily: CORES.fonte, padding: '5px'}}
                            />
                          )}
                          <div style={{ display: 'flex', gap: '5px', marginTop: '5px' }}>
                            <button onClick={() => handleUpdate(atv.id)} style={{ flex: 1, background: 'green', color: 'white', border: 'none', padding: '8px', cursor: 'pointer', fontWeight: 'bold', fontFamily: CORES.fonte }}>SALVAR</button>
                            <button onClick={() => setEditando(null)} style={{ flex: 1, background: '#ccc', border: 'none', padding: '8px', cursor: 'pointer', fontFamily: CORES.fonte }}>CANCELAR</button>
                          </div>
                        </div>
                      ) : (
                        <>
                          <button onClick={() => setEditando({ ...atv })} style={{ background: 'none', border: '1px solid #ccc', cursor: 'pointer', fontFamily: CORES.fonte, padding: '2px 8px' }}>editar</button>
                          <button onClick={() => handleDelete(atv.id)} style={{ background: CORES.cin, color: '#fff', border: 'none', cursor: 'pointer', fontFamily: CORES.fonte, padding: '2px 8px' }}>deletar</button>
                        </>
                      )
                    ) : (
                      usuarioLogado && (
                        <button 
                          onClick={() => handleInscricaoSimulada(atv.titulo)} 
                          style={{ background: '#000', color: '#fff', border: 'none', width: '100%', cursor: 'pointer', fontFamily: CORES.fonte, padding: '10px', fontWeight: 'bold' }}
                        > 
                          INSCREVER-SE
                        </button>
                      )
                    )}
                  </div>
                </div>
              ))}
            </div>
          } />

          <Route path="/cadastro" element={
            usuarioLogado?.email === 'admin' ? (
              <div style={{ maxWidth: '500px' }}>
                <h2 style={{ fontSize: '18px' }}>{`> novo_cadastro.sh`}</h2>
                <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '12px', border: `1px solid ${CORES.cin}`, padding: '20px', boxShadow: `4px 4px 0px ${CORES.cin}` }}>
                  <label style={{ fontSize: '12px' }}>TIPO DE EVENTO:</label>
                  <select value={tipo} onChange={(e) => setTipo(e.target.value)} style={{ padding: '8px', fontFamily: CORES.fonte }}>
                    {['Workshop', 'Hackathon', 'Palestra'].map(t => <option key={t} value={t}>{t}</option>)}
                  </select>

                  <input name="titulo" placeholder="Título do Evento *" onChange={handleChange} required style={{ padding: '8px' }} />
                  <input name="data" placeholder="Data (dd/mm/aaaa) *" value={formData.data} onChange={handleChange} required style={{ padding: '8px' }} />
                  <div style={{ display: 'flex', gap: '10px' }}>
                    <input name="data_inicio" placeholder="Início Inscrições *" value={formData.data_inicio} onChange={handleChange} required style={{ padding: '8px', flex: 1 }} />
                    <input name="data_fim" placeholder="Fim Inscrições *" value={formData.data_fim} onChange={handleChange} required style={{ padding: '8px', flex: 1 }} />
                  </div>
                  
                  {tipo !== 'Hackathon' && (
                    <>
                      <input name="horario" placeholder="Horário (hh:mm) *" value={formData.horario} onChange={handleChange} required style={{ padding: '8px' }} />
                      <input name="local" placeholder="Local *" value={formData.local} onChange={handleChange} required style={{ padding: '8px' }} />
                      <input name="duracao" placeholder="Duração (hh:mm) *" value={formData.duracao} onChange={handleChange} required style={{ padding: '8px' }} />
                    </>
                  )}
                  
                  <input name="vagas" type="number" placeholder="Limite de Vagas *" onChange={handleChange} required style={{ padding: '8px' }} />

                  <div style={{ padding: '10px', background: '#eee', marginTop: '5px' }}>
                    <span style={{ fontSize: '11px', fontWeight: 'bold' }}>DETALHES ESPECÍFICOS:</span>
                    <div style={{ display: 'flex', flexDirection: 'column', gap: '10px', marginTop: '10px' }}>
                      {tipo === 'Workshop' && (
                        <>
                          <input name="materiais" placeholder="Materiais necessários" onChange={handleChange} style={{ padding: '5px' }} />
                          <input name="requisitos" placeholder="Software/Requisitos" onChange={handleChange} style={{ padding: '5px' }} />
                        </>
                      )}
                      {tipo === 'Hackathon' && (
                        <>
                          <input name="premiacao" placeholder="Premiação" onChange={handleChange} style={{ padding: '5px' }} />
                          <input name="tamanho_equipe" type="number" placeholder="Pessoas por equipe" onChange={handleChange} style={{ padding: '5px' }} />
                          <input name="edital" placeholder="Link do Edital (URL)" onChange={handleChange} style={{ padding: '5px' }} />
                        </>
                      )}
                      {tipo === 'Palestra' && (
                        <>
                          <input name="palestrante" placeholder="Nome do Palestrante" onChange={handleChange} style={{ padding: '5px' }} />
                          <input name="tema" placeholder="Tema Principal" onChange={handleChange} style={{ padding: '5px' }} />
                        </>
                      )}
                    </div>
                  </div>
                  <button type="submit" style={{ background: CORES.cin, color: '#fff', border: 'none', padding: '12px', cursor: 'pointer', fontFamily: CORES.fonte, fontWeight: 'bold' }}>EXEC_CADASTRO</button>
                </form>
              </div>
            ) : (
              <div style={{ textAlign: 'center', marginTop: '50px' }}>
                <p>Acesso Restrito: Apenas administradores podem gerenciar eventos.</p>
                <Link to="/">Voltar para Home</Link>
              </div>
            )
          } />
        </Routes>
        {erro && <p style={{ color: 'red', marginTop: '20px' }}>{erro}</p>}
      </div>
    </Router>
  );
}

export default App;