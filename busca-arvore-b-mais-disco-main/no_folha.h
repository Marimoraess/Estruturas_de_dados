#ifndef BUSCA_ARVORE_B_MAIS_DISCO_NO_FOLHA_H
#define BUSCA_ARVORE_B_MAIS_DISCO_NO_FOLHA_H

#include <stdio.h>
#include "cliente.h"

typedef struct NoFolha {
    // m eh o numero total de registros armazenados no noh
    int m;
    // ponteiro para o noh pai
    int pont_pai;
    // ponteiro para o proximo noh folha
    int pont_prox;
    // essa lista tera sempre m clients
    TCliente **clientes;
} TNoFolha;

void imprime_no_folha(int d, TNoFolha *no);
TNoFolha *no_folha(int d, int m, int pont_pai, int pont_prox);
TNoFolha *no_folha_vazio(int d);
TNoFolha *cria_no_folha(int d, int pont_pai, int pont_prox, int m, ...);
void salva_no_folha(int d, TNoFolha *no, FILE *out);
TNoFolha *le_no_folha(int d, FILE *in);
int tamanho_no_folha(int d);
void libera_no_folha(int d, TNoFolha *no);

#endif //BUSCA_ARVORE_B_MAIS_DISCO_NO_FOLHA_H
