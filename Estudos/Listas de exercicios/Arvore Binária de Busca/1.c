#include <stdio.h>
#include<stdlib.h>

typedef struct ab{
 int info;
 struct ab *esq, *dir;
}TABB;

TABB* maior(TABB *a){
    if(a==NULL){
        return NULL;
    }
    if(a->dir==NULL){
        return a;
    }
    return maior(a->dir);
}