#ifndef HISTORICO_H
#define HISTORICO_H

#include "pilha.h"

/* ==========================================================
   Lista duplamente encadeada para desfazer/refazer jogadas.

   O ponteiro 'cursor' sempre aponta para o ultimo movimento
   que esta de fato refletido no estado atual das hastes.
   Isso garante consistencia entre a lista e as pilhas: ver
   comentario detalhado em historico.c.
   ========================================================== */

typedef struct NoDuplo {
    char origem;
    char destino;
    int disco;
    struct NoDuplo *ant;
    struct NoDuplo *prox;
} NoDuplo;

typedef struct ListaDupla {
    NoDuplo *inicio;
    NoDuplo *fim;
    NoDuplo *cursor;   /* NULL = nenhum movimento aplicado ainda */
} ListaDupla;

ListaDupla *criarListaDupla(void);
void destruirListaDupla(ListaDupla *lista);

/* Valida, executa e registra um novo movimento. Retorna 1 se aplicado,
   0 se o movimento era invalido (nada e alterado). Descarta qualquer
   historico de "refazer" que existisse. */
int registrarMovimento(ListaDupla *lista, char origem, char destino,
                        Pilha *a, Pilha *b, Pilha *c);

/* Desfaz o ultimo movimento aplicado. Retorna 0 se nao havia nada a desfazer. */
int desfazer(ListaDupla *lista, Pilha *a, Pilha *b, Pilha *c);

/* Refaz o proximo movimento desfeito. Retorna 0 se nao havia nada a refazer. */
int refazer(ListaDupla *lista, Pilha *a, Pilha *b, Pilha *c);

/* Conta quantos movimentos estao aplicados no momento (posicao do cursor) */
int totalMovimentosAplicados(ListaDupla *lista);

#endif