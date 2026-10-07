#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TABB;

TABB *retira_impares(TABB *a)
{
    if (a == NULL)
    {
        return NULL;
    }

    a->esq = retira_impares(a->esq);
    a->dir = retira_impares(a->dir);

    if (a->info % 2 != 0)
    {
        // não tem filho esquerdo
        if (a->esq == NULL)
        {
            TABB *aux = a->dir;
            free(a);
            return aux;
        }

        // não tem filho direito
        if (a->dir == NULL)
        {
            TABB *aux = a->esq;
            free(a);
            return aux;
        }

        // tem dois filhos
        TABB *p = a->dir;

        while (p->esq != NULL)
        {
            p = p->esq;
        }

        p->esq = a->esq;

        TABB *aux = a->dir;

        free(a);

        return aux;
    }

    // nó é par, então permanece na árvore
    return a;
}

TABB *insere(TABB *a, int x)
{
    if (a == NULL)
    {
        TABB *novo = (TABB *)malloc(sizeof(TABB));

        novo->info = x;
        novo->esq = NULL;
        novo->dir = NULL;

        return novo;
    }

    if (x < a->info)
    {
        a->esq = insere(a->esq, x);
    }
    else
    {
        a->dir = insere(a->dir, x);
    }

    return a;
}

void imprime(TABB *a)
{
    if (a != NULL)
    {
        imprime(a->esq);
        printf("%d ", a->info);
        imprime(a->dir);
    }
}

int main()
{
    TABB *a = NULL;

    a = insere(a, 25);
    a = insere(a, 22);
    a = insere(a, 40);
    a = insere(a, 30);
    a = insere(a, 45);
    a = insere(a, 27);
    a = insere(a, 20);
    a = insere(a, 21);
    a = insere(a, 48);

    printf("Antes: ");
    imprime(a);

    a = retira_impares(a);

    printf("\nDepois: ");
    imprime(a);

    return 0;
}