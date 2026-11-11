#include "ej3.h"
#include <stdlib.h>

TList deleteAll(TList list, int value, int * count) {
    if (list == NULL) {
        *count = 0;
        return NULL;
    }

    TList next = deleteAll(list->tail, value, count);

    if (list->head == value) {
        free(list);
        (*count)++;
        return next;
    }
    list->tail = next;
    return list;
}
