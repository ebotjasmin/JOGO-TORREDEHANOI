/* ==========================================================
   Torre de Hanoi - logica do jogo (front-end puro, sem libs)

   As hastes sao representadas como pilhas (arrays onde o
   ULTIMO elemento e sempre o topo), espelhando o mesmo
   comportamento das pilhas dinamicas encadeadas da versao em C.

   O historico de jogadas usa um "cursor" (ponteiro para o
   ultimo movimento aplicado), do mesmo jeito que a lista
   duplamente encadeada da versao em C: permite desfazer/refazer
   sem perder consistencia com o estado atual das hastes.
   ========================================================== */

const CORES_DISCOS = ['--disc-1', '--disc-2', '--disc-3', '--disc-4',
                       '--disc-5', '--disc-6', '--disc-7', '--disc-8'];

let pegs = { A: [], B: [], C: [] };
let discCount = 4;
let historico = [];   // lista de {origem, destino, disco}
let cursor = -1;      // indice do ultimo movimento aplicado (-1 = nenhum)
let pegSelecionada = null;
let resolvendoAuto = false;

const els = {
  board: document.getElementById('board'),
  discCount: document.getElementById('discCount'),
  velocidade: document.getElementById('velocidade'),
  btnNovo: document.getElementById('btnNovo'),
  btnDesfazer: document.getElementById('btnDesfazer'),
  btnRefazer: document.getElementById('btnRefazer'),
  btnAuto: document.getElementById('btnAuto'),
  contador: document.getElementById('contadorMovimentos'),
  minimo: document.getElementById('minimoMovimentos'),
  mensagem: document.getElementById('mensagem'),
};

/* ---------- Estruturas basicas de pilha ---------- */

function pilhaVazia(nome) {
  return pegs[nome].length === 0;
}

function topoPilha(nome) {
  const p = pegs[nome];
  return p.length ? p[p.length - 1] : -1;
}

function movimentoValido(origem, destino) {
  if (pilhaVazia(origem)) return false;
  if (pilhaVazia(destino)) return true;
  return topoPilha(origem) < topoPilha(destino);
}

function moverDiscoFisico(origem, destino) {
  const disco = pegs[origem].pop();
  pegs[destino].push(disco);
  return disco;
}

/* ---------- Historico (desfazer / refazer) ---------- */

function registrarMovimento(origem, destino) {
  if (!movimentoValido(origem, destino)) return false;

  // descarta qualquer "futuro" de refazer, igual a versao em C
  historico = historico.slice(0, cursor + 1);

  const disco = moverDiscoFisico(origem, destino);
  historico.push({ origem, destino, disco });
  cursor = historico.length - 1;
  return true;
}

function desfazer() {
  if (cursor < 0) return false;
  const mov = historico[cursor];
  moverDiscoFisico(mov.destino, mov.origem);
  cursor--;
  return true;
}

function refazer() {
  if (cursor + 1 >= historico.length) return false;
  cursor++;
  const mov = historico[cursor];
  moverDiscoFisico(mov.origem, mov.destino);
  return true;
}

/* ---------- Solucao recursiva (gera lista de movimentos) ---------- */

function hanoiRecursivo(n, origem, destino, auxiliar, lista) {
  if (n === 0) return;
  hanoiRecursivo(n - 1, origem, auxiliar, destino, lista);
  lista.push({ origem, destino, disco: n });
  hanoiRecursivo(n - 1, auxiliar, destino, origem, lista);
}

/* ---------- Jogo / UI ---------- */

function novoJogo() {
  discCount = parseInt(els.discCount.value, 10);
  pegs = { A: [], B: [], C: [] };
  for (let i = discCount; i >= 1; i--) pegs.A.push(i);
  historico = [];
  cursor = -1;
  pegSelecionada = null;
  resolvendoAuto = false;
  els.minimo.textContent = (2 ** discCount - 1).toString();
  mostrarMensagem('');
  render();
}

