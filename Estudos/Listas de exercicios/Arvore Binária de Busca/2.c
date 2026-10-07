#include <stdio.h>
#include<stdlib.h>

typedef struct ab{
 int info;
 struct ab *esq, *dir;
}TABB;

TABB* menor(TABB *a){
    if(a==NULL){
        return NULL;
    }
    if(a->esq==NULL){
        return a;
    }
    return menor(a->esq);
}