#ifndef BUSCA_ARVORE_B_MAIS_DISCO_NO_INTERNO_H
#define BUSCA_ARVORE_B_MAIS_DISCO_NO_INTERNO_H

#include <stdio.h>

typedef struct NoInterno {
    // m eh o numero total de chaves armazenados no noh
    int m;
    // ponteiro para o noh pai
    int pont_pai;
    // flag que diz se noh aponta pra folha ou nao
    int aponta_folha;
    // essa lista tera sempre m + 1 ponteiros
    int *p;
    // essa lista tera sempre m chaves
    int *chaves;
} TNoInterno;

void imprime_no_interno(int d, TNoInterno *no);
TNoInterno *no_interno(int d, int m, int pont_pai, int aponta_folha);
TNoInterno *no_interno_vazio(int d);
TNoInterno *cria_no_interno(int d, int m, int pont_pai, int aponta_folha, int size, ...);
void salva_no_interno(int d, TNoInterno *no, FILE *out);
TNoInterno *le_no_interno(int d, FILE *in);
int tamanho_no_interno(int d);
void libera_no_interno(TNoInterno *no);

#endif //BUSCA_ARVORE_B_MAIS_DISCO_NO_INTERNO_H