function mostrarMensagem(texto, tipo) {
  els.mensagem.textContent = texto;
  els.mensagem.className = 'mensagem' + (tipo ? ' ' + tipo : '');
}

function jogoConcluido() {
  return pegs.C.length === discCount;
}

function render() {
  ['A', 'B', 'C'].forEach((nome) => {
    const container = document.getElementById('discs-' + nome);
    container.innerHTML = '';
    pegs[nome].forEach((tamanho) => {
      const div = document.createElement('div');
      div.className = 'disc';
      const largura = 34 + (tamanho - 1) * 16;
      div.style.width = largura + 'px';
      div.style.setProperty('--c', `var(${CORES_DISCOS[(tamanho - 1) % CORES_DISCOS.length]})`);
      div.textContent = tamanho;
      container.appendChild(div);
    });

    document.querySelector(`.peg-column[data-peg="${nome}"]`)
      .classList.toggle('selecionada', pegSelecionada === nome);
  });

  els.contador.textContent = (cursor + 1).toString();
  els.btnDesfazer.disabled = cursor < 0 || resolvendoAuto;
  els.btnRefazer.disabled = cursor + 1 >= historico.length || resolvendoAuto;
  els.btnAuto.disabled = resolvendoAuto;
  els.discCount.disabled = resolvendoAuto;

  if (jogoConcluido() && !resolvendoAuto) {
    mostrarMensagem(`Resolvido em ${cursor + 1} movimentos!`, 'sucesso');
  }
}

function aoClicarHaste(nome) {
  if (resolvendoAuto) return;

  if (pegSelecionada === null) {
    if (pilhaVazia(nome)) {
      mostrarMensagem('Essa haste esta vazia.', 'erro');
      return;
    }
    pegSelecionada = nome;
    mostrarMensagem('');
  } else if (pegSelecionada === nome) {
    pegSelecionada = null;
  } else {
    const ok = registrarMovimento(pegSelecionada, nome);
    if (!ok) mostrarMensagem('Movimento invalido: nao pode colocar disco maior sobre um menor.', 'erro');
    else mostrarMensagem('');
    pegSelecionada = null;
  }
  render();
}

async function resolverAutomaticamente() {
  if (resolvendoAuto) return;

  // recomeça do zero garantindo estado inicial consistente
  pegs = { A: [], B: [], C: [] };
  for (let i = discCount; i >= 1; i--) pegs.A.push(i);
  historico = [];
  cursor = -1;
  pegSelecionada = null;
  resolvendoAuto = true;
  mostrarMensagem('Resolvendo automaticamente...');
  render();

  const movimentos = [];
  hanoiRecursivo(discCount, 'A', 'C', 'B', movimentos);
  const delay = parseInt(els.velocidade.value, 10);

  for (const mov of movimentos) {
    registrarMovimento(mov.origem, mov.destino);
    render();
    await new Promise((r) => setTimeout(r, delay));
  }

  resolvendoAuto = false;
  render();
}

/* ---------- Eventos ---------- */

document.querySelectorAll('.peg-column').forEach((col) => {
  col.tabIndex = 0;
  col.setAttribute('role', 'button');
  const nome = col.dataset.peg;
  col.addEventListener('click', () => aoClicarHaste(nome));
  col.addEventListener('keydown', (e) => {
    if (e.key === 'Enter' || e.key === ' ') {
      e.preventDefault();
      aoClicarHaste(nome);
    }
  });
});

els.btnNovo.addEventListener('click', novoJogo);
els.btnDesfazer.addEventListener('click', () => { desfazer(); mostrarMensagem(''); render(); });
els.btnRefazer.addEventListener('click', () => { refazer(); mostrarMensagem(''); render(); });
els.btnAuto.addEventListener('click', resolverAutomaticamente);
els.discCount.addEventListener('change', novoJogo);

novoJogo();