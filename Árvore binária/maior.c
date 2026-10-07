#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NOS 255
#define VAZIO INT_MIN

typedef struct sNoA {
    int info;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

TNoA *maior(TNoA *a) {
    TNoA *mesq;
    TNoA *mdir;
    TNoA *mno;

    if (a == NULL)
        return NULL;

    mno = a;
    mesq = maior(a->esq);
    mdir = maior(a->dir);

    if (mesq != NULL && mesq->info > mno->info)
        mno = mesq;

    if (mdir != NULL && mdir->info > mno->info)
        mno = mdir;

    return mno;
}

TNoA *inicializa(void) {
    return NULL;
}

TNoA *criaNo(int ch) {
    TNoA *novo;

    novo = (TNoA *) malloc(sizeof(TNoA));
    novo->info = ch;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }

    if (nodo != NULL) {
        printf("%d\n", nodo->info);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else {
        printf("vazio");
    }
}

void imprimeProfundidade(TNoA *nodo, int altura) {
    altura = altura - 1;

    if (nodo != NULL) {
        printf("%d", nodo->info);

        if (altura > 0) {
            printf("-");
            imprimeProfundidade(nodo->esq, altura);
            printf("-");
            imprimeProfundidade(nodo->dir, altura);
        }
    } else {
        printf("*");

        if (altura > 0) {
            printf("-");
            imprimeProfundidade(NULL, altura);
            printf("-");
            imprimeProfundidade(NULL, altura);
        }
    }
}

TNoA *criaArvore(int entrada[MAX_NOS], int tamanho) {
    int novaEntrada[MAX_NOS];
    int i, j;
    TNoA *novo;

    novo = NULL;

    if ((tamanho > 0) && (entrada[0] != VAZIO)) {
        novo = criaNo(entrada[0]);
        tamanho = tamanho / 2;

        i = 1;
        j = 0;

        while (i <= tamanho) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }

        novo->esq = criaArvore(novaEntrada, tamanho);

        i = tamanho + 1;
        j = 0;

        while (i <= tamanho * 2) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }

        novo->dir = criaArvore(novaEntrada, tamanho);
    }

    return novo;
}

int main(void) {
    TNoA *raiz;
    raiz = inicializa();

    char l[1000];
    char delimitador[] = "-";
    char *ptr;
    int entrada[MAX_NOS];
    int tam;

    scanf("%s", l);

    tam = 0;
    ptr = strtok(l, delimitador);

    while ((ptr != NULL) && (tam < MAX_NOS)) {
        if (ptr[0] == '*') {
            entrada[tam] = VAZIO;
        } else {
            entrada[tam] = atoi(ptr);
        }

        tam++;
        ptr = strtok(NULL, delimitador);
    }

    raiz = criaArvore(entrada, tam);

    TNoA *no = maior(raiz);

    if (no != NULL) {
        printf("%d", no->info);
    } else {
        printf("Arvore vazia!");
    }

    return 0;
}