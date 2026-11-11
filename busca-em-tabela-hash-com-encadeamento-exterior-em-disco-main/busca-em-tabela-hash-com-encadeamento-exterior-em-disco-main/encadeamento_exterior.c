#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "encadeamento_exterior.h"

#define M 7

void imprime_arquivos(char *nome_arquivo_hash, char *nome_arquivo_dados) {
    //Imprime arquivo de hash
    printf("TABELA HASH:\n");
    imprime_arquivo_hash(nome_arquivo_hash);

    //Imprime arquivo de dados
    printf("\nDADOS:\n");
    imprime_arquivo_dados(nome_arquivo_dados);
}

/* Executa busca em Arquivos por Encadeamento Exterior (Hash)
 * Assumir que ponteiro para proximo noh eh igual a -1 quando nao houver proximo noh
 * Ponteiros são lógicos (é preciso multiplicar pelo tamanho do registro para calcular o valor do deslocamento
 * Use a função tamanho_compartimento() e tamanho_cliente() dependendo do arquivo que está sendo manipulado
 *
 * Parametros:
 * cod_cli: chave do cliente que esta sendo buscado
 * nome_arquivo_hash: nome do arquivo que contem a tabela hash
 * nome_arquivo_dados: nome do arquivo onde os dados estao armazenados
 * m: tamanho da tabela hash (a função de hash é h(x) = x mod m
 *
 * Retorna o endereco (lógico) onde o cliente foi encontrado, ou -1 se nao for encontrado
 */

int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m) {

    FILE *arq_hash = fopen(nome_arquivo_hash, "rb");

    if (arq_hash == NULL) {
        return -1;
    }

    int indice = cod_cli % m;

    fseek(arq_hash, indice * tamanho_compartimento(), SEEK_SET);

    TCompartimento *comp = le_compartimento(arq_hash);

    fclose(arq_hash);

    if (comp == NULL) {
        return -1;
    }

    int pont = comp->prox;

    free(comp);

    if (pont == -1) {
        return -1;
    }

    FILE *arq_dados = fopen(nome_arquivo_dados, "rb");

    if (arq_dados == NULL) {
        return -1;
    }

    while (pont != -1) {

        fseek(arq_dados, pont * tamanho_cliente(), SEEK_SET);

        TCliente *cli = le_cliente(arq_dados);

        if (cli == NULL) {
            fclose(arq_dados);
            return -1;
        }

        imprime_cliente(cli);

        if (cli->cod == cod_cli && cli->ocupado == 1) {

            int resultado = pont;

            free(cli);
            fclose(arq_dados);

            return resultado;
        }

        pont = cli->prox;

        free(cli);
    }

    fclose(arq_dados);

    return -1;
}

int main() {
    /* Essa função gera a saída que é usada nos casos de teste. Ela NÃO DEVE SER MODIFICADA */
    int cod;
    int pont;

    //Descomente essa linha de código caso deseje imprimir o conteúdo dos arquivos de entrada para analisar
    //o comportamento da sua implementação
    //imprime_arquivos("tabHash.dat", "clientes.dat");

    //le chave a ser buscada
    scanf("%d", &cod);
    printf("REGISTROS ACESSADOS:\n");
    pont = busca(cod, "tabHash.dat", "clientes.dat", M);

    //Imprime resultado da função
    printf("RESULTADO: %d\n", pont);
}
