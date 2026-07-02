#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node { 
   const char * person; 
   unsigned int popularity; 
   struct node * tail; 
} node; 
 
typedef node * TList;

// SOLUCION QUE HICE YO
TList upPop(TList l, const char * name, const unsigned int pop) {
    // Caso base 1: Llegue al final de la lista y no encontre a la persona que buscaba
    if (l == NULL) {
        struct node * newNode = malloc(sizeof(struct node));
        newNode->person = strdup(name);    // Hago este strdup por si en algun momento se probara pasando un char[] en lugar del string constante
        newNode->popularity = pop;
        newNode->tail = NULL;
        return newNode;
    }

    // Caso base 2: Encuentro a la persona
    if (strcmp(l->person, name) == 0) {
        l->popularity += pop;
        return l;
    }

    // Caso general:
    TList ret = upPop(l->tail, name, pop);      // Avanzo en la lista hasta el final, y cuando vuelvo

    // Caso 1: La popularidad del nodo actual es mayor o igual que la del nodo que me devolvieron.
    //         En este caso NO intercambio los nodos.
    if (l->popularity >= ret->popularity) {
        l->tail = ret;
        return l;    
    }

    // Caso 2: La popularidad del nodo actual es menor que la del nodo que me devolvieron. En este caso
    //         intercambio el nodo actual con el que me devolvieron, y vuelvo a devolver el mismo.
    l->tail = ret->tail;        // Mi nuevo nodo siguiente es el siguiente al devuelto
    ret->tail = l;              // El siguiente del devuelto soy yo
    return ret;                 // En las dos lineas de arriba me intercambie con el devuelto, y devuelvo siempre
                                // el nodo con mas popularity
}

// OTRA SOLUCION MUY BUENA, PROPUESTA POR UN ALUMNO
/*
TList upPop(TList list, const char * name, unsigned int pop){
    // Caso base 1: se agrega al final de la lista la persona nueva
    if (list == NULL) {
        TList new = malloc(sizeof(*new));
        new->person = strdup(name);
        new->popularity = pop;
        new->tail = NULL;
        return new;
    }

    // Caso base 2: encontro a la persona: aumenta pop
    if (strcmp(name, list->person) == 0) {
        list->popularity += pop;
        return list;
    }
    
    list->tail = upPop(list->tail, name, pop);

    // La lista me quedo desordenada, voy intercambiando nodos hasta que me quede ordenada.
    if (list->tail->popularity > list->popularity) {
        TList aux = list->tail;
        TList aux2 = aux->tail;
        aux->tail = list;
        list->tail = aux2;
        return aux;
    }
    
    return list;
}
*/

void freeList(TList l) {
    if (l == NULL) {
        return;
    }
    freeList(l->tail);
    free((char *) l->person);
    free(l);
}

int main(void) { 
    TList myList = NULL;                // Lista Vacía 
    myList = upPop(myList, "Cato", 5);  // {"Cato",5} 
    myList = upPop(myList, "Paco", 3);  // {"Cato",5} -> {"Paco",3} 
    myList = upPop(myList, "Mon" , 4);  // {"Cato",5} -> {"Mon" ,4} -> {"Paco",3} 
    myList = upPop(myList, "Cato", 1);  // {"Cato",6} -> {"Mon" ,4} -> {"Paco",3} 
    myList = upPop(myList, "Mon" , 2);  // {"Cato",6} -> {"Mon" ,6} -> {"Paco",3} 
    myList = upPop(myList, "Paco", 2);  // {"Cato",6} -> {"Mon" ,6} -> {"Paco",5} 
    myList = upPop(myList, "Paco", 2);  // {"Paco",7} -> {"Cato",6} -> {"Mon" ,6} 
    myList = upPop(myList, "Mon" , 1);  // {"Paco",7} -> {"Mon" ,7} -> {"Cato",6} 
    // Se agrega otro (PACO no es lo mismo que Paco) 
    myList = upPop(myList, "PACO" , 7);   
                            // {"Paco",7} -> {"Mon",7} -> {"PACO",7} -> {"Cato",6} 
    myList = upPop(myList, "Cato" , 8);   
                            // {"Cato",14} -> {"Paco",7} -> {"Mon",7} -> {"PACO",7} 
    
    freeList(myList);
    puts("OK"); 
    return 0; 
}
