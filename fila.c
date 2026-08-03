#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila *criarFila(void) {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void destruirFila(Fila *f) {
    NoFila *atual = f->inicio;
    while (atual != NULL) {
        NoFila *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(f);
}

int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

void enfileirar(Fila *f, char origem, char destino, int disco) {
    NoFila *novo = (NoFila *) malloc(sizeof(NoFila));
    novo->origem = origem;
    novo->destino = destino;
    novo->disco = disco;
    novo->prox = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

int desenfileirar(Fila *f, char *origem, char *destino, int *disco) {
    if (filaVazia(f)) return 0;
    NoFila *aux = f->inicio;
    *origem = aux->origem;
    *destino = aux->destino;
    *disco = aux->disco;
    f->inicio = aux->prox;
    if (f->inicio == NULL) f->fim = NULL;
    free(aux);
    return 1;
}

Fila *listaParaFila(ListaMovimentos *lista) {
    Fila *f = criarFila();
    Movimento *atual = lista->inicio;
    while (atual != NULL) {
        enfileirar(f, atual->origem, atual->destino, atual->disco);
        atual = atual->prox;
    }
    return f;
}

void simularMovimentos(Fila *fila, Pilha *a, Pilha *b, Pilha *c, int pausar) {
    char origem, destino;
    int disco;
    int passo = 1;

    while (desenfileirar(fila, &origem, &destino, &disco)) {
        Pilha *pOrigem = obterHastePorNome(origem, a, b, c);
        Pilha *pDestino = obterHastePorNome(destino, a, b, c);

        printf("\nPasso %d: mover disco %d de %c para %c\n", passo, disco, origem, destino);

        if (movimentoValido(pOrigem, pDestino)) {
            moverDisco(pOrigem, pDestino);
        } else {
            printf("  (movimento invalido - ignorado)\n");
        }

        imprimirEstado(a, b, c);

        if (pausar) {
            printf("(ENTER para continuar) ");
            getchar();
        }
        passo++;
    }
}