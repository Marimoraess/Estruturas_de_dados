//maior
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
TAB* maior(TAB *a){
    if(a==NULL){
        return NULL;
    }
    TAB *maior_at=a;
    TAB* maior_esq=maior(a->esq);
    TAB* maior_dir=maior(a->dir);

    if(maior_esq!=NULL && maior_esq->info >maior_at->info){
        maior_at=maior_esq;
    }
    if(maior_dir!=NULL && maior_dir ->info >maior_at->info){
        maior_at=maior_dir;
    }
    return maior_at;
}