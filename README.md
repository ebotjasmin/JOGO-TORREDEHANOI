Torre de Hanói em C
Implementação da Torre de Hanói em C, usando apenas estruturas de dados

dinâmicas encadeadas (nada de vetores/arrays fixos):
·	Pilhas (lista encadeada simples) para representar as três hastes.
·	Lista encadeada para registrar a sequência de movimentos da solução recursiva.
·	Fila (lista encadeada) para reproduzir/simular uma sequência de movimentos já conhecida.
·	Lista duplamente encadeada para desfazer/refazer jogadas.
Como jogar
make run

Isso compila o projeto e abre um menu:
===== TORRE DE HANOI =====
1. Jogar manualmente
2. Ver solucao automatica
3. Sair

·	Jogar manualmente: escolha a haste de origem e destino a cada jogada.

Comandos extras: d desfaz o último movimento, r refaz.
·	Ver solução automática: calcula a solução ótima recursivamente e

reproduz o jogo passo a passo (com opção de pausar a cada passo).
Estrutura do projeto
hanoi-game/
├── include/
│   ├── pilha.h        # hastes (pilhas dinâmicas de discos)
│   ├── movimento.h     # lista de movimentos + solução recursiva
│   ├── fila.h           # fila para reproduzir movimentos
│   └── historico.h     # lista dupla para desfazer/refazer
├── src/
│   ├── pilha.c
│   ├── movimento.c
│   ├── fila.c
│   ├── historico.c
│   └── main.c           # menu / jogo interativo
├── Makefile
└── README.md

Compilar manualmente
gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -o hanoi
./hanoi

Regras do jogo
1.	Mover apenas um disco por vez.
2.	Sempre mover o disco do topo de uma haste.
3.	Nunca colocar um disco maior sobre um menor.
O número mínimo de movimentos para resolver com n discos é 2^n - 1.
