#include <stdio.h>
#include <stdlib.h>

typedef struct NoA{
    int info;
    struct NoA *esq,*dir;
}TNoA;
int filhos(TNoA *raiz){
    if(raiz==NULL){
        return 1;
    }
    if(raiz->esq!=NULL && raiz->dir==NULL || raiz->esq==NULL && raiz->dir!=NULL){
        return 0;
    }
    return filhos(raiz->esq)&& filhos(raiz-> dir);
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

    if (filhos(raiz)) {
        printf("Todos os nos possuem 0 ou 2 filhos\n");
    } else {
        printf("Existe um no com apenas 1 filho\n");
    }

    return 0;
}