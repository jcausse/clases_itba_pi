#include "vectorADT.h"
#include <stdlib.h>

#define ELEM_NOT_IN_USE     0
#define ELEM_IN_USE         1

typedef struct vectorElem {
    elemType elem;                  // El elemento
    unsigned char state;            // Flag de si esta usado o no
} vectorElem;

struct vectorCDT {
    CompareFunction cmpFn;          // Funcion de comparacion
    FreeFunction freeFn;            // Funcion para librerar memoria de elementos

    size_t size;                    // Cantidad de posiciones totales (libres + usados)
    size_t usage;                   // Cantidad de posiciones usadas

    vectorElem * storage;           // Vector dinamico para almacenar los elementos. Es de tamaño size
};

vectorADT newVector(CompareFunction cmpFn, FreeFunction freeFn) {
    // La funcion de comparacion es OBLIGATORIA (sin ella no puedo hacer el getIdx)
    if (cmpFn == NULL) {
        return NULL;
    }
    vectorADT ret = calloc(1, sizeof(struct vectorCDT));
    ret->cmpFn = cmpFn;
    ret->freeFn = freeFn;
    return ret;
}

void freeVector(vectorADT v) {
    size_t i;
    
    // Libero el elemento guardado en cada nodo (si corresponde)
    if (v->freeFn != NULL) {                                // Chequeo si la freeFn es distinto de NULL 1 sola vez
        for (i = 0; i < v->size; i++) {                     // Para cada elemento
            if (v->storage[i].state == ELEM_IN_USE) {       // Me fijo que este usado antes de hacerle el free (hacer el free)
                v->freeFn(v->storage[i].elem);              // sobre elementos no usados me puede traer problemas como doble free
            }                                               // o use-after-free, dependiendo de que haga la funcion freeFn
        }
    }

    // Libero el storage (el arreglo dinamico de nodos)
    free(v->storage);

    // Libero la memoria usada por el CDT en si
    free(v);
}

size_t put(vectorADT v, elemType * elems, size_t dim, size_t index) {
    size_t inserted = 0;

    if (index + dim >= v->size) {
        v->storage = realloc(v->storage, (dim + index) * sizeof(struct vectorElem));        // TODO: Review
    }

    for (size_t i = 0; i < dim; i++) {

    }

    return inserted;
}

int getIdx(vectorADT v, elemType elem) {
    size_t i;
    for (i = 0; i < v->size; i++) {                     // Para cada posicion del vector
        if (
            v->storage[i].state == ELEM_IN_USE          // Si la posicion esta en uso
            && 
            v->cmpFn(v->storage[i].elem, elem) == 0     // y el elemento en la posicion i coincide con el que busco
        ) {
            return i;                                   // Retorno la posicion
        }
    }
    return ELEM_NOT_FOUND;                              // Si no lo encuentro, retorno ELEM_NOT_FOUND
}

void deleteElement(vectorADT v, size_t index) {
    if (v->storage[index].state == ELEM_NOT_IN_USE) {
        return;
    }

    if (v->freeFn != NULL) {
        v->freeFn(v->storage[index].elem);
    }

    v->storage[index].state = ELEM_NOT_IN_USE;
    (v->usage)--;
}

int elementCount(vectorADT v) {
    return v->usage;
}
