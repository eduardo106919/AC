#include <stdio.h>
#include <stdlib.h>


#define NV 10

typedef struct aresta {
    int dest; int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];


void fromMat (GrafoM in, GrafoL out) {
    LAdj *temp = NULL;

    int i, j;
    for (i = 0; i < NV; i++) {
        temp = &out[i];

        for (j = 0; j < NV; j++) {
            if (in[i][j] != 0) {
                *temp = malloc(sizeof(struct aresta));

                // error handling ???
                if (*temp == NULL)
                    return;

                (*temp)->dest = j;
                (*temp)->custo = in[i][j];
                temp = &((*temp)->prox);
            }
        }
    }
}

void inverte (GrafoL in, GrafoL out) {
    LAdj *temp = NULL;

    int i, j;
    for (i = 0; i < NV; i++) {
        for (j = 0; j < NV; j++) {
            if (in[j][i] != 0) {
                temp = &out[j];
                *temp = malloc(sizeof(struct aresta));

                // error handling ???
                if (*temp == NULL)
                    return;

                (*temp)->dest = j;
                (*temp)->custo = in[j][i];
                temp = &((*temp)->prox);
            }
        }
    }
}

int inDegree (GrafoL g) {
    int degrees[NV] = {0};
    int max = 0;

    LAdj temp = NULL;
    for (int i = 0; i < NV; i++) {
        temp = g[i];
        while (temp != NULL) {
            degrees[temp->dest]++;

            if (degrees[temp->dest] > degrees[max])
                max = temp->dest;

            temp = temp->prox;
        }
    }

    return max + 1;
}

int colorOK (GrafoL g, int cor[]) {
    LAdj temp = NULL;
    int result = 1;

    for (int i = 0; i < NV && result != 0; i++) {
        temp = g[i];

        while (temp != NULL && result != 0) {
            result = cor[i] == cor[temp->dest];

            temp = temp->prox;
        }
    }

    return result;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]) {
    LAdj temp = NULL, other = NULL;
    int result = 1;

    for (int i = 0; i < NV && result != 0; i++) {
        temp = g[i];

        while (temp != NULL && result != 0) {
            other = h[f[i]];
            while (other != NULL && result != 0) {
                result = other->dest == f[temp->dest];

                other = other->prox;
            }

            temp = temp->prox;
        }
    }

    return result;
}