//copia
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
TAB* copia(TAB *a){
    if(a==NULL){
        return NULL;
    }
    TAB* novo= (TAB*)malloc(sizeof(TAB));
    novo->info=a->info;
    novo->esq=copia(a->esq);
    novo->dir=copia(a->dir);
    return novo;
}