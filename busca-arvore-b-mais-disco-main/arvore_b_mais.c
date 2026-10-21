
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include "arvore_b_mais.h"

void imprime_arquivos() {
    int i;

    /* Imprime arquivo de metadados */
    FILE *arq_m = fopen("metadados.dat", "rb");

    if (arq_m == NULL)
        return;

    TMetadados *m = le_metadados(arq_m);

    printf("*** Arquivo de Metadados ***\n");

    if (m == NULL) {
        fclose(arq_m);
        return;
    }

    imprime_metadados(m);
    fclose(arq_m);

    /* Imprime arquivo de indice */
    FILE *arq_i = fopen("indice.dat", "rb");

    printf("\n\n*** Arquivo de Indice ***\n");

    if (arq_i != NULL) {
        i = 0;

        TNoInterno *ni = le_no_interno(m->d, arq_i);

        while (ni != NULL) {
            printf("(((Endereco %d)))\n",
                   i * tamanho_no_interno(m->d));

            imprime_no_interno(m->d, ni);
            libera_no_interno(ni);

            ni = le_no_interno(m->d, arq_i);
            i++;
        }

        fclose(arq_i);
    }

    /* Imprime arquivo de dados */
    FILE *arq_d = fopen("clientes.dat", "rb");

    printf("\n*** Arquivo de Dados ***\n");

    if (arq_d != NULL) {
        i = 0;

        TNoFolha *nf = le_no_folha(m->d, arq_d);

        while (nf != NULL) {
            printf("(((Endereco %d)))\n",
                   i * tamanho_no_folha(m->d));

            imprime_no_folha(m->d, nf);
            libera_no_folha(m->d, nf);

            nf = le_no_folha(m->d, arq_d);
            i++;
        }

        fclose(arq_d);
    }

    free(m);
}

/*
 * Executa busca em arquivos utilizando arvore B+.
 * Retorna o endereco do no folha em que a chave
 * esta ou deveria estar.
 */
int busca(int chave, char *nome_arquivo_metadados,
          char *nome_arquivo_indice, char *nome_arquivo_dados)
{
    FILE *arq_m;
    FILE *arq_i;
    FILE *arq_d;

    TMetadados *meta;
    TNoInterno *interno;
    TNoFolha *folha;

    int endereco;
    int i;
    int d;

    /* Abre e le os metadados */
    arq_m = fopen(nome_arquivo_metadados, "rb");

    if (arq_m == NULL)
        return -1;

    meta = le_metadados(arq_m);
    fclose(arq_m);

    if (meta == NULL)
        return -1;

    d = meta->d;
    endereco = meta->pont_raiz;

    /* Verifica se a arvore esta vazia */
    if (endereco == -1) {
        free(meta);
        return -1;
    }

    /* Caso a raiz seja uma folha */
    if (meta->raiz_folha == 1) {
        free(meta);

        arq_d = fopen(nome_arquivo_dados, "rb");

        if (arq_d == NULL)
            return -1;

        fseek(arq_d, endereco, SEEK_SET);
        folha = le_no_folha(d, arq_d);

        if (folha == NULL) {
            fclose(arq_d);
            return -1;
        }

        imprime_no_folha(d, folha);
        libera_no_folha(d, folha);

        fclose(arq_d);

        return endereco;
    }

    free(meta);

    /* Abre os arquivos de indice e de dados */
    arq_i = fopen(nome_arquivo_indice, "rb");
    arq_d = fopen(nome_arquivo_dados, "rb");

    if (arq_i == NULL || arq_d == NULL) {
        if (arq_i != NULL)
            fclose(arq_i);

        if (arq_d != NULL)
            fclose(arq_d);

        return -1;
    }

    /* Percorre os nos internos */
    while (endereco != -1) {
        fseek(arq_i, endereco, SEEK_SET);

        interno = le_no_interno(d, arq_i);

        if (interno == NULL) {
            fclose(arq_i);
            fclose(arq_d);
            return -1;
        }

        imprime_no_interno(d, interno);

        /* Encontra o ponteiro do filho correto */
        i = 0;

        while (i < interno->m &&
               chave >= interno->chaves[i]) {
            i++;
        }

        endereco = interno->p[i];

        /* Se os filhos apontam para folhas */
        if (interno->aponta_folha == 1) {
            libera_no_interno(interno);

            if (endereco == -1) {
                fclose(arq_i);
                fclose(arq_d);
                return -1;
            }

            fseek(arq_d, endereco, SEEK_SET);
            folha = le_no_folha(d, arq_d);

            if (folha == NULL) {
                fclose(arq_i);
                fclose(arq_d);
                return -1;
            }

            imprime_no_folha(d, folha);
            libera_no_folha(d, folha);

            fclose(arq_i);
            fclose(arq_d);

            return endereco;
        }

        libera_no_interno(interno);
    }

    fclose(arq_i);
    fclose(arq_d);

    return -1;
}

int main() {
    /*
     * Descomente a linha abaixo se quiser imprimir
     * o conteudo dos arquivos antes da busca.
     */

    // imprime_arquivos();

    int chave;

    scanf("%d", &chave);

    int pont = busca(chave,
                     "metadados.dat",
                     "indice.dat",
                     "clientes.dat");

    printf("RESULTADO DA BUSCA: %d\n", pont);

    return 0;
}
