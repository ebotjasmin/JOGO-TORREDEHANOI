#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pilha.h"
#include "movimento.h"
#include "fila.h"
#include "historico.h"

static void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static int lerInteiro(const char *prompt, int minimo, int maximo) {
    int valor;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &valor) == 1 && valor >= minimo && valor <= maximo) {
            limparBufferEntrada();
            return valor;
        }
        limparBufferEntrada();
        printf("  Valor invalido, tente novamente.\n");
    }
}

static char lerHaste(const char *prompt) {
    char c;
    while (1) {
        printf("%s", prompt);
        scanf(" %c", &c);
        limparBufferEntrada();
        c = (char) toupper((unsigned char) c);
        if (c == 'A' || c == 'B' || c == 'C') return c;
        printf("  Haste invalida, use A, B ou C.\n");
    }
}

static void jogarManual(int n) {
    Pilha *a = criarPilha('A');
    Pilha *b = criarPilha('B');
    Pilha *c = criarPilha('C');
    inicializarHaste(a, n);
    ListaDupla *hist = criarListaDupla();

    printf("\nObjetivo: mover todos os %d discos da haste A para a haste C.\n", n);
    printf("Comandos: 'd' desfazer, 'r' refazer, 'q' sair para o menu.\n\n");

    while (!jogoConcluido(c, n)) {
        imprimirEstado(a, b, c);
        printf("Movimentos aplicados: %d\n", totalMovimentosAplicados(hist));

        printf("\nOrigem (A/B/C), 'd', 'r' ou 'q': ");
        char entrada;
        scanf(" %c", &entrada);
        limparBufferEntrada();
        entrada = (char) toupper((unsigned char) entrada);

        if (entrada == 'Q') {
            break;
        } else if (entrada == 'D') {
            if (!desfazer(hist, a, b, c)) printf("  Nada para desfazer.\n");
        } else if (entrada == 'R') {
            if (!refazer(hist, a, b, c)) printf("  Nada para refazer.\n");
        } else if (entrada == 'A' || entrada == 'B' || entrada == 'C') {
            char destino = lerHaste("Destino (A/B/C): ");
            if (!registrarMovimento(hist, entrada, destino, a, b, c)) {
                printf("  Movimento invalido!\n");
            }
        } else {
            printf("  Comando nao reconhecido.\n");
        }
        printf("\n");
    }

    if (jogoConcluido(c, n)) {
        printf("Parabens! Voce resolveu a Torre de Hanoi em %d movimentos.\n",
               totalMovimentosAplicados(hist));
    }

    destruirListaDupla(hist);
    destruirPilha(a);
    destruirPilha(b);
    destruirPilha(c);
}

static void resolverAutomaticamente(int n) {
    Pilha *a = criarPilha('A');
    Pilha *b = criarPilha('B');
    Pilha *c = criarPilha('C');
    inicializarHaste(a, n);

    ListaMovimentos *movs = criarListaMovimentos();
    hanoiRecursivo(n, 'A', 'C', 'B', movs);

    printf("\nSolucao otima (%d movimentos):\n", (1 << n) - 1);
    imprimirMovimentos(movs);

    int pausar = lerInteiro("\nPausar a cada passo? (1=sim, 0=nao): ", 0, 1);

    Fila *fila = listaParaFila(movs);
    simularMovimentos(fila, a, b, c, pausar);

    printf("\nResolvido!\n");

    destruirFila(fila);
    destruirListaMovimentos(movs);
    destruirPilha(a);
    destruirPilha(b);
    destruirPilha(c);
}

static void exibirMenu(void) {
    printf("\n===== TORRE DE HANOI =====\n");
    printf("1. Jogar manualmente\n");
    printf("2. Ver solucao automatica\n");
    printf("3. Sair\n");
}

int main(void) {
    int opcao;
    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ", 1, 3);

        if (opcao == 1 || opcao == 2) {
            int n = lerInteiro("Quantos discos (2 a 10)? ", 2, 10);
            if (opcao == 1) jogarManual(n);
            else resolverAutomaticamente(n);
        }
    } while (opcao != 3);

    printf("Ate a proxima!\n");
    return 0;
}