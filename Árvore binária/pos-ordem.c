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

void pos(TNo *raiz) {
    TNo *pilha1[100];
    TNo *pilha2[100];
    int tp1 = -1;
    int tp2 = -1;

    if (raiz == NULL)
        return;

    pilha1[++tp1] = raiz;

    while (tp1 != -1) {

        TNo *p = pilha1[tp1--];
        pilha2[++tp2] = p;
        if (p->esq != NULL)
            pilha1[++tp1] = p->esq;

        if (p->dir != NULL)
            pilha1[++tp1] = p->dir;
    }

    while (tp2 != -1) {
        TNo *p = pilha2[tp2--];
        printf("%d ", p->info);
    }
}

int main() {

    TNo *raiz = criaNo(01);

    raiz->esq = criaNo(31);
    raiz->dir = criaNo(458);
    raiz->esq->esq = criaNo(51);
    raiz->esq->dir = criaNo(77);
    raiz->dir->esq = criaNo(45);
    raiz->dir->dir = criaNo(90);

    printf("Caminho: ");
    pos(raiz);

    return 0;
}