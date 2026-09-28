#include <stdio.h>
#include <stdlib.h>

typedef struct ab {
    int info;
    struct ab *esq, *dir;
} TAB;
int altura(TAB *a){
    if(a==NULL){
        return 0;
    }
    int alt_esq=altura(a->esq);
    int alt_dir=altura(a->dir);
    if(alt_esq>alt_dir){
        return alt_esq+ 1;
    }
    else{
        return alt_dir +1;
    }
}