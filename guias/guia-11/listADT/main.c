#include <stdio.h>
#include "list.h"
#include <assert.h>
#include <stdlib.h>

int main() {
    List myList = newList();  // lista vacia

    assert(isEmpty(myList));

    assert(belongs(myList, 10)==0);

    int * vec2 = toArray(myList);
    int dim2 = size(myList);
    for(int i=0; i < dim2; i++) {
        printf("%d\n", vec2[i]);
    }
    free(vec2);
    assert(size(myList)==0);
    // Agregamos el numero 10
    myList = add(myList, 10);
    assert(! isEmpty(myList));
    assert(size(myList)==1);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==0);
    printf("%p \n", myList);

    // Volvemos a agregar, no tiene  que agregarlo
    myList = add(myList, 10);
    assert(! isEmpty(myList));
    assert(size(myList)==1);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==0);
    printf("%p \n", myList);

    myList = add(myList, 15);
    assert(! isEmpty(myList));
    assert(size(myList)==2);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==1);
    printf("%p \n", myList);

    myList = add(myList, 5);
    assert(! isEmpty(myList));
    assert(size(myList)==3);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==1);
    printf("%p \n", myList);

    // Borrar uno que no existe
    myList = delete(myList, 50);
    assert(! isEmpty(myList));
    assert(size(myList)==3);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==1);
    assert(belongs(myList, 5)==1);
    assert(belongs(myList, 50)==0);
    printf("%p \n", myList);

    myList = delete(myList, 5);
    assert(! isEmpty(myList));
    assert(size(myList)==2);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==1);
    assert(belongs(myList, 5)==0);
    printf("%p \n", myList);

    myList = delete(myList, 15);
    assert(! isEmpty(myList));
    assert(size(myList)==1);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==0);
    assert(belongs(myList, 5)==0);
    printf("%p \n", myList);

    myList = delete(myList, 10);
    assert(isEmpty(myList));
    assert(size(myList)==0);
    printf("%p \n", myList);

    // Agregamos uno mas para probar el free
    myList = add(myList, 10);
    myList = add(myList, 5);
    myList = add(myList, 15);

    List aux = myList;
    while ( !isEmpty(aux)) {
        printf("%d \t", head(aux));
        aux = tail(aux);
    }
    putchar('\n');

    aux = myList;
    int suma = 0;
    while ( !isEmpty(aux)) {
        suma += head(aux);
        aux = tail(aux);
    }
    assert(suma==30);

    myList = add(myList, 5);
    assert(! isEmpty(myList));
    assert(size(myList)==3);
    assert(belongs(myList, 10)==1);
    assert(belongs(myList, 15)==1);
    printf("%p \n", myList);

    int * vec = toArray(myList);
    int dim = size(myList);
    suma=0;
    for(int i=0; i < dim; i++) {
        suma += vec[i];
    }
    assert(suma==30);
    free(vec);

    // Agregado
    // La lista es 5 -> 10 -> 15
    assert(get(myList, 0) == 5);
    assert(get(myList, 1) == 10);
    assert(get(myList, 2) == 15);
    //

    freeList(myList);

    

    puts("OK!!!");
    return 0;
}
