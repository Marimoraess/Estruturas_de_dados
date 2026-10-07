#include <stdio.h>
#include <stdlib.h>

typedef struct viz
{
    int id_vizinho;
    struct viz *prox;
} TVizinho;

typedef struct grafo
{
    int id;
    struct grafo *prox;
    TVizinho *prim_vizinho;
} TGrafo;

int iguais(TGrafo *g1, TGrafo *g2)
{
    TGrafo *p1 = g1;

    while (p1 != NULL)
    {
        // procura o mesmo vertice em g2
        TGrafo *p2 = g2;

        while (p2 != NULL && p2->id != p1->id)
        {
            p2 = p2->prox;
        }

        // vertice de g1 nao existe em g2
        if (p2 == NULL)
        {
            return 0;
        }

        // verifica os vizinhos desse vertice
        TVizinho *v1 = p1->prim_vizinho;

        while (v1 != NULL)
        {
            TVizinho *v2 = p2->prim_vizinho;

            while (v2 != NULL && v2->id_vizinho != v1->id_vizinho)
            {
                v2 = v2->prox;
            }

            // vizinho de g1 nao existe em g2
            if (v2 == NULL)
            {
                return 0;
            }

            v1 = v1->prox;
        }

        p1 = p1->prox;
    }

    // verifica se g2 possui algum vertice a mais
    TGrafo *p2 = g2;

    while (p2 != NULL)
    {
        TGrafo *p1aux = g1;

        while (p1aux != NULL && p1aux->id != p2->id)
        {
            p1aux = p1aux->prox;
        }

        if (p1aux == NULL)
        {
            return 0;
        }

        p2 = p2->prox;
    }

    return 1;
}