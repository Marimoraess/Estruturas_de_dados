#include <stdio.h>
#include <stdlib.h>

typedef struct NoA
{
    int info;
    struct NoA *esq, *dir;
} TNoA;
int soma_folhas(TNoA *a){
    if(a==NULL){
        return 0;
    }
    if(a->esq==NULL&& a->dir==NULL){
        return a->info;
    }
    return soma_folhas(a->esq)+ soma_folhas(a->dir);
}