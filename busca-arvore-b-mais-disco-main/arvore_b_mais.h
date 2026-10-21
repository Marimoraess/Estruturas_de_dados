#ifndef BUSCA_ARVORE_B_MAIS_DISCO_ARVORE_B_MAIS_H
#define BUSCA_ARVORE_B_MAIS_DISCO_ARVORE_B_MAIS_H

#include <stdio.h>
#include "metadados.h"
#include "no_interno.h"
#include "no_folha.h"

void imprime_arquivos();
int busca(int chave, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados);

#endif //BUSCA_ARVORE_B_MAIS_DISCO_ARVORE_B_MAIS_H
