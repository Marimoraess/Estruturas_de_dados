#include <stdio.h>

void imprime_arquivo(char *nomeArq) {
    FILE *arq;

    arq = fopen(nomeArq, "r");

    if (arq != NULL) {
        char s[10];

        fscanf(arq, "%s", s);

        while (!feof(arq)) {
            printf("%s\n", s);
            fscanf(arq, "%s", s);
        }

        fclose(arq);
    }
    else {
        printf("Erro ao abrir arquivo\n");
    }
}

void merge(char *nomeArq1, char *nomeArq2, char *nomeArqMerge) {

    FILE *arq1 = fopen(nomeArq1, "r");
    FILE *arq2 = fopen(nomeArq2, "r");
    FILE *arqMerge = fopen(nomeArqMerge, "w");

    if (arq1 == NULL || arq2 == NULL || arqMerge == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int n1, n2;

    int tem1 = fscanf(arq1, "%d", &n1);
    int tem2 = fscanf(arq2, "%d", &n2);

    while (tem1 == 1 && tem2 == 1) {

        if (n1 < n2) {
            fprintf(arqMerge, "%d\n", n1);
            tem1 = fscanf(arq1, "%d", &n1);
        }

        else if (n2 < n1) {
            fprintf(arqMerge, "%d\n", n2);
            tem2 = fscanf(arq2, "%d", &n2);
        }

        else {
            fprintf(arqMerge, "%d\n", n1);

            tem1 = fscanf(arq1, "%d", &n1);
            tem2 = fscanf(arq2, "%d", &n2);
        }
    }

    while (tem1 == 1) {
        fprintf(arqMerge, "%d\n", n1);
        tem1 = fscanf(arq1, "%d", &n1);
    }

    while (tem2 == 1) {
        fprintf(arqMerge, "%d\n", n2);
        tem2 = fscanf(arq2, "%d", &n2);
    }

    fclose(arq1);
    fclose(arq2);
    fclose(arqMerge);
}

int main(int argc, char **argv) {

    merge("numeros1.txt", "numeros2.txt", "merge.txt");

    imprime_arquivo("merge.txt");

    return 0;
}