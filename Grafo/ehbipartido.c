#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct vizinho {
    int id_vizinho;
    struct vizinho *prox;
} TVizinho;

/*
 * Funções e tipos auxiliares
 */

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

typedef struct pilha {
    TLista *topo;
} TPilha;

TPilha *inicializa() {
    TPilha *pilha = (TPilha *) malloc(sizeof(TPilha));
    pilha->topo = NULL;
    return pilha;
}

void libera(TPilha *p) {
    TLista *q = p->topo;
    TLista *r;

    while (q != NULL) {
        r = q;
        q = q->prox;
        free(r);
    }

    free(p);
}

int pilha_vazia(TPilha *pilha) {
    if (pilha->topo == NULL)
        return 1;
    else
        return 0;
}

void push(TPilha *pilha, int elem) {
    TLista *novo = (TLista*) malloc(sizeof(TLista));

    novo->info = elem;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int pop(TPilha *pilha) {
    if (pilha_vazia(pilha)) {
        exit(1);
    }
    else {
        TLista *aux = pilha->topo;
        int info = aux->info;

        pilha->topo = aux->prox;

        free(aux);

        return info;
    }
}

int peek(TPilha *pilha) {
    if (pilha_vazia(pilha))
        return -1;
    else
        return pilha->topo->info;
}

void imprime_pilha(TPilha *pilha) {
    int x;
    TPilha *aux = inicializa();

    while (!pilha_vazia(pilha)) {
        x = pop(pilha);
        printf("%d\n", x);
        push(aux, x);
    }

    while (!pilha_vazia(aux)) {
        push(pilha, pop(aux));
    }

    libera(aux);

    printf("\n");
}

/*
 * Funções de grafo
 */

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
    while ((vertice != NULL) &&
           (vertice->id_vertice != id)) {

        vertice = vertice->prox;
    }

    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, int id) {
    while ((vizinho != NULL) &&
           (vizinho->id_vizinho != id)) {

        vizinho = vizinho->prox;
    }

    return vizinho;
}

void insere_aresta(TGrafo *g, int origem, int destino) {
    TGrafo *pv1 = busca_vertice(g, origem);
    TGrafo *pv2 = busca_vertice(g, destino);

    if (pv1 != NULL && pv2 != NULL) {
        TVizinho *nova =
            (TVizinho *) malloc(sizeof(TVizinho));

        nova->id_vizinho = destino;
        nova->prox = pv1->prim_vizinho;

        pv1->prim_vizinho = nova;
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

/* Verifica se o grafo é bipartido */
int ehbipartido(TGrafo *g) {

    TGrafo *p = g;

    while (p != NULL) {

        if (p->cor == -1) {

            TPilha *pilha = inicializa();

            p->cor = 0;

            push(pilha, p->id_vertice);

            while (!pilha_vazia(pilha)) {

                int id = pop(pilha);

                TGrafo *atual =
                    busca_vertice(g, id);

                TVizinho *v =
                    atual->prim_vizinho;

                while (v != NULL) {

                    TGrafo *vizinho =
                        busca_vertice(g,
                                     v->id_vizinho);

                    if (vizinho->cor == -1) {

                        vizinho->cor =
                            1 - atual->cor;

                        push(pilha,
                             vizinho->id_vertice);
                    }

                    else if (vizinho->cor ==
                             atual->cor) {

                        libera(pilha);

                        return 0;
                    }

                    v = v->prox;
                }
            }

            libera(pilha);
        }

        p = p->prox;
    }

    return 1;
}

int main() {

    int num_vertices, num_arestas;
    int id;
    int origem, destino;

    char l[100];
    char delimitador[] = "-";
    char *ptr;

    int i;

    TGrafo *g = NULL;

    /* lê número de vértices */
    scanf("%d", &num_vertices);

    /* cria os vértices */
    for (i = 0; i < num_vertices; i++) {

        scanf("%s", l);

        id = atoi(l);

        g = insere_vertice(g, id);
    }

    /* lê número de arestas */
    scanf("%d", &num_arestas);

    /* cria as arestas */
    for (i = 0; i < num_arestas; i++) {

        scanf("%s", l);

        ptr = strtok(l, delimitador);
        origem = atoi(ptr);

        ptr = strtok(NULL, delimitador);
        destino = atoi(ptr);

        /*
         * Como o grafo é não orientado,
         * insere nos dois sentidos
         */
        insere_aresta(g, origem, destino);
        insere_aresta(g, destino, origem);
    }

    printf("%d", ehbipartido(g));

    libera_vertice(g);

    return 0;
}