#include "listADT.h"
#include <stdlib.h>

typedef struct node {
    elemType        head;
    struct node *   tail;
} node_t;

struct listCDT {
    node_t *        first;
    size_t          size;
    comparator      cmp;
};

listADT newList(comparator cmp) {
    listADT l = malloc(sizeof(struct listCDT));
    l->first = NULL;
    l->size = 0;
    l->cmp = cmp;
    return l;
}

static void freeListRecursive(node_t * l) {
    if (l == NULL) {
        return;
    }
    freeListRecursive(l->tail);
    free(l);
}

void freeList(listADT l) {
    freeListRecursive(l->first);
    free(l);
}

static node_t * addRecursive(node_t * l, elemType e, comparator cmp, bool * added) {
    int comparisonResult = 0;

    // Caso Base 1: sublista vacia o lugar encontrado para el nuevo elemento, agregar y retornar
    if (l == NULL || (comparisonResult = cmp(l->head, e)) > 0) {
        node_t * newNode = malloc(sizeof(node_t));
        newNode->head = e;
        newNode->tail = l;
        *added = true;
        return newNode;
    }

    // Caso Base 2: elemento repetido
    if (comparisonResult == 0) {
        *added = false;
        return l;
    }

    // Caso General: recursividad (rearma la lista para atras)
    l->tail = addRecursive(l->tail, e, cmp, added);
    return l;
}

bool add(listADT l, elemType e) {
    bool added = false;
    l->first = addRecursive(l->first, e, l->cmp, &added);   // Actualiza el first
    if (added) {
        l->size++;
    }
    return added;
}

static node_t * removeRecursive(node_t * l, elemType e, comparator cmp, bool * removed) {
    int comparisonResult = 0;

    // Caso Base 1: sublista vacia o encuentro un elemento mayor
    if (l == NULL || (comparisonResult = cmp(l->head, e)) > 0) {
        *removed = false;
        return l;
    }

    // Caso Base 2: elemento encontrado
    if (comparisonResult == 0) {
        node_t * aux = l->tail;
        free(l);
        *removed = true;
        return aux;
    }
    
    // Caso General: recursividad (rearma la lista para atras)
    l->tail = removeRecursive(l->tail, e, cmp, removed);
    return l;
}

bool remove(listADT l, elemType e) {
    bool removed = false;
    l->first = removeRecursive(l->first, e, l->cmp, &removed);   // Actualiza el first
    if (removed) {
        l->size--;
    }
    return removed;
}

size_t size(listADT l) {
    return l->size;
}

bool isEmpty(listADT l) {
    return l->size == 0;
}

bool belongsRecursive(const node_t * l, elemType e, comparator cmp) {
    if (l == NULL) {
        return false;
    }

    if (cmp(l->head, e) == 0) {
        return true;
    }

    return belongsRecursive(l->tail, e, cmp);
}

bool belongs(listADT l, elemType e) {
    return belongsRecursive(l->first, e, l->cmp);
}
