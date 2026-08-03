#ifndef PILHA_H
#define PILHA_H

/* ==========================================================
   Hastes do jogo, representadas como pilhas dinamicas
   (lista encadeada simples, topo = inicio da lista).
   ========================================================== */

typedef struct Disco {
    int tamanho;
    struct Disco *prox;
} Disco;

typedef struct Pilha {
    char nome;      /* 'A', 'B' ou 'C' */
    Disco *topo;
} Pilha;

Pilha *criarPilha(char nome);
void destruirPilha(Pilha *p);

int pilhaVazia(Pilha *p);
int topoPilha(Pilha *p);
void empilhar(Pilha *p, int tamanho);
int desempilhar(Pilha *p);

int movimentoValido(Pilha *origem, Pilha *destino);
void moverDisco(Pilha *origem, Pilha *destino);

void inicializarHaste(Pilha *p, int n);
void imprimirEstado(Pilha *a, Pilha *b, Pilha *c);

/* Retorna a haste (A, B ou C) correspondente ao nome informado */
Pilha *obterHastePorNome(char nome, Pilha *a, Pilha *b, Pilha *c);

/* Verifica se o jogo terminou: todos os n discos estao na haste destino */
int jogoConcluido(Pilha *destino, int n);

#endif