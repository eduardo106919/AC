#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashing.h"

int hash(char key[], int size) {
    int total = 0, i = 0;
    while (key[i])
        total += key[i++];

    return total % size;
}

void initHT(HT *h, int size) {
    h->size = size;

    h->tbl = calloc(size, sizeof(struct pair));

    for (int i = 0; i < size; i++)
        strcpy(h->tbl[i].key, EMPTY);
}

// Checks if a given bucket is free or not
int freeHT(HT *h, int k) {
    return strcmp(h->tbl[k].key, EMPTY) == 0 ||
           strcmp(h->tbl[k].key, DELETED) == 0;
}

void growHT(HT *h, int new_size) {
    struct pair *new = calloc(new_size, sizeof(struct pair));

    for (int i = 0; i < new_size; i++)
        strcpy(new[i].key, EMPTY);

    for (int i = 0; i < h->size; i++) {
        // se o bucket tiver conteudo valido
        if (!freeHT(h, i)) {
            int index = hash(h->tbl[i].key, new_size);

            while (strcmp(new[index].key, EMPTY) ||
                   strcmp(new[index].key, DELETED) == 0)
                index = (index + 1) % new_size;

            new[index].value = h->tbl[i].value;
            strcpy(new[index].key, h->tbl[i].key);
        }
    }

    free(h->tbl);
    h->tbl = new;
    h->size *= 2;

    printf("--- REHASHED TO %d BUCKETS ---\n", new_size);
}

int writeHT(HT *h, char key[], int value) {
    float load = h->used / (float)h->size;

    // realocar para o dobro do tamanho
    if (load >= 0.8)
        growHT(h, 2 * h->size);

    int index = hash(key, h->size);

    while (!freeHT(h, index))
        index = (index + 1) % h->size;

    h->tbl[index].value = value;
    strcpy(h->tbl[index].key, key);
    h->used++;

    return index;
}

int readHT(HT *h, char key[], int *value) {
    int index = hash(key, h->size);

    for (int i = 0; i < h->size && strcmp(h->tbl[index].key, EMPTY); i++) {
        if (strcmp(h->tbl[index].key, key) == 0) {
            *value = h->tbl[index].value;
            return index;
        }

        index = (index + 1) % h->size;
    }

    return -1;
}

int deleteHT(HT *h, char key[]) {
    int temp = 0;
    int index = readHT(h, key, &temp);

    if (index != -1) {
        strcpy(h->tbl[index].key, DELETED);
        h->used--;
    }

    return index;
}

void showHT(HT *h) {
    for (int i = 0; i < h->size; i++) {
        printf("%02d: ", i);
        if (freeHT(h, i)) {
            printf("-------------\n");
        } else {
            printf("key: '%s'\tvalue: %d\n", h->tbl[i].key, h->tbl[i].value);
        }
    }
}