#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct noA {
    char info;
    struct noA *esq;
    struct noA *dir;
} TNoA;

int count(TNoA *raiz, char valor) {
    if (raiz == NULL)
        return 0;

    return (raiz->info == valor) +
           count(raiz->esq, valor) +
           count(raiz->dir, valor);
}

int mesmos_nos(TNoA *a1, TNoA *a2) {
    char c;

    for (c = 'A'; c <= 'Z'; c++) {
        if (count(a1, c) != count(a2, c))
            return 0;
    }

    return 1;
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }

    if (nodo != NULL) {
        printf("%c\n", nodo->info);
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
        printf("%c", nodo->info);

        if (altura > 0) {
            imprimeProfundidade(nodo->esq, altura);
            imprimeProfundidade(nodo->dir, altura);
        }
    } else {
        printf("*");

        if (altura > 0) {
            imprimeProfundidade(NULL, altura);
            imprimeProfundidade(NULL, altura);
        }
    }
}

TNoA *criaArvore(char entrada[100], int tamanho) {
    char novaEntrada[100];
    int i, j;
    TNoA *novo;

    novo = NULL;

    if ((tamanho > 0) && (entrada[0] != '*')) {
        novo = (TNoA *) malloc(sizeof(TNoA));
        novo->info = entrada[0];

        tamanho = tamanho / 2;

        i = 1;
        j = 0;

        while (i <= tamanho) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }

        novaEntrada[j] = '\0';

        novo->esq = criaArvore(novaEntrada, tamanho);

        i = tamanho + 1;
        j = 0;

        while (i <= tamanho * 2) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }

        novaEntrada[j] = '\0';

        novo->dir = criaArvore(novaEntrada, tamanho);
    }

    return novo;
}

int main(void) {
    TNoA* a1 = NULL;
    TNoA* a2 = NULL;
    int tam;
    char entrada1[100];
    char entrada2[100];

    scanf("%s", entrada1);
    tam = strlen(entrada1);
    a1 = criaArvore(entrada1, tam);

    scanf("%s", entrada2);
    tam = strlen(entrada2);
    a2 = criaArvore(entrada2, tam);

    printf("%d", mesmos_nos(a1, a2));

    return 0;
}