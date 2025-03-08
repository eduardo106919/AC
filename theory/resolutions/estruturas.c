#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Exercicio 1

#define SIZE 1009
    
typedef struct no {
    char matricula[6];
    struct no *next;
} No;
typedef No *Tabela[SIZE];

int hash(char matricula[6]) {
    int count = 0;

    for (int i = 0; i < 6; i++)
        count += matricula[i];

    return count % SIZE;
}

int insert(Tabela t, char matricula[6]) {
    int index = hash(matricula);

    struct no * temp = t[index];

    while(temp && strcmp(matricula, temp->matricula))
        temp = temp->next;

    // se não existir, adiciono na cabeça da lista
    if (temp == NULL) {
        struct no * new = malloc(sizeof(struct no));
        strcpy(new->matricula, matricula);
        new->next = t[index];
        t[index] = new;
        return 1;
    }

    return 0;
}

// Exercicio 2

typedef struct no {
    int info;
    int bal;
    struct no *esq, *dir;
} No;
typedef No *Arvore;

/*
    Estou a assumir:
        -1 -> direita
         0 -> balanceado
         1 -> esquerda
*/

Arvore rr(Arvore arv) {
    Arvore temp = arv->esq;
    int root_bal = arv->bal;
    int left_bal = temp->bal;

    arv->esq = temp->dir;
    temp->dir = arv;

    temp->bal = -1;

    if (root_bal > 0 && left_bal <= 0)
        arv->bal = 0;
    else
        arv->bal = -1;

    return temp;
}

// Exercicio 3

/*
    T(N) = 2*Taltura(N/2) + 2*Tbals(N/2)
         = 2*N + 2Tbals(N/2)
         = sum(1 -> 1+log(N)) 2N
         = 2N * (1+log(N))
         = teta(N*log(N))
*/

// Exercicio 4

typedef struct s {
    char *sin;
    struct s *next;
} Sin;

typedef struct p {
    char *pal;
    Sin *sins;
    struct p *next;
} Pal;

#define TAM 1000

typedef Pal *Dic[TAM];

void sinonimos(Dic d, char *pal) {
    int index = hash(pal) % TAM;
    struct p * temp = d[index];
    
    while(temp && strcmp(temp->pal, pal))
        temp = temp->next;

    if (temp) {
        struct s * aux = temp->sins;
        while(aux) {
            printf("%s\n", aux->sin);
            aux = aux->next;
        }
    }
}

// Exercicio 5

typedef int Heap[TAM];

typedef struct nodo {
    int val;
    struct no *esq, *dir;
} Nodo, *Tree;

Tree build_heap_aux(Heap h, int i, int n) {
    if (i >= n)
        return NULL;

    Tree root = create_node(h[i]);
    root->esq = build_heap_aux(h, 2 * i + 1, n);
    root->dir = build_heap_aux(h, 2 * i + 2, n);

    return root;
}

Tree build_heap(Heap h, int n) {
    return build_heap_aux(h, 0, n);
}

// Exercicio 6

/*
    ao adicionar 10, será efetuado um rotate right
    ao adicionar 30, será efetuado um rotate right na árvore da direita e depois um rotate left na árvore
    ao adicionar 70, será efetuado um rotate left na árvore da direita
*/

// Exercicio 7

typedef struct node {
    int info;
    struct node *esq, *dir;
} *Node;

Node buildBST(int arr[], int n) {
    if (n <= 0)
        return NULL;

    Node root = create_node(arr[n / 2]);
    root->esq = buildBST(arr, n / 2);
    root->dir = buildBST(arr + n / 2, n - (n / 2));

    return root;
}

// Exercicio 8

typedef struct count {
    int store[1001];
    int total;
} Count;

Count * init_count(void) {
    Count *new = malloc(sizeof(Count));

    new->total = 0;

    for (int i = 0; i < 1001; i++)
        new->store[i] = 0;

    return new;
}

void insert(Count *c, int x) {
    c->store[x]++;
    c->total++;
}

int check(Count *c, int x) {
    return c->store[x];
}

void show(Count *c) {
    int aux = 0;
    for (int i = 0; i < 1001 && aux < c->total; i++) {
        for (int j = 0; j < c->store[i]; j++)
            printf("%d ", i);
    }
}

// Exercicio 9

#define MaxH 1000
typedef struct mHeap {
    int tamanho;
    int heap [MaxH];
} *MinHeap;

#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2

void bubbleUp(MinHeap h, int i) {
    int parent = PARENT(i);

    while (i > 0 && h->heap[parent] > h[i]) {
        swap(h, i, parent);
        i = parent;
        parent = PARENT(parent);
    }
}

void muda (MinHeap h, int pos, int valor) {
    h->heap[pos] = valor;
    bubbleUp(h, pos);
}

// Exercicio 10

typedef struct nodo *ABPInt;

struct nodo {
    int valor;
    ABPInt esq, dir;
};

int procura (ABPInt a, int l, int u) {
    while(a) {
        if (a->val < u && a->val > l)
            return 1;
        
        if (a->val >= u)
            a = a->esq;
        else if (a->val <= l)
            a = a->dir;
    }

    return 0;
}

