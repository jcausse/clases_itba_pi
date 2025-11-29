#include <stdio.h>
#include <assert.h>

typedef struct node {
    int elem;
    struct node * tail;
};

typedef struct node * TList;

TList deleteAll(TList list1, TList list2){
    // Caso Base 1: Si se acaba list2, retorno list1 porque ese nodo y todos los que vienen
    //              despues se mantienen
    if (list2 == NULL){
        return list1;
    }

    // Caso Base 2: Si se acaba list1, retorno NULL porque llegue al final de la lista
    if (list1 == NULL){
        return NULL;
    }

    // Caso 1: Cuando los elementos coinciden
    if (list1->elem == list2->elem) {
        TList aux = list1->tail;
        free(list1);                            // Elimino el nodo actual
        return deleteAll(aux, list2->tail);     // Sigo el algoritmo a partir del nodo siguiente (avanzo sobre las dos listas)
    }

    // Caso 2: No coinciden, tengo que avanzar sobre solo una de las listas
    if (list1->elem > list2->elem) {
        list1->tail =  deleteAll(list1, list2->tail);
    }
    else {
        list1->tail = deleteAll(list1->tail, list2);
    }
    return list1;
}

int main(void) { 
    int list1_array[] = {1, 2, 3, 4, 5, 6, 7};

    int list2_array[] = {0, 1, 3, 5, 10, 11, 14};

    int res_array[] = {2, 4, 6, 7};
}
