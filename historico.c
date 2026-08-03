#include <stdio.h>
#include <stdlib.h>
#include "historico.h"

ListaDupla *criarListaDupla(void) {
    ListaDupla *l = (ListaDupla *) malloc(sizeof(ListaDupla));
    l->inicio = NULL;
    l->fim = NULL;
    l->cursor = NULL;
    return l;
}

void destruirListaDupla(ListaDupla *lista) {
    NoDuplo *atual = lista->inicio;
    while (atual != NULL) {
        NoDuplo *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista);
}

/* Remove e libera todos os nos apos o cursor (descarta "futuro" de refazer) */
static void descartarFuturo(ListaDupla *lista) {
    NoDuplo *inicioDescarte = (lista->cursor == NULL) ? lista->inicio : lista->cursor->prox;
    NoDuplo *atual = inicioDescarte;
    while (atual != NULL) {
        NoDuplo *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    if (lista->cursor == NULL) {
        lista->inicio = NULL;
    } else {
        lista->cursor->prox = NULL;
    }
    lista->fim = lista->cursor;