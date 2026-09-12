#include <stdio.h>
#include <stdlib.h>
typedef struct noA{
    int info;
    struct noA* esq;
    struct noA* dir;
} TNoA;
int main() {

    TArv* raiz = cria(1);

    raiz->esq = cria(2);
    raiz->dir = cria(3);

    raiz->esq->esq = cria(4);
    raiz->esq->dir = cria(5);

    if (cheia(raiz))
        printf("A arvore e cheia\n");
    else
        printf("A arvore nao e cheia\n");

    return 0;
}