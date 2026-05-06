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

  const carregarAtividades = () => {
    fetch(`${API}/atividades`)
      .then(res => res.json())
      .then(data => { setAtividades(data); setErro(null); })
      .catch(() => setErro("⚠️ Servidor offline."));
  };

  useEffect(() => { carregarAtividades(); }, []);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    const rotas = { 'Workshop': 'cadastrar_workshop', 'Clube': 'cadastrar_clube', 'Estagio': 'cadastrar_estagio', 'Hackathon': 'cadastrar_hackathon', 'Palestra': 'cadastrar_palestra' };
    const payload = { ...formData, vagas: parseInt(formData.vagas), bolsa: parseFloat(formData.bolsa), tamanho_equipe: parseInt(formData.tamanho_equipe) };

    fetch(`${API}/${rotas[tipo]}`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload),
    }).then(res => { if (res.ok) { alert("✅ Sucesso!"); carregarAtividades(); } });
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

        <Routes>
          <Route path="/" element={
            <div style={{ display: 'grid', gap: '15px', gridTemplateColumns: 'repeat(auto-fill, minmax(280px, 1fr))' }}>
              {atividades.map((atv) => (
                <div key={atv.id} style={{ border: `1px solid ${CORES.cin}`, padding: '15px', boxShadow: `4px 4px 0px ${CORES.cin}` }}>
                  <span style={{ fontWeight: 'bold', color: CORES.cin, fontSize: '12px' }}>{atv.tipo}</span>
                  <h3>{atv.titulo}</h3>
                  <p>📅 {atv.data} | 🎯 Vagas: {atv.vagas}</p>
                  {editando?.id === atv.id ? (
                    <div style={{ display: 'flex', gap: '5px' }}>
                      <input type="number" value={editando.vagas} onChange={(e) => setEditando({ ...editando, vagas: e.target.value })} style={{ width: '50px' }} />
                      <button onClick={() => handleUpdate(atv.id)}>Salvar</button>
                    </div>
                  ) : (
                    <div style={{ display: 'flex', gap: '8px' }}>
                      <button onClick={() => setEditando({ id: atv.id, vagas: atv.vagas })} style={{fontFamily: CORES.fonte}}>editar</button>
                      <button onClick={() => handleDelete(atv.id)} style={{ background: CORES.cin, color: '#fff', border: 'none', fontFamily: CORES.fonte }}>deletar</button>
                    </div>
                  )}
                </div>
              ))}
            </div>
          } />

          <Route path="/cadastro" element={
            <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '10px', maxWidth: '400px', border: `1px solid #ccc`, padding: '15px' }}>
              <select value={tipo} onChange={(e) => setTipo(e.target.value)} style={{fontFamily: CORES.fonte}}>{['Workshop', 'Clube', 'Estagio', 'Hackathon', 'Palestra'].map(t => <option key={t}>{t}</option>)}</select>
              <input name="titulo" placeholder="Título *" onChange={handleChange} required />
              <input name="data" placeholder="Data *" onChange={handleChange} required />
              <input name="vagas" type="number" placeholder="Vagas *" onChange={handleChange} required />
              {tipo === 'Workshop' && <><input name="materiais" placeholder="Materiais" onChange={handleChange} /><input name="requisitos" placeholder="Software" onChange={handleChange} /></>}
              {tipo === 'Clube' && <><input name="area" placeholder="Área" onChange={handleChange} /><input name="edital" placeholder="Edital" onChange={handleChange} /></>}
              {tipo === 'Estagio' && <><input name="bolsa" type="number" placeholder="Bolsa" onChange={handleChange} /><input name="local" placeholder="Local" onChange={handleChange} /></>}
              {tipo === 'Hackathon' && <><input name="premiacao" placeholder="Prêmio" onChange={handleChange} /><input name="tamanho_equipe" type="number" placeholder="Equipe" onChange={handleChange} /></>}
              {tipo === 'Palestra' && <><input name="palestrante" placeholder="Palestrante" onChange={handleChange} /><input name="tema" placeholder="Tema" onChange={handleChange} /></>}
              <button type="submit" style={{ background: CORES.cin, color: '#fff', border: 'none', padding: '10px', cursor: 'pointer', fontFamily: CORES.fonte }}>./cadastrar.sh</button>
            </form>
          } />
        </Routes>
        {erro && <p style={{ color: 'red' }}>{erro}</p>}
      </div>
    </Router>
  );
}

export default App;