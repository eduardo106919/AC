#include "grafos.h"
#include <stdio.h>

int maisLonga(GrafoL g, int or, int p[]) {
    int q[NV], front, end;
    int vis[NV], dist[NV], pais[NV];
    int max = or;
    LAdj a;

    for (int i = 0; i < NV; i++) {
        vis[i] = 0;
        dist[i] = -1;
        pais[i] = -1;
    }

    front = end = 0;
    q[end++] = or;
    vis[or] = 1;
    dist[or] = 0;
    max = or;

    while (front != end) {
        or = q[front++];
        for (a = g[or]; a != NULL; a = a->prox)
            if (!vis[a->dest]) {
                vis[a->dest] = 1;
                pais[a->dest] = or;
                dist[a->dest] = 1 + dist[or];
                q[end++] = a->dest;
                if (dist[max] < dist[a->dest])
                    max = a->dest;
            }
    }
    
    int next = max;
    for (int i = dist[max]; i >= 0 && next != -1; i--) {
        p[i] = next;
        next = pais[next];
    }

    return dist[max];
}

int componentesRec(GrafoL g, int * stamp, int v, int estado[], int temp[], int c[]) {
    LAdj it;
    int r = 0;

    estado[v] = 1; // em visita
    c[v] = temp[v] = *stamp++;

    for (it = g[v]; it != NULL; it = it->prox)
        if (estado[it->dest] != 2) { // não visitado ou em visita
            if (estado[it->dest] == 0) // não visitado
                r += componentesRec(g, stamp, it->dest, estado, temp, c);
            if (c[it->dest] < c[v])
                c[v] = c[it->dest];
        }

    if (c[v] == temp[v])
        r++;
    
    estado[v] = 2; // visitado
    return r;
}

int componentes(GrafoL g, int c[]) {
    int estado[NV], temp[NV];
    int i, r, stamp = 0;

    for (i = 0; i < NV; i++)
        estado[i] = 0; // não visitado

    for (i = 0; i < NV; i++)
        if (estado[i] == 0)
            r += componentesRec(g, &stamp, i, estado, temp, c);

    return r;
}

int ordTop(GrafoL g, int ord[]) {
    LAdj it;
    int v, inicio, fim;
    int nant[NV]; // número de antecessores

    // calculo do grau de entrada
    for (v = 0; v < NV; v++)
        nant[v] = 0;
    for (v = 0; v < NV; v++)
        for (it = g[v]; it != NULL; it = it->prox)
            nant[it->dest]++;
    
    // inicializacao da queue
    inicio = fim = 0; // queue vazia
    for (v = 0; v < NV; v++)
        if (nant[v] == 0)
            ord[fim++] = v; // enqueue(v)

    // construção da ordenação
    while (inicio < fim) { // queue não vazia
        v = ord[inicio++]; // dequeue()
        for (it = g[v]; it != NULL; it = it->prox) {
            nant[it->dest]--;
            if (nant[it->dest] == 0)
                ord[fim++] = it->dest; // enqueue(it->dest)
        }
    }

    return inicio;
}

int cicloRec(GrafoL g, int v, int vis[], int pai[], int c[], int *cicloSize) {
    vis[v] = 1; // em visita

    int w;
    for (LAdj a = g[v]; a != NULL; a = a->prox) {
        w = a->dest;
        if (vis[w] == 0) {
            pai[w] = v;
            if (cicloRec(g, w, vis, pai, c, cicloSize) != 0)
                return 1;
        } else if (vis[w] == 1) {
            // existe ciclo: reconstruir
            int tmp[NV];
            int len = 0;

            tmp[len++] = w; // inicio do ciclo
            while (v != w) {
                tmp[len++] = v;
                v = pai[v];
            }

            // copiar ciclo para array c
            for (v = 0; v < len; v++)
                c[v] = tmp[len - 1 - v];
            
            *cicloSize = len;
            return 1;
        }
    }

    vis[v] = 2; // visitado
    return 0;
}

int ciclo(GrafoL g, int c[]) {
    int vis[NV] = {0};
    int pai[NV];
    int cicloSize = 0, i;

    for (i = 0; i < NV; i++)
        pai[i] = -1;

    for (i = 0; i < NV; i++)
        if (vis[i] == 0)
            if (cicloRec(g, i, vis, pai, c, &cicloSize) != 0)
                return cicloSize;

    return 0; // sem ciclos
}

int caminho(int L, int C, char *mapa[L], int ls, int cs, int lf, int cf);
