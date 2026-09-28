#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *esq;
    struct no *dir;
} TNoA;

TNoA* criaNo(int valor) {
    TNoA *novo = (TNoA*) malloc(sizeof(TNoA));

    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

int cheia(TNoA *raiz) {

    if (raiz == NULL)
        return 1;
    if (raiz->esq == NULL && raiz->dir == NULL)
        return 1;                                 
    if (raiz->esq == NULL || raiz->dir == NULL)
        return 0;
    return cheia(raiz->esq) && cheia(raiz->dir);
}

int main() {

    TNoA *raiz = criaNo(100);

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