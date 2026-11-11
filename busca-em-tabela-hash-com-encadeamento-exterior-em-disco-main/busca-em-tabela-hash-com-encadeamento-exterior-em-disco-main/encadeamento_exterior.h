#ifndef BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_ENCADEAMENTO_EXTERIOR_H
#define BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_ENCADEAMENTO_EXTERIOR_H

#include "cliente.h"
#include "compartimento_hash.h"

void imprime_arquivos(char *nome_arquivo_hash, char *nome_arquivo_dados);
int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m);

#endif //BUSCA_ENCADEAMENTO_EXTERIOR_DISCO_ENCADEAMENTO_EXTERIOR_H
