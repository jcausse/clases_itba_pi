#ifndef SKIPLIST_SKIPLISTADT_H
#define SKIPLIST_SKIPLISTADT_H

typedef int elemType;

typedef int (* compare) (elemType, elemType);

typedef struct skipListCDT * skipListADT;

/**
 *
 * @param max_level máxima altura del vector de "tails". Si es 1 es equivalente a una lista lineal
 * @return
 */
skipListADT createSkipList(unsigned char max_level, compare cmp);

/**
 * Inserta un nuevo elemento en forma ordenada. Acepta repetidos
 * @param list
 * @param key
 */
void insert(skipListADT list, elemType key);

int search(skipListADT list, elemType key);

void toBegin(skipListADT list);

int hasNext(const skipListADT list);

/**
 * Si no hay un elemento siguiente asigna ENODATA a errno y retorna un valor incierto
 * @param list
 * @return
 */
elemType next(skipListADT list);

/**
 * Libera todos los recursos de la lista
 * @param list
 */
void freeList(skipListADT list);

/**
 * Unicamente para testing, para verificar las alturas.
 * Muestra las distintas "listas" de acuerdo a la altura, asumiendo que elemType es int
 * SOLO PARA TESTING
 * @param list
 */
void display(skipListADT list);

#endif
