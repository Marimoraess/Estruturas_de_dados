#include <stdio.h>
#include <stdlib.h>

typedef struct NoA {
    int info;
    struct NoA *esq, *dir;
} TNoA;
int quant(TNoA *raiz){
    if(raiz==NULL){
        return 0;
    }
    return 1 +quant(raiz->esq)+quant(raiz->dir);
}
int mesmo_tamanho(TNoA *a1, TNoA *a2){
    return quant(a1)==quant(a2);
}

int main() {

    TNoA *a1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *a1_no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *a1_no2 = (TNoA *) malloc(sizeof(TNoA));

    a1->info = 10;
    a1_no1->info = 5;
    a1_no2->info = 20;

    a1->esq = a1_no1;
    a1->dir = a1_no2;

    a1_no1->esq = NULL;
    a1_no1->dir = NULL;

    a1_no2->esq = NULL;
    a1_no2->dir = NULL;


    TNoA *a2 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *a2_no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *a2_no2 = (TNoA *) malloc(sizeof(TNoA));

    a2->info = 50;
    a2_no1->info = 30;
    a2_no2->info = 80;

    a2->esq = a2_no1;
    a2->dir = a2_no2;

    a2_no1->esq = NULL;
    a2_no1->dir = NULL;

    a2_no2->esq = NULL;
    a2_no2->dir = NULL;


    if (mesmo_tamanho(a1, a2)) {
        printf("As arvores possuem a mesma quantidade de nos\n");
    } else {
        printf("As arvores possuem quantidades diferentes de nos\n");
    }

    return 0;
}