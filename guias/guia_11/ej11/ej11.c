#include <stdio.h>
#include "vectorADT.h"
#include <assert.h>


int compInt (elemType source, elemType target) {
    return source - target;
}

int main(void) {
    
    vectorADT v = newVector(compInt, NULL);
    elemType elems[] = {1, 2, 10, 20, 100, -2, 4};
    elemType elems2[]= {1, 3, 4, 10, 22, 33};

    assert( getIdx(v, elems[2]) == -1);
    
    assert( put(v, elems, 7, 3) == 7);    // v queda {vacio, vacio, vacio, 1, 2, 10, 20, 100, -2, 4}
    assert(elementCount(v)==7);
    assert( getIdx(v, 1) == 3);
    assert( getIdx(v, 2) == 4);
    assert( getIdx(v, 10) == 5);
    assert( getIdx(v, 22) == -1);
    assert( put(v, elems2, 6, 0) == 3);   // v queda {1, 3, 4, 1, 2, 10, 20, 100, -2, 4}
    assert( getIdx(v, 22) == -1);
    assert( getIdx(v, 1) == 0);
    assert( getIdx(v, 3) == 1);
    assert(elementCount(v)==10);
    assert( put(v, elems2, 6, 0) == 0);   // v queda igual
    assert( getIdx(v, 1) == 0);
    assert(elementCount(v)==10);
    deleteElement(v, 100);
    assert(elementCount(v)==10);
    deleteElement(v, 0);
    assert( getIdx(v, 1) == 3);
    assert(elementCount(v)==9);
    // Volvemos a borrar el 0, no deberia decrementar la cantidad
    deleteElement(v, 0);
    assert(elementCount(v)==9);
    assert( getIdx(v, 1) == 3);
    
    assert( put(v, elems2 + 5, 1, 12) == 1);   // v queda {vacio, 3, 4, 1, 2, 10, 20, 100, -2, 4. vacio, vacio, 33}
    assert(elementCount(v)==10);
    assert( getIdx(v, 33) == 12);
    assert( getIdx(v, 0) == -1);

    freeVector(v);
    
    puts("OK!");

    return 0;
}
