#include "ej12.h"
#include <stdlib.h>

typedef struct Node {
    elemType elem;
    struct Node * nextByInsertionOrder;         // Proximo nodo en el orden de insercion
    struct Node * nextByAscendingOrder;         // Proximo nodo en el orden ascendente
} Node;

struct listCDT {
    // Punteros de la lista, en ambos ordenes
    Node * firstByInsertionOrder;
    Node * lastByInsertionOrder;
    Node * firstByAscendingOrder;
    Node * lastByAscendingOrder;
    
    // Funcion comparadora
    Comparator ascendingOrderComparator;

    // Iteradores
    Node * insertionOrderIterator;
    Node * ascendingOrderIterator;
};

/* Retorna una lista vacía.
*/
listADT newList(Comparator c) {
    if (c == NULL) {
        return NULL;
    }

    listADT newList = malloc(sizeof(struct listCDT));

    newList->firstByInsertionOrder = NULL;
    newList->lastByInsertionOrder = NULL;

    newList->firstByAscendingOrder = NULL;
    newList->lastByAscendingOrder = NULL;
    
    newList->ascendingOrderComparator = c;
    
    newList->insertionOrderIterator = NULL;
    newList->ascendingOrderIterator = NULL;
    
    return newList;
}

static Node * createNewNode(elemType elem, Node * nextAscending) {
    Node * toReturn = malloc(sizeof(Node));
    toReturn->elem = elem;
    toReturn->nextByInsertionOrder = NULL;
    toReturn->nextByAscendingOrder = nextAscending;
    return toReturn;
}

/* Agrega un elemento. Si ya estaba no lo agrega */
void add(listADT list, elemType elem) {
    
    // Caso lista vacia
    if (list->firstByInsertionOrder == NULL) {
        Node * newNode = createNewNode(elem, NULL);
        list->firstByInsertionOrder = newNode;
        list->lastByInsertionOrder = newNode;
        list->firstByAscendingOrder = newNode;
        list->lastByAscendingOrder = newNode;
        return;
    }
    
    // Caso en que el elemento a insertar coincide con el ultimo en orden ascendente
    if (list->ascendingOrderComparator(elem, list->lastByAscendingOrder->elem) == 0) {
        return;
    }

    Node * newNode = NULL;

    // Caso en que el elemento a insertar es menor que el primero en orden ascendente
    // Me evito tener que recorrer toda la lista solo para darme cuenta de que el elemento nuevo iba al pincipio
    if (list->ascendingOrderComparator(elem, list->firstByAscendingOrder->elem) < 0) {
        newNode = createNewNode(elem, list->firstByAscendingOrder);
        list->firstByAscendingOrder = newNode;
    }

    // Caso en que el elemento a insertar es mayor que el ultimo en orden ascendente
    // Me evito tener que recorrer toda la lista solo para darme cuenta de que el elemento nuevo iba al final
    else if (list->ascendingOrderComparator(elem, list->lastByAscendingOrder->elem) > 0) {
        newNode = createNewNode(elem, NULL);
        list->lastByAscendingOrder->nextByAscendingOrder = newNode;
        list->lastByAscendingOrder = newNode;
    }

    // Caso general: cuando el nuevo elemento es mayor estricto que el primero y menor estricto que el ultimo
    else {
        Node * current = list->firstByAscendingOrder, * last = NULL;
        int result;

        while ((result = list->ascendingOrderComparator(elem, current->elem)) > 0) {
            last = current;
            current = current->nextByAscendingOrder;
        }

        // Si result dio cero, el elemento esta repetido. No hago nada
        if (result < 0) {
            newNode = createNewNode(elem, current);
            last->nextByAscendingOrder = newNode;
        }
    }

    // Para todos los casos anteriores, se asigna el nuevo nodo como siguiente en orden de insercion
    // El null check es para que no tenga problemas si hubo repetidos, ya que el newNode nunca se creo en ese caso
    if (newNode != NULL) {
        list->lastByInsertionOrder->nextByInsertionOrder = newNode;
        list->lastByInsertionOrder = newNode;
    }
}

/* Resetea el iterador que recorre la lista en el orden de inserción */
void toBegin(listADT list) {
    list->insertionOrderIterator = list->firstByInsertionOrder;
}

/* Retorna 1 si hay un elemento siguiente en el iterador que
** recorre la lista en el orden de inserción. Sino retorna 0 */
int hasNext(listADT list) {
    return list->insertionOrderIterator != NULL;
}

/* Retorna el elemento siguiente del iterador que recorre la lista en el orden de inserción. 
** Si no hay un elemento siguiente o no se invocó a toBegin aborta la ejecución.
*/
elemType next(listADT list) {
    if (!hasNext(list)) {
        exit(1);
    }
    elemType toReturn = list->insertionOrderIterator->elem;
    list->insertionOrderIterator = list->insertionOrderIterator->nextByInsertionOrder;
    return toReturn;
}

/* Resetea el iterador que recorre la lista en forma ascendente */
void toBeginAsc(listADT list) {
    list->ascendingOrderIterator = list->firstByAscendingOrder;
}

/* Retorna 1 si hay un elemento siguiente en el iterador que
** recorre la lista en forma ascendente. Sino retorna 0 */
int hasNextAsc(listADT list) {
    return list->ascendingOrderIterator != NULL;
}

/* Retorna el elemento siguiente del iterador que recorre la lista en forma ascendente. 
** Si no hay un elemento siguiente o no se invocó a toBeginAsc aborta la ejecución.
*/
elemType nextAsc(listADT list) {
    if (!hasNextAsc(list)) {
        exit(1);
    }
    elemType toReturn = list->ascendingOrderIterator->elem;
    list->ascendingOrderIterator = list->ascendingOrderIterator->nextByAscendingOrder;
    return toReturn;
}

/* Libera la memoria reservada por la lista */
void freeList(listADT list) {
    Node * current = list->firstByInsertionOrder, * next;
    while(current != NULL) {
        next = current->nextByInsertionOrder;
        free(current);
        current = next;
    }
    free(list);
}
