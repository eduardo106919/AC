#include <stdio.h>

#define NV 10

typedef struct aresta {
    int dest; int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];


void swap(int arr, int i. int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int minIndPeso(int vertices[], int pesos[], int tam) {
    return 0;
}

int dijkstraSP(GrafoL g, int or, int pais[], int pesos[]) {
    int r, i, v, cor[NV], orla[NV], tam;
    LAdj x;

    // inicializacoes
    for (i = 0; i < NV; i++) {
        pais[i] = -2;
        cor[i] = 0; // nao visitado
    }

    r = 0;
    orla[0] = or;
    tam = 1;
    pesos[or] = 0;
    pais[or] = -1;
    cor[or] = 1; // na orla

    // ciclo
    while (tam > 0) {
        // seleccionar vertice de menor peso
        i = minIndPeso(orla, pesos, tam);
        swap(orla, i, --tam);

        v = orla[tam];
        r++;
        cor[v] = 2; // visitado

        for (x = g[v]; x != NULL; x = x->prox) {
            if (cor[x->dest] == 0) {
                cor[x->dest] = 1;
                orla[tam++] = x->dest;
                pais[x->dest] = v;
                pesos[x->dest] = pesos[v] + x->custo;
            } else if (cor[x->dest] == 1 && pesos[v] + x->custo < pesos[x->dest]) {
                pais[x->dest] = v;
                pesos[x->dest] = pesos[v] + x->custo;
            }
        }
    }

    return r;
}

int excentricidadeV (GrafoL g, int v);

int diametro (GrafoL g);
