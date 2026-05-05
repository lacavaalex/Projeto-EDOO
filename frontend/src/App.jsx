import { useEffect, useState } from 'react';

const API = '/api';

function App() {
  const [atividades, setAtividades] = useState([]);
  const [erro, setErro] = useState(null);
  const [tipo, setTipo] = useState('Workshop');
  const [editando, setEditando] = useState(null); // { id, vagas }
  const [formData, setFormData] = useState({
    titulo: '', data: '', vagas: 0,
    materiais: '', requisitos: '',
    area: '', edital: '',
    bolsa: 0.0, local: '',
    premiacao: '', tamanho_equipe: 5,
    palestrante: '', tema: ''
  });

  const carregarAtividades = () => {
    fetch(`${API}/atividades`)
      .then(res => res.json())
      .then(data => { setAtividades(data); setErro(null); })
      .catch(() => setErro("⚠️ Servidor offline. Compile e rode o C++ primeiro."));
  };

  useEffect(() => { carregarAtividades(); }, []);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    const rotas = {
      'Workshop': 'cadastrar_workshop', 'Clube': 'cadastrar_clube',
      'Estagio': 'cadastrar_estagio',   'Hackathon': 'cadastrar_hackathon',
      'Palestra': 'cadastrar_palestra'
    };
    const payload = {
      ...formData,
      vagas: parseInt(formData.vagas) || 0,
      bolsa: parseFloat(formData.bolsa) || 0.0,
      tamanho_equipe: parseInt(formData.tamanho_equipe) || 5
    };

    fetch(`${API}/${rotas[tipo]}`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload),
    })
    .then(res => {
      if (res.ok) {
        alert("✅ Oportunidade cadastrada com sucesso!");
        carregarAtividades();
      } else {
        alert("❌ Erro no cadastro (Código: " + res.status + ")");
      }
    })
    .catch(() => alert("❌ Falha de conexão. Verifique se o C++ está rodando."));
  };

  const handleDelete = (id) => {
    if (!window.confirm("Deseja realmente apagar esta oportunidade?")) return;
    fetch(`${API}/deletar_atividade/${id}`, { method: 'DELETE' })
      .then(res => {
        if (res.ok) carregarAtividades();
        else alert("❌ Erro ao excluir.");
      })
      .catch(() => alert("❌ Falha de conexão."));
  };

  const handleUpdate = (id) => {
    const novasVagas = parseInt(editando.vagas);
    if (isNaN(novasVagas) || novasVagas < 0) {
      alert("Número de vagas inválido.");
      return;
    }
    fetch(`${API}/atualizar_atividade/${id}`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ vagas: novasVagas }),
    })
    .then(res => {
      if (res.ok) {
        alert("✅ Vagas atualizadas!");
        setEditando(null);
        carregarAtividades();
      } else {
        alert("❌ Erro ao atualizar.");
      }
    })
    .catch(() => alert("❌ Falha de conexão."));
  };

  return (
    <div style={{ padding: '20px', fontFamily: 'sans-serif', maxWidth: '1100px', margin: '0 auto' }}>
      <h1>Painel CIn-Events</h1>

      {/* Formulário de cadastro */}
      <section style={{ border: '1px solid #ccc', padding: '15px', marginBottom: '20px', borderRadius: '8px' }}>
        <h3>Nova Oportunidade</h3>
        <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '10px', maxWidth: '400px' }}>
          <select value={tipo} onChange={(e) => setTipo(e.target.value)}>
            <option>Workshop</option>
            <option>Clube</option>
            <option>Estagio</option>
            <option>Hackathon</option>
            <option>Palestra</option>
          </select>

          <input name="titulo" placeholder="Título *" onChange={handleChange} required />
          <input name="data"   placeholder="Data (ex: 20/05/2026) *" onChange={handleChange} required />
          <input name="vagas"  type="number" placeholder="Vagas *" onChange={handleChange} required />

          {tipo === 'Workshop'  && (<><input name="materiais"  placeholder="Materiais" onChange={handleChange} /><input name="requisitos" placeholder="Requisitos de Software" onChange={handleChange} /></>)}
          {tipo === 'Clube'     && (<><input name="area"       placeholder="Área de Estudo" onChange={handleChange} /><input name="edital" placeholder="Link do Edital" onChange={handleChange} /></>)}
          {tipo === 'Estagio'   && (<><input name="bolsa"      type="number" step="0.01" placeholder="Bolsa R$" onChange={handleChange} /><input name="local" placeholder="Empresa/Local" onChange={handleChange} /></>)}
          {tipo === 'Hackathon' && (<><input name="premiacao"  placeholder="Premiação" onChange={handleChange} /><input name="tamanho_equipe" type="number" placeholder="Tamanho da Equipe" onChange={handleChange} /></>)}
          {tipo === 'Palestra'  && (<><input name="palestrante" placeholder="Palestrante" onChange={handleChange} /><input name="tema" placeholder="Tema" onChange={handleChange} /></>)}

          <button type="submit" style={{ padding: '10px', background: '#004a99', color: '#fff', border: 'none', cursor: 'pointer', borderRadius: '5px' }}>
            Cadastrar
          </button>
        </form>
      </section>

      {/* Mensagem de erro de conexão */}
      {erro && (
        <p style={{ color: 'red', background: '#fff0f0', padding: '10px', borderRadius: '5px', border: '1px solid red' }}>
          {erro}
        </p>
      )}

      {/* Lista de atividades */}
      <h3>Oportunidades Cadastradas ({atividades.length})</h3>
      {atividades.length === 0 && !erro && (
        <p style={{ color: '#888' }}>Nenhuma oportunidade cadastrada ainda.</p>
      )}

      <div style={{ display: 'grid', gap: '15px', gridTemplateColumns: 'repeat(auto-fill, minmax(280px, 1fr))' }}>
        {atividades.map((atv) => (
          <div key={atv.id} style={{ border: '1px solid #ccc', padding: '15px', borderRadius: '8px', background: '#fafafa' }}>
            <span style={{ fontWeight: 'bold', color: '#004a99', fontSize: '12px', textTransform: 'uppercase' }}>
              {atv.tipo}
            </span>
            <h3 style={{ margin: '5px 0' }}>{atv.titulo}</h3>
            <p style={{ margin: '4px 0', color: '#555' }}>📅 {atv.data}</p>
            <p style={{ margin: '4px 0', color: '#555' }}>🎯 Vagas: {atv.vagas}</p>
            {atv.descricao && (
              <p style={{ margin: '4px 0', color: '#777', fontSize: '13px' }}>📝 {atv.descricao}</p>
            )}

            {/* Modo de edição de vagas */}
            {editando?.id === atv.id ? (
              <div style={{ marginTop: '10px', display: 'flex', gap: '8px', alignItems: 'center' }}>
                <input
                  type="number"
                  value={editando.vagas}
                  onChange={(e) => setEditando({ ...editando, vagas: e.target.value })}
                  style={{ width: '70px', padding: '4px' }}
                />
                <button onClick={() => handleUpdate(atv.id)}
                  style={{ background: '#28a745', color: '#fff', border: 'none', padding: '5px 10px', cursor: 'pointer', borderRadius: '4px' }}>
                  Salvar
                </button>
                <button onClick={() => setEditando(null)}
                  style={{ background: '#6c757d', color: '#fff', border: 'none', padding: '5px 10px', cursor: 'pointer', borderRadius: '4px' }}>
                  Cancelar
                </button>
              </div>
            ) : (
              <div style={{ marginTop: '10px', display: 'flex', gap: '8px' }}>
                <button onClick={() => setEditando({ id: atv.id, vagas: atv.vagas })}
                  style={{ background: '#ffc107', color: '#000', border: 'none', padding: '5px 10px', cursor: 'pointer', borderRadius: '4px' }}>
                  ✏️ Editar vagas
                </button>
                <button onClick={() => handleDelete(atv.id)}
                  style={{ background: '#dc3545', color: '#fff', border: 'none', padding: '5px 10px', cursor: 'pointer', borderRadius: '4px' }}>
                  🗑️ Deletar
                </button>
              </div>
            )}
          </div>
        ))}
      </div>
    </div>
  );
}

export default App;