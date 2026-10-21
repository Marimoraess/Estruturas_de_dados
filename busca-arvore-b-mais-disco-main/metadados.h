#ifndef BUSCA_ARVORE_B_MAIS_DISCO_METADADOS_H
#define BUSCA_ARVORE_B_MAIS_DISCO_METADADOS_H

#include <stdio.h>

typedef struct Metadados {
    int d; // ordem da arvore
    // ponteiro para a raiz da arvore
    int pont_raiz;
    // flag que diz se a raiz eh uma folha (nesse caso ela esta no arquivo de dados)
    int raiz_folha;
    // ponteiro para o proximo noh interno livre
    int pont_prox_no_interno_livre;
    // ponteiro para o proximo noh folha livre
    int pont_prox_no_folha_livre;
} TMetadados;

void imprime_metadados(TMetadados *metadados);
TMetadados *metadados(int d, int pont_raiz, int raiz_folha, int pont_prox_no_interno_livre, int pont_prox_no_folha_livre);
TMetadados *metadados_vazio(int d);
void salva_metadados(TMetadados *metadados, FILE *out);
void salva_arq_metadados(char *nome_arquivo, TMetadados *metadados);
TMetadados *le_metadados(FILE *in);
TMetadados *le_arq_metadados(char *nome_arquivo);
int tamanho_metadados();

#endif //BUSCA_ARVORE_B_MAIS_DISCO_METADADOS_H
