#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *esq;
    struct no *dir;
} TNo;

TNo* criaNo(int valor) {
    TNo *novo = (TNo*) malloc(sizeof(TNo));

    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

int cheia(TNo *raiz) {

    if (raiz == NULL)
        return 1;
    if (raiz->esq == NULL && raiz->dir == NULL)
        return 1;
    if (raiz->esq == NULL || raiz->dir == NULL)
        return 0;
    return cheia(raiz->esq) && cheia(raiz->dir);
}

int main() {

    TNo *raiz = criaNo(100);

    raiz->esq = criaNo(50);
    raiz->dir = criaNo(105);

    raiz->esq->esq = criaNo(2);
    raiz->esq->dir = criaNo(7);

    raiz->dir->esq = criaNo(112);
    raiz->dir->dir = criaNo(2);

    // Testando
    if (cheia(raiz))
        printf("cheia.\n");
    else
        printf("nao.\n");

    return 0;
}