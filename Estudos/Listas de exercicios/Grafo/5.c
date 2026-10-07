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
    int cor;
    struct grafo *prox;
    TVizinho *prim_vizinho;
} TGrafo;
int nao_tem_mesma_cor(TGrafo *g)
{
    TGrafo *p = g;

    while (p != NULL)
    {
        TVizinho *v = p->prim_vizinho;

        while (v != NULL)
        {
            TGrafo *aux = g;

            // procura o vertice vizinho no grafo
            while (aux != NULL && aux->id != v->id_vizinho)
            {
                aux = aux->prox;
            }

            // compara a cor do vertice com a cor do vizinho
            if (aux != NULL && p->cor == aux->cor)
            {
                return 0;
            }

            v = v->prox;
        }

        p = p->prox;
    }

    return 1;
}