// Exercicio 11

/*
    melhor caso: a raiz está no intervalo selecionado
        T(N) = 1

    pior caso: temos de percorrer todos os niveis da árvore, isto é,
               o elemento está no último nível ou não existe.
        T(N) = log(N)
*/


// Exercicio 12

/*
    As folhas de uma árvore são os nodos que não têm sucessores, logo numa min heap
    o conjunto dos maiores elementos estará nas folhas da heap
 */

int biggest(MinHeap *h) {
    int stop = h->tamanho / 2;
    int min = h->heap[h->tamanho - 1];

    for (int i = h->tamanho - 2; i >= 0 && i >= stop; i--)
        if (h->heap[i] > min)
            min = h->heap[i];

    return min;
}

// Exercicio 13

typedef struct avlnode {
    int value,balance;
    struct avlnode *esq, *dir;
} *AVL;

int rdir(AVL * ptr) {
    if (*ptr == NULL || (*ptr)->esq == NULL)
        return -1;

    AVL left = (*ptr)->esq;
    (*ptr)->esq = left->dir;
    *ptr = left;

    return 0;
}

// Exercicio 14

/*
    adicionar 30, fazer rotate left
    adicionar 40, fazer rotate right na arvore de raiz 70, fazer rotate left na arvore de raiz 30
*/

// Exercicio 17

/*
    adicionar 6, fazer rotate left na arvore de raiz 5, fazer rotate right na arvore de raiz 8
*/

// Exercicio 19

typedef struct minheap {
    int size;
    int used;
    int *values;
} *MinHeap;

int *ordenados (MinHeap h) {
    int *ord = calloc(h->used, sizeof(int));

    for (int i = 0; i < h->used; i++) {
        ord[i] = h->values[0];
        swap(h->values, 0, h->used - 1 - i);
        bubbleDown(h);
    }

    free(h->values);
    free(h);

    return ord;
}

// Exercicio 20

typedef struct entryC {
    char key[10];
    void *info;
    struct entryC *next;
} EntryChain;

typedef struct hashT {
    int hashsize;
    EntryChain *table;
} *HashTableChain;

/*
    nesta tabela, o fator de carga, é o tamanho médio de cada lista, ou seja, o número médio de colisões
    logo, load = used / size
*/

float loadFactorC (HashTableChain t) {
    int count = 0;
    for (int i = 0; i < t->hashsize; i++) {
        EntryChain *temp = t->table[i];
        while(temp) {
            count++;
            temp = temp->next;
        }
    }

    return count / (float) t->hashsize;
}

// Exercicio 21

int rank[26];

int hash (int size, char key[]) {
    int res = 0;
    for (int i = 0; i < size; i++)
        res += rank[tolower(key[i]) - 'a'];

    return res % size;
}

// Exercicio 22

/* adicionar 25, 30, 23, 17, 13, 40 */

// Exercicio 23

/*
    b)
        T(N) = 1 + 2*T(N/2)
             = sum(0 -> log(N)) 2 elevado a i
             = 2*N - 1
             = linear
*/

// Exercicio 24

#define STATUS_FREE 0
#define STATUS_USED 1
#define STATUS_DELETED 2

typedef struct entryO {
    int status;
    char *key;
    void *info;
} EntryOAdd;

typedef struct hashT {
    int size;
    int used;
    EntryOAdd *table;
} *HashTableOAddr;

void doubleTable (HashTableOAddr h) {
    int d_size = 2 * h->size;
    EntryOAdd * new = calloc(d_size, sizeof(EntryOAdd));
    // não é necessário inicializar os buckets a FREE, o calloc faz isso

    for (int i = 0; i < h->size; i++) {
        int index = hash(h->table[i].key, d_size);
        while(new[index].status != STATUS_FREE)
            index = (index + 1) % d_size;

        new[index].status = STATUS_USED;
        new[index].info = h->table[i].info;
        strcpy(new[index].key, h->table[i].key);
    }

    h->size = d_size;
    free(h->table);
    h->table = new;
}

// Exercicio 26

// alinea b)

int menor(MinHeap h, int i) {
    if (i >= h->used)
        return 1;

    // vai dar barraco porque LEFT e RIGHT vai sair fora dos limites
    // fazer com PARENT em vez
    if (h->values[i] > h->values[LEFT(i)] || h->values[i] > h->values[RIGHT(i)])
        return 0;

    return menor(h, LEFT(i)) && menor(h, RIGHT(i));
}

int minHeapOk(MinHeap h) {
    return menor(h, 0);
}

// Exercicio 27

typedef struct entry {
    char key[10];
    void *info;
    struct entry *next;
} *Entry;

typedef struct hashT {
    int hashsize;
    Entry *table;
} *HashTable;

HashTable newTable(int hashsize) {
    HashTable new = malloc(sizeof(struct hashT));
    new->hashsize = hashsize;
    new->table = malloc(hashsize * sizeof(Entry));
    for (int i = 0; i < hashsize; i++)
        new->table[i] = NULL;

    return new;
}

// Exercicio 29

