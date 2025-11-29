#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char head;
    int hits;
    struct node * tail;
} node;

typedef node * TList;

TList addElem(TList l, char c) {
    // TODO
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
    assert(l->head == 'X'); assert(l->tail->head == 'Z');
    l = addElem(l, 'A');
    // (X,1) -> (Z,0) -> (A,0) o bien (X,1) -> (A,0) -> (Z,0)
    assert(l->head == 'X');
    assert((l->tail->head == 'Z' && l->tail->tail->head == 'A')
    || (l->tail->head == 'A' && l->tail->tail->head == 'Z'));
    l = addElem(l, 'A');
    l = addElem(l, 'A');
    assert(l->head == 'A');
    assert(l->tail->head == 'X');
    assert(l->tail->tail->head == 'Z');
    assert(l->tail->tail->tail == NULL);
    
    freeList(l);
    puts( "OK");
    return 0;
}
