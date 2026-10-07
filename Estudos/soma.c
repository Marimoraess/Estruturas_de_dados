#include <stdio.h>
#include <stdlib.h>

typedef struct NoA {
    int info;
    struct NoA *esq, *dir;
} TNoA;
int soma(TNoA *raiz){
    if (raiz == NULL) {
    return 0;
    }
    return raiz->info + soma(raiz->esq)+soma(raiz->dir);
}
int main() {
    TNoA *raiz = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no2 = (TNoA *) malloc(sizeof(TNoA));

    raiz->info = 10;
    no1->info = 5;
    no2->info = 20;

    raiz->esq = no1;
    raiz->dir = no2;

    no1->esq = NULL;
    no1->dir = NULL;

    no2->esq = NULL;
    no2->dir = NULL;

    printf("Soma: %d\n", soma(raiz));

    return 0;
}