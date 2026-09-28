#include <stdio.h>
#include <stdlib.h>

typedef struct NoA {
    int info;
    struct NoA *esq, *dir;
} TNoA;
TNoA *maior(TNoA *raiz){
    if(raiz==NULL){
        return NULL;
    }
    TNoA *maior_at=raiz;
    TNoA *maior_esq=maior(raiz->esq);
    TNoA *maior_dir=maior(raiz->dir);
    if(maior_esq !=NULL && maior_esq->info > maior_at->info){
        maior_at=maior_esq;
    }
    if(maior_dir !=NULL && maior_dir->info > maior_at->info){
        maior_at=maior_dir;
    }
    return maior_at;
}
int main() {

    TNoA *raiz = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no1 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no2 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no3 = (TNoA *) malloc(sizeof(TNoA));
    TNoA *no4 = (TNoA *) malloc(sizeof(TNoA));

    raiz->info = 10;
    no1->info = 5;
    no2->info = 20;
    no3->info = 2;
    no4->info = 30;

    raiz->esq = no1;
    raiz->dir = no2;

    no1->esq = no3;
    no1->dir = no4;

    no2->esq = NULL;
    no2->dir = NULL;

    no3->esq = NULL;
    no3->dir = NULL;

    no4->esq = NULL;
    no4->dir = NULL;

    TNoA *resultado = maior(raiz);

    if (resultado != NULL) {
        printf("Maior elemento: %d\n", resultado->info);
    }

    return 0;
}