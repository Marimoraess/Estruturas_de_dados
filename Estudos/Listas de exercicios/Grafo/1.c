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
int na(TGrafo *g)
{
    int cont = 0;
    TGrafo *p = g;//ponteiro para percorrer os vertices

    while (p != NULL)//enquanto existir vertice
    {
        TVizinho *v=p->prim_vizinho; //ponteiro q vai apontar p/ primeiro vizinho

        while (v!=NULL)//percorre todos os vizinhos daquele vertice
        {
            cont++;
            v=v->prox;
        }
        p=p->prox;
        
    }
    return cont/2;
}
int main()
{
    TGrafo g1, g2, g3;

    TVizinho v12, v13;
    TVizinho v21, v23;
    TVizinho v31, v32;

    // vertices do grafo
    g1.id = 1;
    g1.prox = &g2;

    g2.id = 2;
    g2.prox = &g3;

    g3.id = 3;
    g3.prox = NULL;

    // vizinhos do vertice 1: 2 e 3
    v12.id_vizinho = 2;
    v12.prox = &v13;

    v13.id_vizinho = 3;
    v13.prox = NULL;

    g1.prim_vizinho = &v12;

    // vizinhos do vertice 2: 1 e 3
    v21.id_vizinho = 1;
    v21.prox = &v23;

    v23.id_vizinho = 3;
    v23.prox = NULL;

    g2.prim_vizinho = &v21;

    // vizinhos do vertice 3: 1 e 2
    v31.id_vizinho = 1;
    v31.prox = &v32;

    v32.id_vizinho = 2;
    v32.prox = NULL;

    g3.prim_vizinho = &v31;

    printf("Quantidade de arestas: %d\n", na(&g1));

    return 0;
}