#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho {
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo {
    char nome[10];
    int idade;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade) {
    TGrafo *vertice = (TGrafo *) malloc(sizeof(TGrafo));

    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;

    return vertice;
}

TGrafo *busca_vertice(TGrafo *vertice, char *nome) {
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0)) {
        vertice = vertice->prox;
    }

    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome) {
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0)) {
        vizinho = vizinho->prox;
    }

    return vizinho;
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino) {
    TGrafo *pv1 = busca_vertice(g, nome_origem);
    TGrafo *pv2 = busca_vertice(g, nome_destino);

    if (pv1 != NULL && pv2 != NULL) {
        TVizinho *vizinho = (TVizinho *) malloc(sizeof(TVizinho));

        strcpy(vizinho->nome, nome_destino);
        vizinho->prox = pv1->prim_vizinho;
        pv1->prim_vizinho = vizinho;
    }
}

void imprime(TGrafo *vertice) {
    while (vertice != NULL) {
        printf("Pessoa: %s - %d anos\n", vertice->nome, vertice->idade);
        printf("Segue: ");

        TVizinho *vizinho = vertice->prim_vizinho;

        while (vizinho != NULL) {
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
        }

        printf("\n\n");
        vertice = vertice->prox;
    }
}

int numero_seguidos(TGrafo *g, char *nome) {
    TGrafo *p;
    TVizinho *v;
    int cont = 0;

    p = busca_vertice(g, nome);

    if (p == NULL)
        return 0;

    v = p->prim_vizinho;

    while (v != NULL) {
        cont++;
        v = v->prox;
    }

    return cont;
}

int seguidores(TGrafo *g, char *nome, int imprime) {
    TGrafo *p = g;
    TVizinho *v;
    int cont = 0;

    while (p != NULL) {

        v = p->prim_vizinho;

        while (v != NULL) {

            if (strcmp(v->nome, nome) == 0) {
                cont++;

                if (imprime == 1)
                    printf("%s ", p->nome);

                break;
            }

            v = v->prox;
        }

        p = p->prox;
    }

    if (imprime == 1)
        printf("\n");

    return cont;
}

TGrafo *mais_popular(TGrafo *g) {
    TGrafo *p = g;
    TGrafo *popular = NULL;
    int maior = -1;
    int qtd;

    while (p != NULL) {

        qtd = seguidores(g, p->nome, 0);

        if (qtd > maior) {
            maior = qtd;
            popular = p;
        }

        p = p->prox;
    }

    return popular;
}

int segue_mais_velho(TGrafo *g, int imprime) {
    TGrafo *p = g;
    TGrafo *seguido;
    TVizinho *v;
    int cont = 0;
    int somente_mais_velhos;

    while (p != NULL) {

        v = p->prim_vizinho;
        somente_mais_velhos = 1;

        while (v != NULL) {

            seguido = busca_vertice(g, v->nome);

            if (seguido->idade <= p->idade) {
                somente_mais_velhos = 0;
                break;
            }

            v = v->prox;
        }

        if (p->prim_vizinho != NULL && somente_mais_velhos == 1) {
            cont++;

            if (imprime == 1)
                printf("%s ", p->nome);
        }

        p = p->prox;
    }

    if (imprime == 1)
        printf("\n\n");

    return cont;
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

int main() {
    int num_vertices, num_arestas;
    char nome[30];
    char origem[30], destino[30];
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int idade;
    int i;
    TGrafo *g = NULL;

    scanf("%d", &num_vertices);

    for (i = 0; i < num_vertices; i++) {
        scanf("%s", l);

        ptr = strtok(l, delimitador);
        strcpy(nome, ptr);

        ptr = strtok(NULL, delimitador);
        idade = atoi(ptr);

        g = insere_vertice(g, nome, idade);
    }

    scanf("%d", &num_arestas);

    for (i = 0; i < num_arestas; i++) {
        scanf("%s", l);

        ptr = strtok(l, delimitador);
        strcpy(origem, ptr);

        ptr = strtok(NULL, delimitador);
        strcpy(destino, ptr);

        insere_aresta(g, origem, destino);
    }

    scanf("%s", nome);

    printf("SEGUIDOS por %s: %d\n", nome, numero_seguidos(g, nome));

    printf("SEGUIDORES de %s:\n", nome);
    seguidores(g, nome, 1);

    TGrafo *p;

    p = mais_popular(g);

    printf("MAIS POPULAR: %s\n", p->nome);

    printf("SEGUEM APENAS PESSOAS MAIS VELHAS:\n");
    segue_mais_velho(g, 1);

    libera_vertice(g);

    return 0;
}