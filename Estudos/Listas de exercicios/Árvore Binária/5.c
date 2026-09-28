//iguais
#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;
int igual(TAB* a1, TAB* a2){
    if(a1==NULL && a2==NULL){
        return 1;
    }
   
    if(a1== NULL && a2!=NULL || a1!=NULL && a2==NULL){
        return 0;
    }
     if(a1->info != a2->info){
        return 0;
    }
    return igual(a1->esq, a2->esq) && igual(a1->dir,a2->dir);
