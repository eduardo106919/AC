//
//  hashing.c
//  Hashing
//
//  Created by Jorge Sousa Pinto on 22/11/17.
//  Copyright © 2017 Jorge Sousa Pinto. All rights reserved.
//

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
    HT *new_ht = calloc(1, sizeof(HT));

    initHT(new_ht, new_size);

    for (int i = 0; i < h->size; i++) {
        if (!freeHT(h, i))
            writeHT(new_ht, h->tbl[i].key, h->tbl[i].value);
    }

    free(h->tbl);

    h = new_ht;
}

int writeHT(HT *h, char key[], int value) {
    float load = h->used / h->size;

    // realocar para o dobro do tamanho
    if (load >= 0.8)
        growHT(h, 2 * h->size);
    
    int index = hash(key, h->size);

    // the i variable is not necessary, load < 0.8 ensures there is always free buckets
    for (int i = 0; i < h->size; i++) {
        // if the bucket is free, insert
        if (freeHT(h, index)) {
            h->tbl[index].value = value;
            strcpy(h->tbl[index].key, key);
        }

        index = (index + 1) % h->size;
    }

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
