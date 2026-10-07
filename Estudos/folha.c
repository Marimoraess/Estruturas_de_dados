#include <stdio.h>
#include <stdlib.h>

typedef struct NoA {
    int info;
    struct NoA *esq, *dir;
} TNoA;
int folha(TNoA *raiz){
    if(raiz==NULL){
        return 0;
    }
    if(raiz->esq==NULL && raiz->dir==NULL){
        return 1;
    }
    return 0;
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

    printf("%d\n", folha(no1));

    return 0;
}
