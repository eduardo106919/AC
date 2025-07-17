#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/* exercicio 1 */
#define SIZE 1009

typedef struct no {
    char matricula[6];
    struct no *next;
} No;

typedef No *Tabela[SIZE];

int hash(char matricula[6]) {
    int hash = 0;
    for (int i = 0; i < 6; i++) {
        hash += matricula[i];
    }

    return hash;
}

int insert(Tabela t, char matricula[6]) {
    int index = hash(matricula) % SIZE;

    No *temp = t[index];
    while (temp != NULL && strcmp(t, temp->matricula) != 0) {
        temp = temp->next;
    }

    int result = 0;
    if (temp == NULL) {
        temp = malloc(sizeof(No));
        if (temp == NULL) {
            result = 1;
        } else {
            strcpy(temp->matricula, matricula);
            temp->next = t[index];
            t[index] = temp;
            result = 0;
        }
    }

    return result;
}


/* exercicio 2 */

typedef struct no {
    int info;
    int bal;
    struct no *esq, *dir;
} No;

typedef No *Arvore;

Arvore rr(Arvore arv) {
    if (arv != NULL) {
        Arvore left = arv->esq;
        // if root is left and left sub tree is not left
        if (arv->bal < 0 && left->bal > -1) {
            arv->bal = 0; // BALANCED
        } else {
            arv->bal = 1; // RIGHT
        }

        left->bal = 1; // RIGHT

        arv->esq = left->dir;
        left->dir = arv;

        return left;
    }

    return NULL;
}


/* exercicio 3 */

/*
Complexidade de bals:
    T(N) = 0    , se N == 0
    T(N) = 2*(N/2) + 2T(N/2)  , N > 0

    T(N) = sum {i=1, log(N)} N = O(N * log(N))
*/


/* exercicio 4 */

typedef struct s {
    char *sin;
    struct s *next;
} Sin;

typedef struct p {
    char *pal;
    Sin *sins;
    struct p *next;
} Pal;

#define TAM 100

typedef Pal *Dic[TAM];
int hash(char *pal);

void sinonimos(Dic d, char *pal) {
    if (d != NULL && pal != NULL) {
        int index = hash(pal) % TAM;

        Pal *temp = d[index];

        while (temp != NULL && strcmp(temp->pal, pal) != 0) {
            temp = temp->next;
        }

        // found the word
        if (temp != NULL) {
            Sin *aux = temp->sins;

            while (aux != NULL) {
                if (aux->sin != NULL)
                    printf("%s ", aux->sin);
                aux = aux->next;
            }

        }
    }
}


/* exercicio 5 */

// #define TAM 100

typedef int Heap[TAM];

typedef struct nodo {
    int val;
    struct no *esq, *dir;
} Nodo, *Tree;


Tree heap_to_tree(Heap h, int start) {
    Tree result = NULL;
    if (start < TAM && start >= 0) {
        result = malloc(sizeof(Nodo));

        if (result == NULL) {
            // error handling ??
            return NULL;
        }

        result->val = h[start];
        result->esq = heap_to_tree(h, 2 * start + 1);
        result->dir = heap_to_tree(h, 2 * start + 2);
    }

    return result;
}

