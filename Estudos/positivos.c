#include <stdio.h>
#include <stdlib.h>

typedef struct NoA{
    int info;
    struct NoA *esq,*dir;
}TNoA;

int positivos(TNoA *raiz){
    if(raiz==NULL){
        return 1;
    }
    if(raiz->info<=0){
        return 0;
    }
    return positivos(raiz->esq)&& positivos(raiz->dir);
}
int main() {

    TNoA *raiz = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no2 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no3 = (TNoA *) malloc(sizeof(TNoA));

    raiz->info = 10;
    no1->info = 5;
    no2->info = 20;
    no3->info = 2;

    raiz->esq = no1;
    raiz->dir = no2;

    no1->esq = no3;
    no1->dir = NULL;

    no2->esq = NULL;
    no2->dir = NULL;

    no3->esq = NULL;
    no3->dir = NULL;

    if (positivos(raiz)) {
        printf("Todos os nos sao positivos\n");
    } else {
        printf("Existe pelo menos um no nao positivo\n");
    }

    return 0;
}