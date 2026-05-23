#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "utillist.h"

typedef struct nodeBrief * TListBrief; 

typedef struct nodeBrief {
    int elem;
    size_t count;
    struct nodeBrief * tail;
} TNodeBrief;


TListBrief comprimeList(const List list) {
    if (list == NULL) {
        return NULL;
    }

    TNodeBrief * current_node = comprimeList(list->tail);

    if (list->tail == NULL || list->head < list->tail->head) {
        TNodeBrief * new_node = malloc(sizeof(TNodeBrief));
        new_node->elem = list->head;
        new_node->count = 1;
        new_node->tail = current_node;
        return new_node;
    }

    (current_node->count)++;
    return current_node;
}

// Auxiliar para que pase el test con sanitizer
void freeListBrief(TListBrief lb) {
    if ( lb == NULL)
        return;
    freeListBrief(lb->tail);
    free(lb);
}

int main(void) {
    int v[] = {1,1,2,3,3,3,3,3,10,100,100,998};
    List list = fromArray(v, sizeof(v)/sizeof(v[0]));
    TListBrief bf = comprimeList(list);

    TListBrief aux = bf;
    assert(aux->elem ==1 && aux->count == 2);

    aux = aux->tail;
    assert(aux->elem ==2 && aux->count == 1);

    aux = aux->tail;
    assert(aux->elem ==3 && aux->count == 5);

    aux = aux->tail;
    assert(aux->elem ==10 && aux->count == 1);

    aux = aux->tail;
    assert(aux->elem ==100 && aux->count == 2);

    aux = aux->tail;
    assert(aux->elem ==998 && aux->count == 1);

    aux = aux->tail;
    assert(aux == NULL);

    freeList(list);
    freeListBrief(bf);
    
    printf ("OK!\n");
    return 0;
}
