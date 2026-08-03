#ifndef MOVIMENTO_H
#define MOVIMENTO_H

/* ==========================================================
   Registro de movimentos (lista simplesmente encadeada) e
   solucao recursiva classica da Torre de Hanoi.
   ========================================================== */

typedef struct Movimento {
    char origem;
    char destino;
    int disco;
    struct Movimento *prox;
} Movimento;

typedef struct ListaMovimentos {
    Movimento *inicio;
    Movimento *fim;
} ListaMovimentos;

ListaMovimentos *criarListaMovimentos(void);
void destruirListaMovimentos(ListaMovimentos *lista);

void inserirMovimento(ListaMovimentos *lista, char origem, char destino, int disco);
void imprimirMovimentos(ListaMovimentos *lista);

/* Preenche 'lista' com a sequencia otima de movimentos para resolver
   o Hanoi de n discos, de 'origem' para 'destino', usando 'auxiliar' */
void hanoiRecursivo(int n, char origem, char destino, char auxiliar, ListaMovimentos *lista);

#endif