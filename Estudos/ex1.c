#include <stdio.h>
#include <stdlib.h>

typedef struct NoA
{
    int info;
    struct NoA *esq, *dir;
} TNoA;
int um_filho(TNoA *a){
    if(a==NULL){
        return 0;
    }
    if(a->esq!=NULL && a->dir==NULL || a->esq==NULL && a->dir!=NULL){
        return 1+ um_filho(a->esq)+ um_filho(a->dir);
    }
    return um_filho(a->esq)+ um_filho(a->dir);

}