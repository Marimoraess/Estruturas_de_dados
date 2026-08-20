#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *esq;
    struct no *dir;
} TNo;

typedef struct pilha {
    TNo *info;
    struct pilha *prox;
} TPilha;

TNo* criaNo(int valor) {
    TNo *novo = (TNo*) malloc(sizeof(TNo));

    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

void push(TPilha **p, TNo *no) {
    TPilha *novo = (TPilha*) malloc(sizeof(TPilha));

    novo->info = no;
    novo->prox = *p;
    *p = novo;
}

TNo* pop(TPilha **p) {
    TPilha *aux;
    TNo *no;

    if (*p == NULL)
        return NULL;

    aux = *p;
    no = aux->info;
    *p = aux->prox;

    free(aux);

    return no;
}

int pilhaVazia(TPilha *p) {
    return p == NULL;
}

void emOrdem(TNo *raiz) {
    TPilha *p = NULL;
    TNo *atual = raiz;

    while (atual != NULL || !pilhaVazia(p)) {

        while (atual != NULL) {
            push(&p, atual);
            atual = atual->esq;
        }

        atual = pop(&p);

        printf("%d ", atual->info);

        atual = atual->dir;
    }
}

int main() {

    TNo *raiz = criaNo(25);

    raiz->esq = criaNo(13);
    raiz->dir = criaNo(30);

    raiz->esq->esq = criaNo(8);
    raiz->esq->dir = criaNo(17);

    raiz->dir->esq = criaNo(27);
    raiz->dir->dir = criaNo(35);

    printf("Percurso em ordem simetrica: ");

    emOrdem(raiz);

    printf("\n");

    return 0;
}