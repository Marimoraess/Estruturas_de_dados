//quantidade de nós internos
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
int ni(TAB *a){
    if(a==NULL){
        return 0;
    }
    if(a->esq ==NULL && a->dir==NULL){
        return 0;
    }
    return 1+ni(a->esq)+ni(a->dir);
}