#include "ej13.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Node {
    elemType elem;
    struct Node * next;
} Node;

struct moveToFrontCDT {
    elemTypeComparator cmp;
    unsigned int size;
    Node * first;
    Node * iterator;
};

moveToFrontADT newMoveToFront(elemTypeComparator cmp) {
    moveToFrontADT ret = malloc(sizeof(struct moveToFrontCDT));
    ret->cmp = cmp;
    ret->size = 0;
    ret->first = NULL;
    ret->iterator = NULL;
    return ret;
}

static void freeList(Node * l) {
    if (l == NULL) {
        return;
    }
    freeList(l->next);
    free(l);
}

void freeMoveToFront(moveToFrontADT m) {
    freeList(m->first);
    free(m);
}

static Node * addToList(Node * l, elemType elem, elemTypeComparator cmp, bool * added) {
    // Caso base 1: Llego al final sin encontrarlo -> no se repite
    if (l == NULL) {
        Node * newNode = malloc(sizeof(Node));
        newNode->elem = elem;
        newNode->next = NULL;
        *added = true;
        return newNode;
    }

    // Caso base 2: El elemento esta repetido -> no hago nada
    if (cmp(l->elem, elem) == 0) {
        *added = false;
        return l;
    }

    // Caso general: Avanzo hasta encontrar el repetido o hasta el final
    l->next = addToList(l->next, elem, cmp, added);
    return l;
}

unsigned int add(moveToFrontADT moveToFront, elemType elem) {
    bool added;
    moveToFront->first = addToList(moveToFront->first, elem, moveToFront->cmp, &added);
    if (added) {
        (moveToFront->size)++;
    }
    return added;
}

unsigned int size(moveToFrontADT moveToFront) {
    return moveToFront->size;
}

void toBegin(moveToFrontADT moveToFront) {
    moveToFront->iterator = moveToFront->first;
}

int hasNext(moveToFrontADT moveToFront) {
    return moveToFront->iterator != NULL;
}

elemType next(moveToFrontADT moveToFront) {
    assert(moveToFront->iterator != NULL);
    elemType ret = moveToFront->iterator->elem;
    moveToFront->iterator = moveToFront->iterator->next;
    return ret;
}

static Node * popFromList(Node * l, elemType elem, elemTypeComparator cmp, Node ** res) {
    // Caso base 1: Llego al final sin encontrarlo -> el resultado es NULL
    if (l == NULL) {
        *res = NULL;
        return NULL;
    }

    // Caso base 2: El elemento se encontro -> lo quito de la lista, y devuelvo un puntero a ese nodo
    if (cmp(l->elem, elem) == 0) {
        Node * toReturn = l->next;
        l->next = NULL;                 // Quitarle al nodo que extraje la referencia al que era su siguiente
        *res = l;                       // Voy a retornar el nodo extraido
        return toReturn;
    }

    // Caso general: Avanzo hasta encontrar el repetido o hasta el final
    l->next = popFromList(l->next, elem, cmp, res);
    return l;
}

elemType * get(moveToFrontADT moveToFront, elemType elem) {
    elemType * toReturn = NULL;
    Node * res;
    
    moveToFront->first = popFromList(moveToFront->first, elem, moveToFront->cmp, &res);

    if (res != NULL) {
        res->next = moveToFront->first;
        moveToFront->first = res;

        toReturn = malloc(sizeof(elemType));
        *toReturn = res->elem;
    }

    return toReturn;
}
