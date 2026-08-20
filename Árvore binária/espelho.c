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
void preOrdem(TNo *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->info);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void espelho(TNo *raiz) {
    TNo *aux;

    if (raiz == NULL)
        return;
    aux = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = aux;

    espelho(raiz->esq);
    espelho(raiz->dir);
}

int main() {

    TNo *raiz = criaNo(70);
    raiz->esq = criaNo(84);
    raiz->dir = criaNo(32);
    raiz->esq->esq = criaNo(4);
    raiz->esq->dir = criaNo(200);
    raiz->dir->esq = criaNo(89);
    raiz->dir->dir = criaNo(13);

    printf("Arvore original: ");
    preOrdem(raiz);
    espelho(raiz);
    printf("\nArvore espelho: ");
    preOrdem(raiz);
    printf("\n");

    return 0;
}