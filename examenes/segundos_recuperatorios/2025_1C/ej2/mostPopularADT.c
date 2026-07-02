#include <stdlib.h>
#include "mostPopularADT.h"

typedef struct Node {
    elemType elem;
    struct Node * next;
} Node;

struct mostPopularCDT {
    Node * first;
    Node * iter;
    unsigned int size;
    CompareFn cmp;
};

mostPopularADT newMostPopular(CompareFn cmp) {
    mostPopularADT ret = calloc(1, sizeof(struct mostPopularCDT));
    ret->cmp = cmp;
    return ret;
}

static void freeList(Node * l) {
    if (l == NULL) {
        return;
    }
    freeList(l->next);
    free(l);
}
 
void freeMostPopular(mostPopularADT tad) {
    freeList(tad->first);
    free(tad);
}

static Node * addRec(Node * l, elemType elem, CompareFn f, bool * result) {
    // Caso Base 1: Llegue al final de la lista, lo agrego
    if (l == NULL) {
        Node * ret = malloc(sizeof(Node));
        ret->elem = elem;
        ret->next = NULL;
        *result = true;
        return ret;
    }

    // Caso Base 2: Encontre el elemento (no hago nada)
    if (f(l->elem, elem) == 0) {
        *result = false;
        return l;
    }

    // Caso General: sigo buscando
    l->next = addRec(l->next, elem, f, result);
    return l;
}

unsigned int add(mostPopularADT tad, elemType elem) {
    bool result = false;

    tad->first = addRec(tad->first, elem, tad->cmp, &result);

    if (result) {
        (tad->size)++;
        return 1;
    }

    return 0;
}
   
unsigned int size(const mostPopularADT tad) {
    return tad->size;
}
  
void toBegin(mostPopularADT tad) {
    tad->iter = tad->first;
}

int hasNext(const mostPopularADT tad) {
    return tad->iter != NULL;
}  

elemType next(mostPopularADT tad) {
    if (!hasNext(tad)) {
        exit(1);
    }

    elemType ret = tad->iter->elem;
    tad->iter = tad->iter->next;
    return ret;
}

static Node * extractNodeOrNULL(Node * l, elemType target, CompareFn f, Node ** extractedNode) {
    // Caso Base 1: Llegue al final de la lista, y el elemento que buscaba no esta
    if (l == NULL) {
        *extractedNode = NULL;
        return NULL;
    }

    // Caso Base 2: Encontre el nodo que tiene el elemento que buscaba
    if (f(l->elem, target) == 0) {
        Node * aux = l->next;
        
        *extractedNode = l;
        (*extractedNode)->next = NULL;

        return aux;
    }

    // Caso General: Sigo buscando
    l->next = extractNodeOrNULL(l->next, target, f, extractedNode);
    return l;
}

int exist(mostPopularADT tad, elemType elem) {
    Node * extracted = NULL;

    tad->first = extractNodeOrNULL(tad->first, elem, tad->cmp, &extracted);

    // Si elem no estaba, extractNodeOrNULL me deja extracted en NULL
    if (extracted == NULL) {
        return 0;
    }

    // Si el nodo si estaba, lo muevo al principio
    extracted->next = tad->first;
    tad->first = extracted;

    // Si se movio un elemento, reinicio el iterador
    toBegin(tad);

    return 1;
}
