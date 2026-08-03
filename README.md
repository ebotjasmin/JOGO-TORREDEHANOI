Torre de Hanói - Interface Web
Versão jogável no navegador, feita com HTML + CSS + JavaScript puro

(sem frameworks) e um servidor Node.js minimalista (sem dependências

externas) só pra servir os arquivos.
Como rodar
cd web
node server.js

Depois abra http://localhost:3000 no navegador.
Ou, se preferir usar o npm:
cd web
npm start

Como jogar
·	Clique numa haste para selecionar (pega o disco do topo).
·	Clique em outra haste para soltar o disco lá.
·	Clique na mesma haste de novo para cancelar a seleção.
·	Desfazer / Refazer: voltam e avançam movimentos, iguais aos da

versão em C (lista duplamente encadeada / cursor de histórico).
·	Resolver automaticamente: calcula a solução ótima recursivamente

e anima a resolução, movimento a movimento (dá pra ajustar a velocidade).
Estrutura
web/
├── server.js         # servidor estatico (http + fs, sem dependencias)
├── package.json
└── public/
    ├── index.html
    ├── style.css     # identidade visual (brinquedo de madeira / discos)
    └── script.js     # logica do jogo (pilhas, historico, solucao recursiva)

Sobre a lógica em JavaScript
O script.js espelha a mesma lógica de estruturas de dados da versão em C:
·	Cada haste é uma pilha (array onde o último elemento é o topo,

usando push/pop, exatamente como a pilha encadeada em C).
·	O histórico de jogadas usa um cursor apontando pro último

movimento aplicado — o mesmo mecanismo da lista duplamente encadeada

da Questão 4 do trabalho original — o que permite desfazer/refazer

com consistência garantida.
·	A solução automática usa a mesma recursão clássica (hanoiRecursivo)

da Questão 2.
Deploy (opcional)
Como é só HTML/CSS/JS estático + um servidor Node bem simples, dá pra

publicar de graça em serviços como Vercel, Netlify ou

GitHub Pages (nesse último caso, só a pasta public/, já que o

GitHub Pages não roda o server.js — mas o jogo funciona 100% no

navegador sem precisar de backend, o server.js é só conveniência

pra rodar local).
