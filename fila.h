#ifndef FILA_H
#define FILA_H

#include "pilha.h"
#include "movimento.h"

/* ==========================================================
   Fila dinamica (FIFO) usada para "reproduzir" uma sequencia
   de movimentos ja conhecida sobre as hastes.
   ========================================================== */

typedef struct NoFila {
    char origem;
    char destino;
    int disco;
    struct NoFila *prox;
} NoFila;

typedef struct Fila {
    NoFila *inicio;
    NoFila *fim;
} Fila;

Fila *criarFila(void);
void destruirFila(Fila *f);

int filaVazia(Fila *f);
void enfileirar(Fila *f, char origem, char destino, int disco);
int desenfileirar(Fila *f, char *origem, char *destino, int *disco);

/* Converte uma lista de movimentos (Q2) numa fila, preservando a ordem */
Fila *listaParaFila(ListaMovimentos *lista);

/* Consome a fila e aplica cada movimento nas tres hastes, mostrando
   o estado do jogo apos cada passo. 'pausar' controla se o usuario
   precisa apertar ENTER entre os passos (modo interativo). */
void simularMovimentos(Fila *fila, Pilha *a, Pilha *b, Pilha *c, int pausar);

#endif
