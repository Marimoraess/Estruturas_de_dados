//quantiade de nós folhas
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
int nf(TAB *a){
    if(a==NULL){
        return 0;
    }
    if(a->esq==NULL && a->dir==NULL){
        return 1;
    }
    return nf(a->esq)+ nf(a->dir);