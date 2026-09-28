#include <stdio.h>
#include <stdlib.h>

typedef struct NoA
{
    int info;
    struct NoA *esq, *dir;
} TNoA;
void troca(TNoA *raiz)
{
    if(raiz==NULL){
        return;
    }
    TNoA *aux=raiz->esq;
    raiz->esq=raiz->dir;
    raiz->dir=aux;
}
int main()
{
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

    printf("Antes:\n");
    printf("Raiz: %d\n", raiz->info);
    printf("Esquerda: %d\n", raiz->esq->info);
    printf("Direita: %d\n", raiz->dir->info);

    troca(raiz);

    printf("\nDepois:\n");
    printf("Raiz: %d\n", raiz->info);
    printf("Esquerda: %d\n", raiz->esq->info);
    printf("Direita: %d\n", raiz->dir->info);

    return 0;
}