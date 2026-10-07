//zigue-zague
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
int zz(TAB *a){
    if(a==NULL){
        return 1;
    }
    //folha
    if(a->esq ==NULL &&a->dir==NULL){
        return 1;
    }
    //dois filhos
    if(a->esq!=NULL && a->dir!=NULL){
        return 0;
    }
    return zz(a->esq) && zz(a->dir);

    
}