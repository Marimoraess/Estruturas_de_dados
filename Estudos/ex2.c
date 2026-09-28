#include <stdio.h>
#include <stdlib.h>

typedef struct NoA
{
    int info;
    struct NoA *esq, *dir;
} TNoA;
int dois_filhos(TNoA *a){
    if(a==NULL){
        return 0;
    }
    if(a->esq!=NULL&& a->dir!=NULL){
        return 1+dois_filhos(a->esq)+dois_filhos(a->dir);
    }
    return dois_filhos(a->esq)+dois_filhos(a->dir);
}