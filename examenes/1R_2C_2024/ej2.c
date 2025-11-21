#include <stdio.h>
#include <assert.h>

#define END -1

void copiarRestantes(int l[], int r, int * w) {
    while (l[r] != END) {
        l[*w] = l[r];
        (*w)++;
        r++;
    }
}

// TL;DR: Eliminar de lista1 todos los elementos que se encuentren en
//        lista2, y viceversa, sabiendo que no tienen repetidos y estan
//        ordenados ascendente.
void actualizarTareas(int l1[], int l2[]) {
    int r1 = 0, r2 = 0, w1 = 0, w2 = 0; // r = read, w = write

    // Mientras ambos vectores tengan elementos
    while (l1[r1] != END && l2[r2] != END) {
        
        // Caso 1: Si coinciden, elimino ambos (no copiando, elimino)
        if (l1[r1] == l2[r2]) {
            r1++;
            r2++;
        }

        // Caso 2: Si no coinciden, avanzo sobre el vector que
        //         tenga el elemento mas chico. Ademas, copio sobre
        //         el que avanzo porque esos elementos NO deben borrarse

        // Caso 2.1: El elemento mas chico esta sobre la lista l1
        else if (l1[r1] < l2[r2]) {
            l1[w1] = l1[r1];
            r1++;
            w1++;
        }

        // Caso 2.2: El elemento mas chico esta sobre la lista l2
        else {
            l2[w2] = l2[r2];
            r2++;
            w2++;
        }
    }

    // Cuando sale del primer while, se puede terminar 1 o las 2 a la vez
    // En cualquier caso, lo que hago es copiar todos los elementos restantes
    // de la que no se termino
    copiarRestantes(l1, r1, &w1);
    copiarRestantes(l2, r2, &w2);

    l1[w1] = END;
    l2[w2] = END;
}


int main(void) {
    int lista1[] = {1, 3, 5, 7, 100, -1};
    int lista2[] = {3, 4, 5, 6, 7, -1};
    
    actualizarTareas(lista1, lista2);
    assert(lista1[0]==1 && lista1[1]==100 && lista1[2]==-1);
    assert(lista2[0]==4 && lista2[1]==6 && lista2[2]==-1);
    
    actualizarTareas(lista1, lista2);
    assert(lista1[0]==1 && lista1[1]==100 && lista1[2]==-1);
    assert(lista2[0]==4 && lista2[1]==6 && lista2[2]==-1);
    
    int lista3[] = {-1};
    actualizarTareas(lista1, lista3);
    assert(lista1[0]==1 && lista1[1]==100 && lista1[2]==-1);
    assert(lista3[0]==-1);

    int lista4[] = {4, 6, -1};
    actualizarTareas(lista2, lista4);
    assert(lista2[0]==-1);
    assert(lista4[0]==-1);
    
    puts("OK!");
    
    return 0;
}
