#include <stdio.h>
#include <assert.h>
#include "skipListADT.h"
#include <stdlib.h>

int cmpInt(int n1, int n2) {
    return n1-n2;
}

int main() {
    skipListADT list = createSkipList(10, cmpInt);

    insert(list, 3);
    insert(list, 3);
    insert(list, 19);
    insert(list, 3);
    insert(list, 17);

    assert(search(list, 19));
    assert(search(list, 3));
    assert(search(list, 17));
    assert(!search(list, 1));
    assert(!search(list, -3));
    assert(!search(list, 100));

    toBegin(list);
    assert(hasNext(list));
    assert(next(list)==3);
    assert(next(list)==3);
    assert(next(list)==3);
    assert(next(list)==17);
    assert(next(list)==19);
    assert(!hasNext(list));

    for(int i=0; i<100; i++) {
        insert(list, rand()%200);
    }
    display(list);
    putchar('\n');
    freeList(list);

    // Probamos de un solo nivel
    list = createSkipList(1, cmpInt);
    for(int i=0; i<50; i++) {
        insert(list, rand()%100);
    }

    display(list);
    freeList(list);

    puts("OK!");
    return 0;
}