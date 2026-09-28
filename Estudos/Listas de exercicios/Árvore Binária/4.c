//menor
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
TAB* menor(TAB *a){
    if(a==NULL){
        return NULL;
    }
    TAB *menor_at=a;
    TAB* menor_esq=menor(a->esq);
    TAB* menor_dir=menor(a->dir);

    if(menor_esq!=NULL && menor_esq->info <menor_at->info){
        menor_at=menor_esq;
    }
    if(menor_dir!=NULL && menor_dir ->info <menor_at->info){
        menor_at=menor_dir;
    }
    return menor_at;
}