#define Bal 0 // Balanceada
#define Esq -1 // Esq mais pesada
#define Dir 1 // Dir mais pesada

typedef struct avlNode *AVL;

struct avlNode {
    int bal; // Bal/Esq/Dir
    int valor;
    struct avlNode *esq,*dir;
}

int altura(AVL a) {
    int count = 0;
    while(a) {
        if (a->bal == Dir)
            a = a->dir;
        else
            a = a->esq;
        count++;
    }

    return count;
}

// Exercicio 30

typedef struct nodo{
    int valor;
    int altura;
    struct nodo *esq, *dir;
} Node, *AVL;

AVL rotateLeft (AVL a) {
    AVL new = a->dir;
    a->dir = new->esq;
    new->esq = a;

    // existe forma melhor ??
    a->altura = altura(a);
    new->altura = altura(new);

    return new;
}

// Exercicio 31

#define Livre 0
#define Ocupado 1
#define Apagado 2

typedef struct key *Key;

struct celula {
    Key k;
    void *info;
    int estado; //Livre/Ocupado/Apagado
};

typedef struct shash {
    int tamanho, ocupados, apagados;
    struct celula *Tabela;
} *THash;

int hash (Key, int);

void remApagados (THash h) {
    if (h->apagados == 0)
        return;

    for (int i = 0; i < h->tamanho; i++) {
        if (h->Tabela[i].estado == Apagado)
            h->Tabela[i].estado == Livre;
        else if (h->Tabela[i].estado == Ocupado) {
            int index = hash(h->Tabela[i].k, h->tamanho);
            h->Tabela[i].estado = Livre; // podia fazer depois (marcando como apagado aqui e depois Livre)
            while(h->Tabela[index].estado == Ocupado)
                index = (index + 1) % h->tamanho;
            h->Tabela[index].estado = Ocupado;
            h->Tabela[index].info = h->Tabela[i].info;
            h->Tabela[index].k = h->Tabela[i].k;
        }
    }
}

// Exercicio 37

void growHeap(Heap *h) {
    h->size *= 2;
    h->heap = realloc(h->heap, h->size);
}

void insertHeap(Heap *h, int x) {
    if(h->used == h->size)
        growHeap(h);

    h->heap[h->used] = x;
    bubbleUp(h, h->used++);
}

// Exercicio 39

int deepest(AVLTree *a) {
    int level = 0;
    // só paro quando encontrar um nodo que não tem nada para a esquerda ou para a direita
    // será um dos nodos do último nível
    while(*a && (*a)->val == Bal && !(*a)->esq && !(*a)->dir) {
        if ((*a)->bal == Left)
            *a = (*a)->esq;
        else
            *a = (*a)->dir;
        level++;
    }

    return level;
}

// Exercicio 40

#define HSIZE 1000

int hash (int chave, int size);

typedef struct lista {
    int valor;
    struct lista *prox;
} *HashChain[HSIZE];

typedef struct celula {
    int estado; // 0 - Livre
                // 1 - Ocupado
                // 2 - Removido
    int valor;
} HashOpen[HSIZE];

int fromChain(HashChain h1, HashOpen h2) {
    int j = 0;
    for (int i = 0; i < HSIZE && j < HSIZE; i++) {
        struct list *temp = h1[i];
        if (temp) {
            while(temp) {
                h2[j].valor = temp->valor;
                h2[j++].estado = 1;
            }
        } else
            h2[j++].estado = 0;
    }
}

// Exercicio 42

#define LEFT 1
#define BAL 0
#define RIGHT -1

typedef struct avl {
    int value;
    int bal;
    struct avl *left, *right;
} *AVL;

AVL maisProfundo(AVL a) {
    AVL temp = a;

    // condição está bem ????
    while(temp && (temp->bal != BAL || temp->left || temp->right))
        temp = temp->bal == LEFT ? temp->left : temp->right;

    return temp;
}

// Exercicio 46

#define LIVRE 0
#define APAGADO 1
#define OCUPADO 2

struct entry {
    int value, status;
};

typedef struct thash {
    int ocupados, tamanho;
    struct entry *tabela;
} *THash;

void cutTable(THash h) {
    int size = (h->tamanho * 2) / 3;
    struct entry * new = calloc(size, sizeof(struct entry));

    for (int i = 0; i < h->tamanho; i++) {
        int index = hash(h->tabela[i].value, size);
        while(new[index].status != LIVRE)
            index = (index + 1) % size;

        new[index].value = h->tabela[i].value;
        new[index].status = OCUPADO;
    }

    free(h->tabela);
    h->tabela = new;
    h->tamanho = size;
}

int remove(THash h, int key) {
    if (h->ocupados == 0)
        return 0;

    int index = hash(key, h->tamanho);
    int count = 0;

    while(h->tabela[index].status != LIVRE && count < h->tamanho) {
        index = (index + 1) % h->tamanho;
        count++;
    }

    if (h->tabela[index].status == OCUPADO && h->tabela[index].value == key) {
        h->tabela[index].status = APAGADO;

        if (--(h->ocupados) / h->tamanho < 0.33)
            cutTable(h);
        return 1;
    }

    return 0;
}