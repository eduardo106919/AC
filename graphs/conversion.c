#include "graphs.h"

int readGraphM(GraphM g) { return 1; }

void print_lines(int n, char x) {
    for (int i = 0; i < n; i++)
        printf("%c", x);

    printf("\n");
}

void printGraphM(GraphM g, int n) {
    printf("     ");
    for (int i = 0; i < n; i++)
        printf("%2d ", i);

    printf("\n   ");
    print_lines(30, '-');

    for (int i = 0; i < n; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < n; j++)
            g[i][j] == NE ? printf("   ") : printf("%2d ", g[i][j]);
        printf("|\n");
    }

    printf("   ");
    print_lines(30, '-');
}

void printGraphL(GraphL g, int n) {
    for (int i = 0; i < n; i++) {
        struct edge *temp = g[i];
        printf("%d ", i);
        while (temp) {
            printf("--> (%d, %d) ", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void graphLtoM(GraphM gm, GraphL gl, int n) {
    for (int i = 0; i < n; i++) {
        struct edge *temp = gl[i];
        for (int j = 0; j < n; j++) {
            if (temp && temp->dest == j) {
                gm[i][j] = temp->weight;
                temp = temp->next;
            } else
                gm[i][j] = NE;
        }
    }
}

struct edge *create_node(WEIGHT value, int dest) {
    struct edge *new = (struct edge *)calloc(1, sizeof(struct edge));
    new->dest = dest;
    new->weight = value;

    return new;
}

void graphMtoL(GraphL gl, GraphM gm, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) {
            if (gm[i][j] != NE) {
                struct edge *temp = create_node(gm[i][j], j);
                temp->next = gl[i];
                gl[i] = temp;
            }
        }
    }
}
