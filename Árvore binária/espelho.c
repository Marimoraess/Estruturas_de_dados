#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    int info;
    struct arvore *esq;
    struct arvore *dir;
} TArv;

void espelho(TArv *raiz) {
    if (raiz == NULL)
        return;

    TArv *aux;

    aux = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = aux;

    espelho(raiz->esq);
    espelho(raiz->dir);
}

void imprime(TArv *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->info);
        imprime(raiz->esq);
        imprime(raiz->dir);
    }
}

int main() {
    TArv *raiz = malloc(sizeof(TArv));
    TArv *n2 = malloc(sizeof(TArv));
    TArv *n3 = malloc(sizeof(TArv));
    TArv *n4 = malloc(sizeof(TArv));
    TArv *n5 = malloc(sizeof(TArv));

    raiz->info = 1;
    raiz->esq = n2;
    raiz->dir = n3;

    n2->info = 2;
    n2->esq = n4;
    n2->dir = n5;

    n3->info = 3;
    n3->esq = NULL;
    n3->dir = NULL;

    n4->info = 4;
    n4->esq = NULL;
    n4->dir = NULL;

    n5->info = 5;
    n5->esq = NULL;
    n5->dir = NULL;

    printf("Antes: ");
    imprime(raiz);

    espelho(raiz);

    printf("\nDepois: ");
    imprime(raiz);

    return 0;
}