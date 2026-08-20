#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NOS 255
#define VAZIO INT_MIN

typedef struct sNoA {
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

int zigue(TNoA *no, int lado) {
    if (no == NULL)
        return 1;

    if (lado == 0) {
        if (no->esq != NULL)
            return 0;
        return zigue(no->dir, 1);
    } else {
        if (no->dir != NULL)
            return 0;
        return zigue(no->esq, 0);
    }
}

int ziguezague(TNoA *raiz) {
    if (raiz == NULL)
        return 1;

    if (raiz->esq != NULL && raiz->dir != NULL)
        return 0;

    return ziguezague(raiz->esq) && ziguezague(raiz->dir);
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else
        printf("vazio");
}

void imprimeProfundidade(TNoA *nodo, int altura) {
    altura = altura - 1;
    if (nodo != NULL) {
        printf("%d", nodo->chave);
        if (altura > 0) {
            printf("-");
            imprimeProfundidade(nodo->esq, altura);
            printf("-");
            imprimeProfundidade(nodo->dir, altura);
        }
    } else {
        printf("*");
        if (altura > 0) {
            printf("-");
            imprimeProfundidade(NULL, altura);
            printf("-");
            imprimeProfundidade(NULL, altura);
        }
    }
}

TNoA *criaArvore(int entrada[MAX_NOS], int tamanho) {
    int novaEntrada[MAX_NOS];
    int i, j;
    TNoA *novo;

    novo = NULL;

    if ((tamanho > 0) && (entrada[0] != VAZIO)) {
        novo = (TNoA *) malloc(sizeof(TNoA));
        novo->chave = entrada[0];
        tamanho = tamanho / 2;

        i = 1;
        j = 0;

        while (i <= tamanho) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }

        novo->esq = criaArvore(novaEntrada, tamanho);

        i = tamanho + 1;
        j = 0;

        while (i <= tamanho * 2) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }

        novo->dir = criaArvore(novaEntrada, tamanho);
    }

    return novo;
}

int main(void) {
    TNoA *raiz;
    raiz = NULL;

    char l[1000];
    char delimitador[] = "-";
    char *ptr;
    int entrada[MAX_NOS];
    int tam;

    scanf("%s", l);

    tam = 0;
    ptr = strtok(l, delimitador);

    while ((ptr != NULL) && (tam < MAX_NOS)) {
        if (ptr[0] == '*')
            entrada[tam] = VAZIO;
        else
            entrada[tam] = atoi(ptr);

        tam++;
        ptr = strtok(NULL, delimitador);
    }

    raiz = criaArvore(entrada, tam);

    printf("%d", ziguezague(raiz));

    return 0;
}