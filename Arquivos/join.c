#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_NOME 100

typedef struct Departamento {
    int cod_dept;
    int sala;
    char nome[TAM_NOME];
} TDepartamento;

typedef struct Funcionario {
    int cod_func;
    int cod_dept;
    char nome[TAM_NOME];
} TFuncionario;

TFuncionario *le_funcionario(FILE *in)
{
    TFuncionario *func = (TFuncionario *) malloc(sizeof(TFuncionario));
    char linha[150];

    if (fgets(linha, 150, in) == NULL) {
        free(func);
        return NULL;
    }

    /* ignora linha vazia */
    if (linha[0] == '\n' || linha[0] == '\r') {
        free(func);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod;

    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    func->cod_func = cod;

    ptr = strtok(NULL, delimitador);
    cod = atoi(ptr);
    func->cod_dept = cod;

    ptr = strtok(NULL, delimitador);
    strcpy(func->nome, ptr);

    return func;
}

TDepartamento *le_departamento(FILE *in)
{
    TDepartamento *dept = (TDepartamento *) malloc(sizeof(TDepartamento));
    char linha[150];

    if (fgets(linha, 150, in) == NULL) {
        free(dept);
        return NULL;
    }

    /* ignora linha vazia */
    if (linha[0] == '\n' || linha[0] == '\r') {
        free(dept);
        return NULL;
    }

    char delimitador[] = ";";
    char *ptr;
    int cod, sala;

    ptr = strtok(linha, delimitador);
    cod = atoi(ptr);
    dept->cod_dept = cod;

    ptr = strtok(NULL, delimitador);
    sala = atoi(ptr);
    dept->sala = sala;

    ptr = strtok(NULL, delimitador);
    strcpy(dept->nome, ptr);

    return dept;
}

void imprime_arquivo(char *name)
{
    FILE *arq;

    arq = fopen(name, "r");

    if (arq != NULL) {
        char linha[150];

        fgets(linha, 150, arq);

        while (!feof(arq)) {
            printf("%s", linha);
            fgets(linha, 150, arq);
        }

        fclose(arq);
    }
    else {
        printf("Erro ao abrir arquivo\n");
    }
}

void leftOuterJoin(char *nome_arq_dept,
                   char *nome_arq_funcionarios,
                   char *nome_arq_join)
{
    FILE *arqDept = fopen(nome_arq_dept, "r");
    FILE *arqFunc = fopen(nome_arq_funcionarios, "r");
    FILE *arqJoin = fopen(nome_arq_join, "w");

    if (arqDept == NULL || arqFunc == NULL || arqJoin == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    TDepartamento *dept;

    while ((dept = le_departamento(arqDept)) != NULL) {

        rewind(arqFunc);

        TFuncionario *func;

        int encontrou = 0;

        while ((func = le_funcionario(arqFunc)) != NULL) {

            if (dept->cod_dept == func->cod_dept) {

                encontrou = 1;

                fprintf(arqJoin, "%d;", dept->cod_dept);
                fprintf(arqJoin, "%d;", dept->sala);
                fprintf(arqJoin, "%s;", dept->nome);
                fprintf(arqJoin, "%d;", func->cod_func);
                fprintf(arqJoin, "%s;\n", func->nome);
            }

            free(func);
        }

        /* nenhum funcionário pertence ao departamento */
        if (encontrou == 0) {

            fprintf(arqJoin, "%d;", dept->cod_dept);
            fprintf(arqJoin, "%d;", dept->sala);
            fprintf(arqJoin, "%s;", dept->nome);

            /* funcionário inexistente */
            fprintf(arqJoin, "0;;\n");
        }

        free(dept);
    }

    /* linha vazia no final do arquivo */
    fprintf(arqJoin, "\n");

    fclose(arqDept);
    fclose(arqFunc);
    fclose(arqJoin);
}

int main()
{
    leftOuterJoin(
        "departamentos.txt",
        "funcionarios.txt",
        "join.txt"
    );

    imprime_arquivo("join.txt");

    return 0;
}