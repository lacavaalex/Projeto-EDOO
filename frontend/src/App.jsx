import { useEffect, useState } from 'react';

function App() {
  const [atividades, setAtividades] = useState([]);
  const [erro, setErro] = useState(null);
  

  const [tipo, setTipo] = useState('Workshop');
  const [formData, setFormData] = useState({
    titulo: '', data: '', vagas: 0,
    materiais: '', requisitos: '', 
    area: '', edital: '',          
    bolsa: 0.0, local: '',         
    premiacao: '', tamanho_equipe: 5, 
    palestrante: '', tema: ''      
  });

  const carregarAtividades = () => {
    fetch('http://localhost:8080/api/atividades')
      .then(res => res.json())
      .then(data => setAtividades(data))
      .catch(err => setErro("Servidor C++ offline?"));
  };

  useEffect(() => {
    carregarAtividades();
  }, []);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    

    const rotas = {
      'Workshop': 'cadastrar_workshop',
      'Clube': 'cadastrar_clube',
      'Estagio': 'cadastrar_estagio',
      'Hackathon': 'cadastrar_hackathon',
      'Palestra': 'cadastrar_palestra'
    };


    const payload = {
      ...formData,
      vagas: parseInt(formData.vagas),
      bolsa: parseFloat(formData.bolsa),
      tamanho_equipe: parseInt(formData.tamanho_equipe)
    };

    fetch(`http://localhost:8080/api/${rotas[tipo]}`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload),
    })
    .then(res => {
      if(res.ok) {
        alert(`${tipo} cadastrado com sucesso!`);
        carregarAtividades(); // Atualiza a lista
      }
    })
    .catch(err => alert("Erro ao conectar com o backend"));
  };

  return (
    <div style={{ padding: '30px', fontFamily: 'Segoe UI, sans-serif', backgroundColor: '#f4f7f6', minHeight: '100vh' }}>
      <h1 style={{ color: '#004a99' }}>Painel CIn-Events</h1>
      
      {/* Formulário de Cadastro */}
      <section style={{ backgroundColor: '#fff', padding: '20px', borderRadius: '10px', marginBottom: '30px', boxShadow: '0 4px 6px rgba(0,0,0,0.1)' }}>
        <h3>Nova Oportunidade</h3>
        <form onSubmit={handleSubmit} style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '10px' }}>
          <select value={tipo} onChange={(e) => setTipo(e.target.value)} style={{ gridColumn: 'span 2', padding: '10px' }}>
            <option>Workshop</option>
            <option>Clube</option>
            <option>Estagio</option>
            <option>Hackathon</option>
            <option>Palestra</option>
          </select>

          <input name="titulo" placeholder="Título" onChange={handleChange} required style={inputStyle} />
          <input name="data" placeholder="Data (ex: 20/05)" onChange={handleChange} required style={inputStyle} />
          <input name="vagas" type="number" placeholder="Vagas" onChange={handleChange} required style={inputStyle} />

          {/* Campos Dinâmicos baseados no Tipo */}
          {tipo === 'Workshop' && (
            <>
              <input name="materiais" placeholder="Materiais" onChange={handleChange} style={inputStyle} />
              <input name="requisitos" placeholder="Requisitos" onChange={handleChange} style={inputStyle} />
            </>
          )}
          {tipo === 'Clube' && (
            <>
              <input name="area" placeholder="Área do Clube" onChange={handleChange} style={inputStyle} />
              <input name="edital" placeholder="Link do Edital" onChange={handleChange} style={inputStyle} />
            </>
          )}
          {tipo === 'Estagio' && (
            <>
              <input name="bolsa" type="number" step="0.01" placeholder="Valor da Bolsa" onChange={handleChange} style={inputStyle} />
              <input name="local" placeholder="Empresa/Local" onChange={handleChange} style={inputStyle} />
            </>
          )}
          {tipo === 'Hackathon' && (
            <>
              <input name="premiacao" placeholder="Premiação" onChange={handleChange} style={inputStyle} />
              <input name="tamanho_equipe" type="number" placeholder="Tam. Equipe" onChange={handleChange} style={inputStyle} />
            </>
          )}
          {tipo === 'Palestra' && (
            <>
              <input name="palestrante" placeholder="Nome do Palestrante" onChange={handleChange} style={inputStyle} />
              <input name="tema" placeholder="Tema Central" onChange={handleChange} style={inputStyle} />
            </>
          )}

          <button type="submit" style={{ gridColumn: 'span 2', padding: '12px', backgroundColor: '#004a99', color: 'white', border: 'none', borderRadius: '5px', cursor: 'pointer' }}>
            Cadastrar Oportunidade
          </button>
        </form>
      </section>

      <hr />

      {/* Listagem */}
      <p>Oportunidades Ativas no Banco SQLite:</p>
      {erro && <p style={{ color: 'red' }}>{erro}</p>}

      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(250px, 1fr))', gap: '20px', marginTop: '20px' }}>
        {atividades.map((atv, i) => (
          <div key={i} style={cardStyle}>
            <span style={{ fontSize: '12px', fontWeight: 'bold', color: '#666', textTransform: 'uppercase' }}>{atv.tipo}</span>
            <h2 style={{ margin: '10px 0', color: '#333' }}>{atv.titulo}</h2>
            <p style={{ fontSize: '14px', color: '#555' }}>📅 {atv.data}</p>
            <p style={{ fontWeight: 'bold', color: atv.vagas > 0 ? '#27ae60' : '#e74c3c' }}>
              {atv.vagas > 0 ? `✅ ${atv.vagas} Vagas` : "❌ Esgotado"}
            </p>
          </div>
        ))}
      </div>
    </div>
  );
}

const inputStyle = { padding: '10px', borderRadius: '4px', border: '1px solid #ddd' };
const cardStyle = { backgroundColor: '#fff', padding: '20px', borderRadius: '12px', boxShadow: '0 2px 8px rgba(0,0,0,0.05)', borderLeft: '5px solid #004a99' };

export default App;