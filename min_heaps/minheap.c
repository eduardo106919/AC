#include "minheap.h"
#include <stdlib.h>

void initHeap(Heap *h, int size) {
    h->size = size;
    h->values = calloc(size, sizeof(Elem));
}

void swap_(Elem h[], int a, int b) {
    int t = h[a];
    h[a] = h[b];
    h[b] = t;
}

void bubbleUp(Elem h[], int i) {
    int parent = PARENT(i);

    while (i > 0 && h[parent] > h[i]) {
        swap_(h, i, parent);
        i = parent;
        parent = PARENT(parent);
    }
}

int insertHeap(Heap *h, Elem x) {
    // se a heap estiver cheia, duplico o tamanho
    if (h->size == h->used) {
        h->size *= 2;
        h->values = realloc(h->values, h->size * sizeof(Elem));
    }

    h->values[h->used] = x;
    bubbleUp(h->values, h->used);
    h->used++;

    return 1;
}

void bubbleDown(Elem h[], int N) {
    int i = 0, min;

    while (LEFT(i) < N) {
        // calcula o minimo entre i e a sua esquerda
        min = h[i] < h[LEFT(i)] ? i : LEFT(i);
        if (RIGHT(i) < N)
            // calcula o minimo entre i, a esquerda e a direita
            min = h[min] < h[RIGHT(i)] ? min : RIGHT(i);
        // se o minimo estiver nos sucessores
        if (min != i) {
            swap_(h, i, min);
            i = min;
        } else
            break;
    }
}

int extractMin(Heap *h, Elem *x) {
    // heap vazia
    if (h->used == 0)
        return 0;

    *x = h->values[0];
    h->values[0] = h->values[--h->used];

    bubbleDown(h->values, h->used);

    return 1;
}

/**
 * Verifica se os sucessores de value, são maiores que este
 */
int menor(Elem h[], Elem value, int index, int N) {
    if (LEFT(index) >= N || RIGHT(index) >= N)
        return 1;
    
    if (value > h[LEFT(index)] || value > h[RIGHT(index)])
        return 0;

    return menor(h, value, LEFT(index), N) && menor(h, value, RIGHT(index), N);
}

int minHeapOK(Heap h) {
    for (int i = 0; i < h.used; i++)
        if (!menor(h.values, h.values[i], i, h.used))
            return 0;

    return 1;
}