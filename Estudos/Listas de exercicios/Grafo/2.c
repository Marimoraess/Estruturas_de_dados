#include <stdio.h>
#include <stdlib.h>
typedef struct viz
{
    int id_vizinho;   // guarda o vizinho
    struct viz *prox; // prox vizinho
} TVizinho;
typedef struct grafo
{
    int id;
    struct grafo *prox;
    TVizinho *prim_vizinho;

} TGrafo;
int nv(TGrafo *g)
{
    int cont=0;
    TGrafo *p=g;
    while (p!=NULL)
    {
        cont++;
        p=p->prox;
    }
    return cont;
}
    