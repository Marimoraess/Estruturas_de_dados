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
int testek(TGrafo *g, int k)
{
    TGrafo *p = g;
    int qtd = 0;

    while (p !NULL)
    {
        int cont = 0;
        TVizinho *v = p->prim_vizinho;

        while (v != NULL)
        {
            cont++;
            v = v->prox;
        }
        if (cont == k)
        {
            qtd++;
        }
        p = p->prox;
    }
    return qtd;
}
