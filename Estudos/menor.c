#include <stdio.h>
#include <stdlib.h>

typedef struct NoA{
    int info;
    struct NoA *esq,*dir;
}TNoA;

TNoA *menor(TNoA *raiz){
    if(raiz==NULL){
        return NULL;
    }
    TNoA *menor_at= raiz;
    TNoA *menor_esq= menor(raiz->esq);
    TNoA *menor_dir=menor(raiz->dir);
    if(menor_esq != NULL && menor_esq->info<menor_at){
        menor_at=menor_esq;
    }
    if(menor_dir!=NULL && menor_dir->info<menor_at){
        menor_at=menor_dir;
    }
    return menor_at;
}
int main() {

    TNoA *raiz = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no2 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no3 = (TNoA *) malloc(sizeof(TNoA));

    raiz->info = 10;
    no1->info = 5;
    no2->info = 20;
    no3->info = 2;

    raiz->esq = no1;
    raiz->dir = no2;

    no1->esq = no3;
    no1->dir = NULL;

    no2->esq = NULL;
    no2->dir = NULL;

    no3->esq = NULL;
    no3->dir = NULL;

    TNoA *resultado = menor(raiz);

    printf("Menor valor: %d\n", resultado->info);

    return 0;
}