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

void ordem(TNo *raiz) {
    TNo *p = raiz;
    TNo *pilha[100];
    int topo = -1;

    while (p != NULL || topo != -1) {

        while (p != NULL) {
            pilha[++topo] = p;
            p = p->esq;
        }

        p = pilha[topo--];

        printf("%d ", p->info);

        p = p->dir;
    }
}

int main() {

    TNo *raiz = criaNo(24);
    raiz->esq = criaNo(59);
    raiz->dir = criaNo(5);
    raiz->esq->esq = criaNo(29);
    raiz->esq->dir = criaNo(74);

    printf("Caminho: ");
    ordem(raiz);

    return 0;
}