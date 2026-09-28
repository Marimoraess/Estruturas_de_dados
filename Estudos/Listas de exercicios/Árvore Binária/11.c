//0 ou 2 filhos
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
int estbin(TAB *a){
    if(a==NULL){
        return 1;
    }
    if(a->esq==NULL && a->dir!=NULL || a->esq!=NULL && a->dir==NULL){
        return 0;
    }
    if(a->esq==NULL && a->dir==NULL){
        return 1;
    }
    return estbin(a->esq) && estbin(a->dir);

}