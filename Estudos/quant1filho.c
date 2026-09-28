#include <stdio.h>
#include <stdlib.h>

typedef struct NoA {
    int info;
    struct NoA *esq, *dir;
} TNoA;
int quant(TNoA *raiz){
    if(raiz==NULL){
        return 0;
    }
    if(raiz->esq==NULL && raiz-> dir==NULL){
        return 0;
    }
    return 1 + quant(raiz->esq)+ quant(raiz->dir);