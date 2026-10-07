#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int m;
    struct No *pai;
    int *s;
    struct No **p;
} TNo;

typedef struct lista {
    int info;
    struct lista *prox;
} TLista;

TLista* insere_ordenado(TLista* li, int i) {
    TLista* novo;
    TLista* ant = NULL;
    TLista* p = li;

    while (p != NULL && p->info < i) {
        ant = p;
        p = p->prox;
    }

    novo = (TLista*) malloc(sizeof(TLista));
    novo->info = i;

    if (ant == NULL) {
        novo->prox = li;
        li = novo;
    }
    else {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return li;
}

void imprime_lista(TLista *li) {
    TLista* p;

    for (p = li; p != NULL; p = p->prox) {
        printf("%d ", p->info);
    }
}

TNo *cria(int d) {
    TNo *novo = (TNo *) malloc(sizeof(TNo));

    novo->m = 0;
    novo->pai = NULL;

    novo->s = (int *) malloc(sizeof(int) * (d * 2));
    novo->p = (TNo **) malloc(sizeof(TNo *) * (d * 2 + 1));

    for (int i = 0; i < (d * 2 + 1); i++) {
        novo->p[i] = NULL;
    }

    return novo;
}

TNo *libera(TNo *a, int d) {
    if (a != NULL) {
        for (int i = 0; i <= a->m; i++) {
            libera(a->p[i], d);
        }

        free(a->s);
        free(a->p);
        free(a);
    }

    return NULL;
}

void imprime_arvore(TNo *a, int nivel) {
    if (a != NULL) {
        char indent[100] = "";

        for (int i = 0; i < nivel; i++) {
            strcat(indent, "\t");
        }

        for (int i = a->m; i > 0; i--) {
            imprime_arvore(a->p[i], nivel + 1);

            printf("%s", indent);
            printf("%5d\n", a->s[i - 1]);
        }

        imprime_arvore(a->p[0], nivel + 1);
    }
}

void imprime_no(TNo *a) {
    if (a != NULL) {
        for (int i = 0; i < a->m; i++) {
            printf("%5d", a->s[i]);
        }

        printf("\n");
    }
}

int posicao(int chave, TNo *no) {
    int inicio = 0;
    int fim = no->m;
    int pos = (fim + inicio) / 2;

    while (pos != no->m &&
           chave != no->s[pos] &&
           inicio < fim) {

        if (chave > no->s[pos]) {
            inicio = pos + 1;
        }
        else {
            fim = pos;
        }

        pos = (fim + inicio) / 2;
    }

    return pos;
}

TNo *busca(TNo *no, int chave) {
    int pos = posicao(chave, no);

    if (no->p[pos] == NULL ||
        (pos < no->m && chave == no->s[pos])) {

        return no;
    }
    else {
        return busca(no->p[pos], chave);
    }
}

void particiona(TNo *P, int d, int pos, int chave, TNo *pt);

void insere(TNo *no, int d, int pos, int chave, TNo *pt) {

    if (pos == -1) {
        pos = posicao(chave, no);
    }

    if (no->m < 2 * d) {

        for (int i = no->m; i > pos; i--) {
            no->s[i] = no->s[i - 1];
            no->p[i + 1] = no->p[i];
        }

        no->s[pos] = chave;
        no->p[pos + 1] = pt;

        if (pt != NULL) {
            pt->pai = no;
        }

        no->m++;
    }
    else {
        particiona(no, d, pos, chave, pt);
    }
}

TNo *insere_folha(TNo *raiz, int d, int chave) {

    if (raiz != NULL) {

        TNo *no = busca(raiz, chave);

        int pos = posicao(chave, no);

        if (pos == no->m || chave != no->s[pos]) {

            insere(no, d, pos, chave, NULL);

            if (raiz->pai != NULL) {
                raiz = raiz->pai;
            }
        }
    }
    else {

        raiz = cria(d);

        raiz->s[0] = chave;
        raiz->m = 1;
    }

    return raiz;
}

void particiona(TNo *P, int d, int pos, int chave, TNo *pt) {

    TNo *Q = cria(d);

    int i = d * 2 - 1;
    int j = d - 1;

    while (j >= 0) {

        if (j != pos - d - 1) {

            Q->s[j] = P->s[i];
            Q->p[j + 1] = P->p[i + 1];

            i--;
        }
        else {

            Q->s[j] = chave;
            Q->p[j + 1] = pt;
        }

        if (Q->p[j + 1] != NULL) {
            Q->p[j + 1]->pai = Q;
        }

        j--;
    }

    Q->m = d;

    if (pos <= d) {

        P->m = d;

        insere(P, d, pos, chave, pt);
    }

    if (P->pai == NULL) {

        TNo *W = cria(d);

        W->p[0] = P;

        P->pai = W;
    }

    insere(P->pai, d, -1, P->s[d], Q);

    Q->p[0] = P->p[d + 1];

    if (Q->p[0] != NULL) {
        Q->p[0]->pai = Q;
    }

    P->m = d;
}


/* Função auxiliar */
void menor_k_aux(TNo *raiz, int k, TLista **lista) {

    if (raiz == NULL) {
        return;
    }

    int i;

    for (i = 0; i < raiz->m; i++) {

        /*
         * O filho p[i] pode possuir valores menores
         * que a chave s[i].
         */
        menor_k_aux(raiz->p[i], k, lista);

        /*
         * Se a chave for menor que k,
         * coloca na lista.
         */
        if (raiz->s[i] < k) {

            *lista = insere_ordenado(
                *lista,
                raiz->s[i]
            );
        }
        else {

            /*
             * Como as chaves da árvore B
             * estão ordenadas, se s[i] >= k,
             * todas as chaves seguintes também
             * serão >= k.
             *
             * Portanto não precisamos visitar
             * o restante.
             */
            return;
        }
    }

    /*
     * Só visitamos o último filho se todas
     * as chaves do nó forem menores que k.
     */
    menor_k_aux(
        raiz->p[raiz->m],
        k,
        lista
    );
}


TLista *menor_k(TNo *raiz, int k) {

    TLista *lista = NULL;

    menor_k_aux(
        raiz,
        k,
        &lista
    );

    return lista;
}


int main(int argc, char *argv[]) {

    TNo *raiz = NULL;

    int d;
    int k;

    scanf("%d", &d);

    char l[1000];
    char delimitador[] = "-";
    char *ptr;
    int valor;

    scanf("%s", l);

    ptr = strtok(l, delimitador);

    while (ptr != NULL) {

        valor = atoi(ptr);

        raiz = insere_folha(
            raiz,
            d,
            valor
        );

        ptr = strtok(
            NULL,
            delimitador
        );
    }

    scanf("%d", &k);

    TLista *lista = menor_k(
        raiz,
        k
    );

    imprime_lista(lista);

    return 0;
}