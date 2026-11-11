#ifndef BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_COMPARTIMENTO_HASH_H
#define BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_COMPARTIMENTO_HASH_H

#include <stdio.h>

typedef struct CompartimentoHash {
    int prox;
} TCompartimento;

void imprime_compartimento(TCompartimento *compartimento);
TCompartimento *compartimento_hash(int prox);
void salva_compartimento(TCompartimento *compartimento, FILE *out);
TCompartimento *le_compartimento(FILE *in);
int tamanho_compartimento();
void imprime_arquivo_hash(char *nome_arquivo_hash);

#endif //BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_COMPARTIMENTO_HASH_H
