#include <stdio.h>
#include <stdlib.h>

typedef struct NoA{
    int info;
    struct NoA *esq,*dir;
}TNoA;
int filho(TNoA *raiz){
    if(raiz==NULL){
        return 1;
    }
   if(raiz->esq!=NULL && raiz->dir!=NULL){
    return 0;
   }
    return filho(raiz->esq)&& filho(raiz->dir);
}
int main() {

    TNoA *raiz = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no2 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no3 = (TNoA *) malloc(sizeof(TNoA));

    raiz->info = 10;
    no1->info = 5;
    no2->info = 8;
    no3->info = 2;

    raiz->esq = no1;
    raiz->dir = NULL;

    no1->esq = NULL;
    no1->dir = no2;

    no2->esq = no3;
    no2->dir = NULL;

    no3->esq = NULL;
    no3->dir = NULL;

    if (filho(raiz)) {
        printf("A arvore possui exatamente um filho em cada no interno\n");
    } else {
        printf("A arvore nao possui exatamente um filho em cada no interno\n");
    }

    return 0;
}