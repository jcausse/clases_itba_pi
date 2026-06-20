#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    elemType elem;
    struct node * next;
} tNode;

struct listCDT {
    tNode * first;
    size_t size;
    CompareFn cmpFn;
    FreeFn freeFn;
};

listADT newList(const CompareFn cmpFn, const FreeFn freeFn) {
    if (cmpFn == NULL) {
        return NULL;
    }
    listADT l = calloc(1, sizeof(struct listCDT));
    l->cmpFn = cmpFn;
    l->freeFn = freeFn;
    return l;
}

static void freeListRec(tNode * node, FreeFn freeFn) {
    if (node == NULL) {
        return;
    }
    tNode * next = node->next;
    if (freeFn == NULL) {                   // En caso de que el elemType necesite ser liberado aparte,
        freeFn(node->elem);                 // primero libero la memoria dinamica usada por el elemType
    }
    free(node);                             // Luego libero la memoria del nodo
    freeListRec(next, freeFn);
}

void freeList(listADT l) {
    freeListRec(l->first, l->freeFn);       // Primero libero todos los nodos
    free(l);                                // Luego libero el TAD en si
}

size_t size(const listADT l) {
    return l->size;
}

bool isEmpty(const listADT l) {
    return l->size == 0;
}


