#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
    int info;
    struct lista *prox;
} TLista;

void imprime_lista(TLista *li) {
    TLista *p;

    for (p = li; p != NULL; p = p->prox)
        printf("%d ", p->info);
}

/* PUSH - insere no topo da pilha */
TLista* push(TLista* pilha, int valor) {
    TLista* novo = (TLista*) malloc(sizeof(TLista));

    novo->info = valor;
    novo->prox = pilha;

    return novo;
}

TLista* pull(TLista* pilha, int *valor) {
    TLista* p;

    if (pilha == NULL)
        return NULL;

    p = pilha;
    *valor = p->info;

    pilha = pilha->prox;

    free(p);

    return pilha;
}

int main(void) {
    TLista* pilha = NULL;
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;
    int retirado;
    scanf("%s", l);

    ptr = strtok(l, delimitador);

    while (ptr != NULL) {
        valor = atoi(ptr);
        pilha = push(pilha, valor);

        ptr = strtok(NULL, delimitador);
    }

    printf("Pilha: ");
    imprime_lista(pilha);

    pilha = pull(pilha, &retirado);

    printf("\nValor retirado: %d\n", retirado);

    printf("Pilha apos pull: ");
    imprime_lista(pilha);

    return 0;
}