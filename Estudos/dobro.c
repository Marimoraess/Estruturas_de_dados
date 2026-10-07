#include <stdio.h>
#include <stdlib.h>

typedef struct NoA
{
    int info;
    struct NoA *esq, *dir;
} TNoA;
void dobra(TNoA *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    raiz->info = raiz->info * 2;
    dobra(raiz->esq);
    dobra(raiz->dir);
}
void imprime(TNoA *raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%d ", raiz->info);

    imprime(raiz->esq);
    imprime(raiz->dir);
}
int main() {

    TNoA *raiz = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no2 = (TNoA *) malloc(sizeof(TNoA));

    raiz->info = 10;
    no1->info = 5;
    no2->info = 20;

    raiz->esq = no1;
    raiz->dir = no2;

    no1->esq = NULL;
    no1->dir = NULL;

    no2->esq = NULL;
    no2->dir = NULL;

    printf("Antes: ");
    imprime(raiz);

    dobra(raiz);

    printf("\nDepois: ");
    imprime(raiz);

    return 0;
}