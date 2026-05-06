import { useEffect, useState } from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';

const API = '/api';

function ListaEventos({ atividades, erro, setEditando, editando, handleUpdate, handleDelete }) {
  return (
    <div>
      <h3>Oportunidades Cadastradas ({atividades.length})</h3>
      {erro && <p style={{ color: 'red' }}>{erro}</p>}
      <div style={{ display: 'grid', gap: '15px', gridTemplateColumns: 'repeat(auto-fill, minmax(280px, 1fr))' }}>
        {atividades.map((atv) => (
          <div key={atv.id} style={{ border: '1px solid #ccc', padding: '15px', borderRadius: '8px', background: '#fafafa' }}>
            <span style={{ fontWeight: 'bold', color: '#004a99', fontSize: '12px' }}>{atv.tipo}</span>
            <h3 style={{ margin: '5px 0' }}>{atv.titulo}</h3>
            <p>📅 {atv.data} | 🎯 Vagas: {atv.vagas}</p>
            {editando?.id === atv.id ? (
              <div style={{ display: 'flex', gap: '8px' }}>
                <input type="number" value={editando.vagas} onChange={(e) => setEditando({ ...editando, vagas: e.target.value })} style={{ width: '60px' }} />
                <button onClick={() => handleUpdate(atv.id)}>Salvar</button>
                <button onClick={() => setEditando(null)}>Sair</button>
              </div>
            ) : (
              <div style={{ display: 'flex', gap: '8px' }}>
                <button onClick={() => setEditando({ id: atv.id, vagas: atv.vagas })}>✏️ Editar</button>
                <button onClick={() => handleDelete(atv.id)} style={{ background: '#dc3545', color: '#fff' }}>🗑️ Deletar</button>
              </div>
            )}
          </div>
        ))}
      </div>
    </div>
  );
}

function FormCadastro({ handleSubmit, tipo, setTipo, handleChange }) {
  return (
    <section style={{ border: '1px solid #ccc', padding: '15px', borderRadius: '8px' }}>
      <h3>Novo Cadastro</h3>
      <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '10px', maxWidth: '400px' }}>
        <select value={tipo} onChange={(e) => setTipo(e.target.value)}>
          <option>Workshop</option><option>Clube</option><option>Estagio</option><option>Hackathon</option><option>Palestra</option>
        </select>
        <input name="titulo" placeholder="Título *" onChange={handleChange} required />
        <input name="data" placeholder="Data *" onChange={handleChange} required />
        <input name="vagas" type="number" placeholder="Vagas *" onChange={handleChange} required />
        
        {tipo === 'Palestra' && <><input name="palestrante" placeholder="Palestrante" onChange={handleChange} /><input name="tema" placeholder="Tema" onChange={handleChange} /></>}
        {tipo === 'Workshop' && <><input name="materiais" placeholder="Materiais" onChange={handleChange} /><input name="requisitos" placeholder="Requisitos" onChange={handleChange} /></>}
        
        <button type="submit" style={{ padding: '10px', background: '#004a99', color: '#fff', cursor: 'pointer' }}>Cadastrar</button>
      </form>
    </section>
  );
}

function App() {
  const [atividades, setAtividades] = useState([]);
  const [erro, setErro] = useState(null);
  const [tipo, setTipo] = useState('Workshop');
  const [editando, setEditando] = useState(null);
  const [formData, setFormData] = useState({ titulo: '', data: '', vagas: 0, palestrante: '', tema: '', materiais: '', requisitos: '' });

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
    const rotas = { 'Workshop': 'cadastrar_workshop', 'Palestra': 'cadastrar_palestra', 'Hackathon': 'cadastrar_hackathon', 'Clube': 'cadastrar_clube', 'Estagio': 'cadastrar_estagio' };
    fetch(`${API}/${rotas[tipo]}`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ ...formData, vagas: parseInt(formData.vagas) }),
    }).then(res => {
      if (res.ok) { alert("✅ Cadastrado!"); carregarAtividades(); }
    });
  };

  const handleDelete = (id) => {
    if (!window.confirm("Apagar?")) return;
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
      <div style={{ padding: '20px', maxWidth: '1100px', margin: '0 auto' }}>
        <nav style={{ marginBottom: '20px', display: 'flex', gap: '20px' }}>
          <Link to="/" style={{ textDecoration: 'none', color: '#004a99', fontWeight: 'bold' }}>🏠 Ver Eventos</Link>
          <Link to="/cadastro" style={{ textDecoration: 'none', color: '#004a99', fontWeight: 'bold' }}>➕ Cadastrar Novo</Link>
        </nav>

        <h1>Painel CIn-Events</h1>

        <Routes>
          <Route path="/" element={
            <ListaEventos 
              atividades={atividades} erro={erro} 
              editando={editando} setEditando={setEditando} 
              handleUpdate={handleUpdate} handleDelete={handleDelete} 
            />
          } />
          <Route path="/cadastro" element={
            <FormCadastro 
              handleSubmit={handleSubmit} tipo={tipo} 
              setTipo={setTipo} handleChange={handleChange} 
            />
          } />
        </Routes>
      </div>
    </Router>
  );
}

export default App;