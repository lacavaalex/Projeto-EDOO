import { useEffect, useState } from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';

const API = '/api';
const CORES = { cin: '#9e1b32', texto: '#1e1e1e', fonte: '"JetBrains Mono", monospace' };

function App() {
  const [atividades, setAtividades] = useState([]);
  const [erro, setErro] = useState(null);
  const [tipo, setTipo] = useState('Workshop');
  const [editando, setEditando] = useState(null);
  const [formData, setFormData] = useState({
    titulo: '', data: '', vagas: 0, materiais: '', requisitos: '',
    area: '', edital: '', bolsa: 0.0, local: '', premiacao: '',
    tamanho_equipe: 5, palestrante: '', tema: ''
  });
  const [mensagem, setMensagem] = useState("");

  const carregarAtividades = () => {
    fetch(`${API}/atividades`)
      .then(res => res.json())
      .then(data => { setAtividades(data); setErro(null); })
      .catch(() => setErro("⚠️ Servidor offline."));
  };

  useEffect(() => { carregarAtividades(); }, []);

  const handleChange = (e) => {
  let { name, value } = e.target;

  if (name === "data") {
    value = value.replace(/\D/g, ""); 

    if (value.length > 2 && value.length <= 4) {
      value = `${value.slice(0, 2)}/${value.slice(2)}`;
    } 
    else if (value.length > 4) {
      value = `${value.slice(0, 2)}/${value.slice(2, 4)}/${value.slice(4, 8)}`;
    }

    value = value.slice(0, 10);
  }

  setFormData(prev => ({ ...prev, [name]: value }));
};

  const handleSubmit = (e) => {
    e.preventDefault();
    const rotas = { 'Workshop': 'cadastrar_workshop', 'Hackathon': 'cadastrar_hackathon', 'Palestra': 'cadastrar_palestra' };
    const payload = { ...formData, vagas: parseInt(formData.vagas), bolsa: parseFloat(formData.bolsa), tamanho_equipe: parseInt(formData.tamanho_equipe) };

    fetch(`${API}/${rotas[tipo]}`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload),
    }).then(res => { 
      if (res.ok) { 
        setMensagem("✅ EVENTO_GRAVADO_COM_SUCESSO");
        setTimeout(() => setMensagem(""), 3000);
        carregarAtividades(); 
      } 
    });
  };

  const handleDelete = (id) => {
    if (!window.confirm("Deseja apagar?")) return;
    fetch(`${API}/deletar_atividade/${id}`, { method: 'DELETE' }).then(res => { if (res.ok) carregarAtividades(); });
  };

  const handleUpdate = (id) => {
    fetch(`${API}/atualizar_atividade/${id}`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ vagas: parseInt(editando.vagas) }),
    }).then(res => { if (res.ok) { setEditando(null); carregarAtividades(); } });
  };

  return (
    <Router>
      <div style={{ padding: '20px', maxWidth: '1100px', margin: '0 auto', fontFamily: CORES.fonte }}>
        <nav style={{ marginBottom: '20px', display: 'flex', gap: '15px', borderBottom: `2px solid ${CORES.cin}`, paddingBottom: '10px' }}>
          <Link to="/" style={{ textDecoration: 'none', color: CORES.cin, fontWeight: 'bold' }}>{`> EVENTOS`}</Link>
          <Link to="/cadastro" style={{ textDecoration: 'none', color: CORES.cin, fontWeight: 'bold' }}>{`> CADASTRAR`}</Link>
        </nav>

        <h1 style={{ color: CORES.cin }}>{`// CIn-Events_`}</h1>

        {mensagem && (
          <div style={{ 
            position: 'fixed', 
            top: '20px', 
            right: '20px', 
            background: CORES.cin, 
            color: '#fff', 
            padding: '15px', 
            border: '2px solid #fff',
            boxShadow: '4px 4px 0px #000',
            zIndex: 1000 
          }}>
            {mensagem}
          </div>
        )}

        <Routes>
          <Route path="/" element={
            <div style={{ display: 'grid', gap: '20px', gridTemplateColumns: 'repeat(auto-fill, minmax(300px, 1fr))' }}>
              {atividades.map((atv) => (
                <div key={atv.id} style={{ 
                  border: `1px solid ${CORES.cin}`, 
                  padding: '15px', 
                  boxShadow: `6px 6px 0px ${CORES.cin}`,
                  background: '#fff',
                  display: 'flex',
                  flexDirection: 'column',
                  justifyContent: 'space-between'
                }}>
                  <div>
                    <span style={{ 
                      background: CORES.cin, 
                      color: '#fff', 
                      padding: '2px 8px', 
                      fontSize: '10px', 
                      textTransform: 'uppercase',
                      fontWeight: 'bold' 
                    }}>{atv.tipo}</span>
                    
                    <h3 style={{ margin: '10px 0 5px 0', borderBottom: '1px solid #eee' }}>{atv.titulo}</h3>
                    
                    <div style={{ fontSize: '14px', marginBottom: '10px' }}>
                      <p style={{ margin: '3px 0' }}><strong>📅 Data:</strong> {atv.data}</p>
                      <p style={{ margin: '3px 0' }}><strong>🎯 Capacidade:</strong> {atv.vagas} vagas</p>
                    </div>

                    {/* SEÇÃO DE DETALHES COMPLETOS (Vem do getDescricaoExtra do C++) */}
                    {atv.descricao && (
                      <div style={{ 
                        marginTop: '10px', 
                        padding: '10px', 
                        background: '#f9f9f9', 
                        borderLeft: `3px solid ${CORES.cin}`,
                        fontSize: '13px'
                      }}>
                        <span style={{ color: '#888', fontWeight: 'bold', display: 'block', marginBottom: '5px' }}>
                          {`// especificacoes_`}
                        </span>
                        <p style={{ margin: 0, whiteSpace: 'pre-wrap', color: '#333', lineHeight: '1.4' }}>
                          {atv.descricao}
                        </p>
                      </div>
                    )}
                  </div>

                  <div style={{ marginTop: '20px', display: 'flex', gap: '10px', borderTop: '1px solid #eee', paddingTop: '10px' }}>
                    {editando?.id === atv.id ? (
                      <>
                        <input 
                          type="number" 
                          value={editando.vagas} 
                          onChange={(e) => setEditando({ ...editando, vagas: e.target.value })} 
                          style={{ width: '60px', fontFamily: CORES.fonte }} 
                        />
                        <button onClick={() => handleUpdate(atv.id)} style={{ cursor: 'pointer' }}>salvar</button>
                        <button onClick={() => setEditando(null)} style={{ cursor: 'pointer' }}>cancelar</button>
                      </>
                    ) : (
                      <>
                        <button 
                          onClick={() => setEditando({ id: atv.id, vagas: atv.vagas })} 
                          style={{ background: 'none', border: '1px solid #ccc', cursor: 'pointer', fontFamily: CORES.fonte, padding: '2px 8px' }}
                        >
                          editar
                        </button>
                        <button 
                          onClick={() => handleDelete(atv.id)} 
                          style={{ background: CORES.cin, color: '#fff', border: 'none', cursor: 'pointer', fontFamily: CORES.fonte, padding: '2px 8px' }}
                        >
                          deletar
                        </button>
                      </>
                    )}
                  </div>
                </div>
              ))}
            </div>
          } />

          <Route path="/cadastro" element={
            <div style={{ maxWidth: '500px' }}>
              <h2 style={{ fontSize: '18px' }}>{`> novo_cadastro.sh`}</h2>
              <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '12px', border: `1px solid ${CORES.cin}`, padding: '20px', boxShadow: `4px 4px 0px ${CORES.cin}` }}>
                <label style={{ fontSize: '12px' }}>TIPO DE EVENTO:</label>
                <select value={tipo} onChange={(e) => setTipo(e.target.value)} style={{ padding: '8px', fontFamily: CORES.fonte }}>
                  {['Workshop', 'Hackathon', 'Palestra'].map(t => <option key={t} value={t}>{t}</option>)}
                </select>

                <input name="titulo" placeholder="Título do Evento *" onChange={handleChange} required style={{ padding: '8px' }} />
                <input name="data" placeholder="Data (dd/mm/aaaa) *" value={formData.data} onChange={handleChange} required style={{ padding: '8px' }} />
                <input name="vagas" type="number" placeholder="Limite de Vagas *" onChange={handleChange} required style={{ padding: '8px' }} />

                <div style={{ padding: '10px', background: '#eee', marginTop: '5px' }}>
                   <span style={{ fontSize: '11px', fontWeight: 'bold' }}>DETALHES ESPECÍFICOS DE {tipo.toUpperCase()}:</span>
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

                <button type="submit" style={{ background: CORES.cin, color: '#fff', border: 'none', padding: '12px', cursor: 'pointer', fontFamily: CORES.fonte, fontWeight: 'bold', marginTop: '10px' }}>
                  EXEC_CADASTRAR
                </button>
              </form>
            </div>
          } />
        </Routes>
        {erro && <p style={{ color: 'red', marginTop: '20px' }}>{erro}</p>}
      </div>
    </Router>
  );
}

export default App;