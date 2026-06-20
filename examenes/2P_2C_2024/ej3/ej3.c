#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
    char head;
    int hits;
    struct node * tail;
} node;

typedef node * TList;

TList addElem(TList l, char c) {
    // Caso base 1: Llegue al final de la lista sin encontrar el elemento -> lo agrego con 0 hits
    if (l == NULL) {
        TList newNode = malloc(sizeof(node));
        newNode->head = c;
        newNode->hits = 0;
        newNode->tail = NULL;
        return newNode;
    }

    // Caso base 2: Encontre el elemento -> le agrego un hit
    if (l->head == c) {
        (l->hits)++;
        return l;
    }

    // Caso general
    // Paso 1: Voy hasta el final para caer en algun caso base antes de mover ningun nodo
    TList res = addElem(l->tail, c);
    
    if (l->hits < res->hits) {
        l->tail = res->tail;
        res->tail = l;
        return res;
    }

    l->tail = res;
    return l;
}

void freeList(TList l) {
    if (l == NULL) {
        return;
    }
    freeList(l->tail);
    free(l);
}

int main(void) {
    TList l = NULL;

    l = addElem(l, 'X');
    l = addElem(l, 'X');
    l = addElem(l, 'Z');
    
    // (X,1) -> (Z,0)
    assert(l->head == 'X'); 
    assert(l->hits == 1);
    assert(l->tail->head == 'Z');
    assert(l->tail->hits == 0);

    l = addElem(l, 'A');

    // (X,1) -> (Z,0) -> (A,0) o bien (X,1) -> (A,0) -> (Z,0)
    assert(l->head == 'X');
    assert((l->tail->head == 'Z' && l->tail->tail->head == 'A') || (l->tail->head == 'A' && l->tail->tail->head == 'Z'));
    
    l = addElem(l, 'A');
    l = addElem(l, 'A');
    
    // (A,2) -> (X,1) -> (Z,0)
    assert(l->head == 'A');
    assert(l->hits == 2);
    assert(l->tail->head == 'X');
    assert(l->tail->hits == 1);
    assert(l->tail->tail->head == 'Z');
    assert(l->tail->tail->hits == 0);
    assert(l->tail->tail->tail == NULL);
    
    freeList(l);
    puts( "OK");
    return 0;
}
