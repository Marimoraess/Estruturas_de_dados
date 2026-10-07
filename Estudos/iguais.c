#include <stdio.h>
#include <stdlib.h>

typedef struct NoA {
    int info;
    struct NoA *esq, *dir;
} TNoA;
int iguais(TNoA *a1, TNoA *a2){
    if(a1==NULL && a2==NULL){
        return 1;
    }
    if(a1==NULL && a2!=NULL || a1!=NULL && a2==NULL){
        return 0;
    }
    if(a1->info != a2->info){
        return 0;
    }
    return iguais(a1->esq,a2->esq)&& iguais(a1->dir,a2->dir);
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

    a2->info = 10;
    a2_no1->info = 5;
    a2_no2->info = 20;

    a2->esq = a2_no1;
    a2->dir = a2_no2;

    a2_no1->esq = NULL;
    a2_no1->dir = NULL;

    a2_no2->esq = NULL;
    a2_no2->dir = NULL;


    if (iguais(a1, a2)) {
        printf("As arvores sao iguais\n");
    } else {
        printf("As arvores sao diferentes\n");
    }

    return 0;
}
