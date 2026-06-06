#include "ej13.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static int compare (elemType e1, elemType e2) {
    return e1.code - e2.code;
}

int main(void) {
    moveToFrontADT p = newMoveToFront(compare);

    elemType aux = {1, "uno"};
    assert(add(p, aux) == 1);

    strcpy(aux.name, "dos");
    assert(add(p, aux) == 0);
    
    aux.code = 2;
    assert(add(p, aux) == 1);

    aux.code = 3;
    strcpy(aux.name, "tres");
    assert(add(p, aux) == 1);

    aux.code = 4;
    strcpy(aux.name, "cuatro");
    assert(add(p, aux) == 1);

    toBegin(p);

    while (hasNext(p)) {
        aux = next(p);
        printf("%d %s ", aux.code, aux.name);
    }
    putchar('\n');

    aux.code = 5;
    elemType * q = get(p, aux);
    assert(q == NULL);
    
    aux.code = 3;
    q = get(p, aux);
    printf("%d %s\n", q->code, q->name);
    free(q);

    toBegin(p);
    while (hasNext(p)) {
        aux = next(p);
        printf("%d %s ", aux.code, aux.name);
    }
    putchar('\n');
    
    freeMoveToFront(p);
    puts("OK!");
    return 0;
}
