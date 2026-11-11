#ifndef EJ3_H
#define EJ3_H

typedef struct node {
    int head;
    struct node * tail;
} node;

typedef node * TList;

/**
 * Elimina recursivamente de list todos los elementos que coincidan con value,
 * y deja en *count cuántos elementos se eliminaron.
 * 
 * list: una lista (puede estar vacía)
 * value: un número entero
 * count: un puntero a int no inicializado
 * 
 * Retorna la lista resultante.
 */
TList deleteAll(TList list, int value, int * count);

#endif // EJ3_H
