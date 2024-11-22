#include "graphs.h"

int inDegree(GraphL g, int j, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        struct edge *temp = g[i];
        while (temp) {
            if (temp->dest == j)
                count++;
            temp = temp->next;
        }
    }

    return count;
}

int outDegree(GraphL g, int j) {
    int count = 0;
    struct edge *temp = g[j];
    while (temp) {
        count++;
        temp = temp->next;
    }

    return count;
}

int capacidadeL(GraphL g, int v, int n) { return 0; }

int maxCap(GraphL g, int n) { return 0; }
