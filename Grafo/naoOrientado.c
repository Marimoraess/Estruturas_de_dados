#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct vizinho {
    int id_vizinho;
    int peso;
    struct vizinho *prox;
} TVizinho;

typedef struct grafo {
    int id_vertice;
    int cor;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, int id) {
    TGrafo *vertice = (TGrafo *) malloc(sizeof(TGrafo));

    vertice->id_vertice = id;
    vertice->cor = -1;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;

    return vertice;
}

void libera_vizinho(TVizinho *vizinho) {
    if (vizinho != NULL) {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TGrafo *vertice) {
    if (vertice != NULL) {
        libera_vizinho(vertice->prim_vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}

TGrafo *busca_vertice(TGrafo *vertice, int id) {

    while ((vertice != NULL) && (vertice->id_vertice != id)) {
        vertice = vertice->prox;
    }

    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, int id) {

    while ((vizinho != NULL) && (vizinho->id_vizinho != id)) {
        vizinho = vizinho->prox;
    }

    return vizinho;
}

void insere_aresta(TGrafo *g, int origem, int destino, int peso) {

    TGrafo *pv1 = busca_vertice(g, origem);
    TGrafo *pv2 = busca_vertice(g, destino);

    if (pv1 != NULL && pv2 != NULL) {

        TVizinho *vizinho = (TVizinho *) malloc(sizeof(TVizinho));

        vizinho->id_vizinho = destino;
        vizinho->peso = peso;

        vizinho->prox = pv1->prim_vizinho;
        pv1->prim_vizinho = vizinho;
    }
}

void imprime(TGrafo *vertice) {

    while (vertice != NULL) {

        printf("Vertice: %d\n", vertice->id_vertice);
        printf("Vizinhos: ");

        TVizinho *vizinho = vertice->prim_vizinho;

        while (vizinho != NULL) {
            printf("%d ", vizinho->id_vizinho);
            vizinho = vizinho->prox;
        }

        printf("\n\n");

        vertice = vertice->prox;
    }
}

/* Verifica se o grafo é não orientado */
int ehNaoOrientado(TGrafo *g) {

    TGrafo *p = g;
    TGrafo *destino;

    TVizinho *v;
    TVizinho *volta;

    int encontrou;

    /* percorre todos os vértices */
    while (p != NULL) {

        /* percorre todas as arestas do vértice p */
        v = p->prim_vizinho;

        while (v != NULL) {

            /*
             * Se temos:
             *
             * p -> v
             *
             * procuramos o vértice v
             */
            destino = busca_vertice(g, v->id_vizinho);

            if (destino == NULL)
                return 0;

            /* procura a aresta de volta */
            volta = destino->prim_vizinho;

            encontrou = 0;

            while (volta != NULL) {

                /*
                 * Precisa existir:
                 *
                 * v -> p
                 *
                 * com o mesmo peso
                 */
                if (volta->id_vizinho == p->id_vertice &&
                    volta->peso == v->peso) {

                    encontrou = 1;
                    break;
                }

                volta = volta->prox;
            }

            /* não encontrou a aresta inversa */
            if (encontrou == 0)
                return 0;

            v = v->prox;
        }

        p = p->prox;
    }

    /* todas as arestas possuem a inversa */
    return 1;
}

int main() {

    /*
     * A função main lê os dados de entrada,
     * cria o grafo e chama a função solicitada.
     * ELA NÃO DEVE SER MODIFICADA.
     */

    int num_vertices, num_arestas;
    int id;
    int origem, destino, peso;

    char l[100];
    char delimitador[] = "-";
    char *ptr;

    int i;

    TGrafo *g = NULL;

    /* lê número de vértices */
    scanf("%d", &num_vertices);

    /* lê e cria os vértices */
    for (i = 0; i < num_vertices; i++) {

        scanf("%s", l);

        id = atoi(l);

        g = insere_vertice(g, id);
    }

    /* lê número de arestas */
    scanf("%d", &num_arestas);

    /* lê e cria as arestas */
    for (i = 0; i < num_arestas; i++) {

        scanf("%s", l);

        ptr = strtok(l, delimitador);
        origem = atoi(ptr);

        ptr = strtok(NULL, delimitador);
        destino = atoi(ptr);

        ptr = strtok(NULL, delimitador);
        peso = atoi(ptr);

        insere_aresta(g, origem, destino, peso);
    }

    printf("%d", ehNaoOrientado(g));

    libera_vertice(g);

    return 0;
}