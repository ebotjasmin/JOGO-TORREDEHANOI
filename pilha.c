#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha *criarPilha(char nome) {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    p->nome = nome;
    p->topo = NULL;
    return p;
}

void destruirPilha(Pilha *p) {
    while (!pilhaVazia(p)) desempilhar(p);
    free(p);
}

int pilhaVazia(Pilha *p) {
    return p->topo == NULL;
}

int topoPilha(Pilha *p) {
    if (pilhaVazia(p)) return -1;
    return p->topo->tamanho;
}

void empilhar(Pilha *p, int tamanho) {
    Disco *d = (Disco *) malloc(sizeof(Disco));
    d->tamanho = tamanho;
    d->prox = p->topo;
    p->topo = d;
}

int desempilhar(Pilha *p) {
    if (pilhaVazia(p)) return -1;
    Disco *aux = p->topo;
    int tamanho = aux->tamanho;
    p->topo = aux->prox;