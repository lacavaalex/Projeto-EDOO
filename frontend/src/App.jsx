import { useEffect, useState } from 'react';

function App() {
  const [atividades, setAtividades] = useState([]);
  const [erro, setErro] = useState(null);

  useEffect(() => {
    fetch('http://localhost:8080/api/atividades')
      .then(res => {
        if (!res.ok) throw new Error("Erro na resposta do servidor");
        return res.json();
      })
      .then(data => setAtividades(data))
      .catch(err => {
        console.error(err);
        setErro("Não foi possível carregar os dados do C++. O servidor está rodando?");
      });
  }, []);

  return (
    <div style={{ padding: '20px', fontFamily: 'sans-serif' }}>
      <h1>Painel CIn-Events</h1>
      <p>Dados vindos do Backend C++:</p>
      
      {erro && <p style={{ color: 'red' }}>{erro}</p>}

      <div style={{ display: 'grid', gap: '15px', marginTop: '20px' }}>
        {atividades.length === 0 && !erro && <p>Carregando atividades...</p>}
        
        {atividades.map((atv, i) => (
          <div key={i} style={{ border: '1px solid #ccc', padding: '15px', borderRadius: '8px', shadow: '2px 2px 5px #eee' }}>
            <strong style={{ color: '#004a99' }}>{atv.tipo}</strong>
            <h2>{atv.titulo}</h2>
            <p>{atv.vagas ? "✅ Vagas Disponíveis" : "❌ Atividade Lotada"}</p>
          </div>
        ))}
      </div>
    </div>
  );
}

export default App;