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

void salva_departamento(TDepartamento *dept, FILE *out)
{
    fprintf(out, "%d", dept->cod_dept);
    fprintf(out, "%c", ';');
    fprintf(out, "%d", dept->sala);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", dept->nome);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", "\n");
}

void salva_funcionario(TFuncionario *func, FILE *out)
{
    fprintf(out, "%d", func->cod_func);
    fprintf(out, "%c", ';');
    fprintf(out, "%d", func->cod_dept);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", func->nome);
    fprintf(out, "%c", ';');
    fprintf(out, "%s", "\n");
}

TFuncionario *le_funcionario(FILE *in)
{
    TFuncionario *func = (TFuncionario *) malloc(sizeof(TFuncionario));

    char linha[150];

    if (fgets(linha, 150, in) == NULL) {
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

void join(char *nome_arq_dept,
          char *nome_arq_funcionarios,
          char *nome_arq_join)
{
    FILE *arqDept;
    FILE *arqFunc;
    FILE *arqJoin;

    arqDept = fopen(nome_arq_dept, "r");
    arqFunc = fopen(nome_arq_funcionarios, "r");
    arqJoin = fopen(nome_arq_join, "w");

    if (arqDept == NULL || arqFunc == NULL || arqJoin == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    TDepartamento *dept;

    while ((dept = le_departamento(arqDept)) != NULL) {

        /* volta para o início do arquivo de funcionários */
        rewind(arqFunc);

        TFuncionario *func;

        while ((func = le_funcionario(arqFunc)) != NULL) {

            if (dept->cod_dept == func->cod_dept) {

                fprintf(arqJoin, "%d;", dept->cod_dept);
                fprintf(arqJoin, "%d;", dept->sala);
                fprintf(arqJoin, "%s;", dept->nome);

                fprintf(arqJoin, "%d;", func->cod_func);
                fprintf(arqJoin, "%s;\n", func->nome);
            }

            free(func);
        }

        free(dept);
    }

    fclose(arqDept);
    fclose(arqFunc);
    fclose(arqJoin);
}

int main()
{
    join("departamentos.txt",
         "funcionarios.txt",
         "join.txt");

    imprime_arquivo("join.txt");

    return 0;
}