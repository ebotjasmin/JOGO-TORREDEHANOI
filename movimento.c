#include <stdio.h>
#include <stdlib.h>
#include "movimento.h"

ListaMovimentos *criarListaMovimentos(void) {
    ListaMovimentos *l = (ListaMovimentos *) malloc(sizeof(ListaMovimentos));
    l->inicio = NULL;
    l->fim = NULL;
    return l;
}

void destruirListaMovimentos(ListaMovimentos *lista) {
    Movimento *atual = lista->inicio;
    while (atual != NULL) {
        Movimento *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista);
}

void inserirMovimento(ListaMovimentos *lista, char origem, char destino, int disco) {
    Movimento *m = (Movimento *) malloc(sizeof(Movimento));
    m->origem = origem;
    m->destino = destino;
    m->disco = disco;
    m->prox = NULL;

    if (lista->fim == NULL) {
        lista->inicio = m;
        lista->fim = m;
    } else {
        lista->fim->prox = m;
        lista->fim = m;
    }
}

void imprimirMovimentos(ListaMovimentos *lista) {
    Movimento *atual = lista->inicio;
    int passo = 1;
    while (atual != NULL) {
        printf("  %d) Mover disco %d de %c para %c\n",
               passo, atual->disco, atual->origem, atual->destino);
        atual = atual->prox;
        passo++;
    }
}

void hanoiRecursivo(int n, char origem, char destino, char auxiliar, ListaMovimentos *lista) {
    if (n == 0) return;
    hanoiRecursivo(n - 1, origem, auxiliar, destino, lista);
    inserirMovimento(lista, origem, destino, n);
    hanoiRecursivo(n - 1, auxiliar, destino, origem, lista);
}