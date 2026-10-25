#include "utillist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int sumAll(List l) {
    /* Caso Base: Lista vacia. Suma cero. */
    if (l == NULL) {
        return 0;
    }

    /* Caso General: La lista no es vacia.  */
    return l->head + sumAll(l->tail);
}

bool odds_or_empty(List l) {
    /* Caso Base */
    if (l == NULL) {
        return true;
    }

    /* Caso General */
    return l->head % 2 != 0 && odds_or_empty(l->tail);
}

bool odds_and_not_empty(List l) {
    /* Caso Base */
    if (l == NULL) {
        return false;
    }

    /* Caso General */
    return l->head % 2 != 0 && (odds_and_not_empty(l->tail) || l->tail == NULL);
}

int tests_juani() {
    /* EJERCICIO 1 A */

    // Suma 17
    int arr[] = {5, 4, -1, 2, 9, 0, 6, 7, -9, -6};
    List l = fromArray(arr, sizeof(arr) / sizeof(arr[0]));
    assert(sumAll(l) == 17);
    freeList(l);

    // La lista vacia suma 0
    assert(sumAll(NULL) == 0);

    // Lista con un unico elemento
    List l2 = malloc(sizeof(struct node));
    l2->head = 15;
    l2->tail = NULL;
    assert(sumAll(l2) == 15);
    free(l2);

    // Otra lista de prueba
    int arr3[] = {1, 5, 3};
    List l3 = fromArray(arr3, sizeof(arr3) / sizeof(arr3[0]));
    assert(sumAll(l3) == 9);
    freeList(l3);


    /* EJERCICIO 1 B */

    int arr4[] = {1, 3, 5, 7, 9};
    List l4 = fromArray(arr4, sizeof(arr4) / sizeof(arr4[0]));
    assert(odds_or_empty(l4));
    assert(odds_and_not_empty(l4));
    freeList(l4);

    int arr5[] = {1, 3, 6, 7, 9};
    List l5 = fromArray(arr5, sizeof(arr5) / sizeof(arr5[0]));
    assert(!odds_or_empty(l5));
    assert(!odds_and_not_empty(l5));
    freeList(l5);

    assert(odds_or_empty(NULL));
    assert(!odds_and_not_empty(NULL));

    puts("OK!");
    return 0;
}

void tests_catedra() {

	assert(sumAll(NULL) == 0);
	assert(odds_or_empty(NULL) == 1 );
	assert(odds_and_not_empty(NULL) == 0 );

	int v [] = {1, 3, 5, -1, 0, 2, 4, 3};
	List l1 = fromArray(v, 8);
	assert(sumAll(l1) == 17);
	assert(odds_or_empty(l1) == 0);
	assert(odds_and_not_empty(l1) == 0);
	freeList(l1);

	l1 = fromArray(v, 4);
	assert(sumAll(l1) == 8);
	assert(odds_or_empty(l1) == 1);
	assert(odds_and_not_empty(l1) == 1);
	freeList(l1);

	l1 = fromArray(v+4, 3);
	assert(sumAll(l1) == 6);
	assert(odds_or_empty(l1) == 0);
	assert(odds_and_not_empty(l1) == 0);
	freeList(l1);
	
	puts("OK!");
}

int main() {
    tests_catedra();
    tests_juani();
    return 0;
}
