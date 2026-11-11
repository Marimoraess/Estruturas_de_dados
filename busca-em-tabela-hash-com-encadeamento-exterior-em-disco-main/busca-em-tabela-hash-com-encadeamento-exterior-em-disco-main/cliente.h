#ifndef BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_CLIENTE_H
#define BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_CLIENTE_H

#include <stdio.h>

#define TAM_NOME 100

typedef struct Cliente {
    int cod;
    char nome[TAM_NOME];
    int prox;
    int ocupado; //Valores possíveis são 0 (LIBERADO) e 1 (OCUPADO)
} TCliente;

void imprime_cliente(TCliente *cliente);
TCliente *cliente(int cod, char *nome, int prox, int flag);
void salva_cliente(TCliente *cliente, FILE *out);
TCliente *le_cliente(FILE *in);
int tamanho_cliente();
void imprime_arquivo_dados(char *nome_arquivo_dados);
int num_registros(char *nome_arquivo_dados);

#endif //BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_CLIENTE_H
