
//copia apenas um nó
#include <stdio.h>
#include <stdlib.h>

typedef struct NoA
{
    int info;
    struct NoA *esq, *dir;
} TNoA;
TNoA *copia(TNoA *raiz){
    if(raiz == NULL){
        return NULL;
    }
    TNoA *novo = (TNoA*)malloc(sizeof(TNoA));
    novo->info=raiz->info;
    novo->esq=NULL;
    novo->dir=NULL;
    return novo;
}
int main()
{
    TNoA *raiz = (TNoA *) malloc(sizeof(TNoA));

    raiz->info = 10;
    raiz->esq = NULL;
    raiz->dir = NULL;

    TNoA *resultado = copia(raiz);

    printf("Original: %d\n", raiz->info);
    printf("Copia: %d\n", resultado->info);

    return 0;
}