/*
Que es un vector de apariciones?

Supongamos que se nos pide contar la cantidad de apariciones de cada elemento en un array de numeros
Podemos suponer que el array es:

unsigned char arr[] = {0, 1, 200, 3, 1, 3, 200, 1, 1, 1, 2, 4, 5, 200, 3, 1};

Cuantas veces aparece cada uno? Tengo dos formas de contestar esto:

1.  Para cada valor en el dominio, cuento la cantidad de veces que aparece.

    for (i = 0; i < dim; i++) {
        apariciones += arr[i] == value;
    }
    
    El problema es que esto es en extremo ineficiente. Si el vector es un vector de unsigned char (256
    posibilidades diferentes) debo recorrer 256 veces el vector para poder decir cuantas veces aparece
    cada elemento.

    VER muy_ineficiente

2.  Con un vector de apariciones:

    Un vector de apariciones es un vector CUYO TAMAÑO es igual al tamaño del dominio de aquello que queremos
    contar. Inicialmente arranca con todas las posiciones en cero, y cada vez que va apareciendo un
    elemento de ese dominio, como cada elemento tiene asociada una posicion en el vector de apariciones, se
    incrementa el contador asociado a ese elemento.

    Para este caso particular, como quiero contar cuantas veces aparece cada numero de un vector de unsigned char,
    el dominio es {0, 1, 2, ..., 253, 254, 255} (que son todos los posibles valores para unsigned char).

    Lo que se hace es se asigna para el valor 0 el indice 0, para el valor 1 el indice 1, ...
    ... para el valor n se usa el indice n

    VER vector_apariciones

*/

#include <stdio.h>
#include <limits.h>

unsigned int cont;

/* FORMA 1 */

unsigned int aparicion_elemento(unsigned char v[], unsigned int dim, unsigned char value) {
    unsigned int apariciones = 0;
    for (unsigned int i = 0; i < dim; i++) {
        apariciones += v[i] == value;
        cont++;
    }
    return apariciones;
}

void muy_ineficiente(unsigned char v[], unsigned int dim) {
    unsigned int apariciones;
    for (int i = 0; i < 256; i++) {
        apariciones = aparicion_elemento(v, dim, i);
        if (apariciones > 0) {
            printf("El valor %u aparece %u veces\n", i, apariciones);
        }
    }
}

/* FORMA 2 */

void vector_apariciones(unsigned char v[], unsigned int dim) {
    unsigned int apariciones[UCHAR_MAX + 1] = {0};

    for (unsigned int i = 0; i < dim; i++) {
        apariciones[v[i]]++;
        cont++;
    }

    // SOLO PARA IMPRIMIR, NO ES PARTE DEL ALGORITMO
    for (unsigned int i = 0; i < UCHAR_MAX + 1; i++) {
        if (apariciones[i] > 0) {
            printf("El valor %u aparece %u veces\n", i, apariciones[i]);
        }
    }
}

int main(void) {
    unsigned char arr[] = {0, 1, 200, 3, 1, 3, 200, 1, 1, 1, 2, 4, 5, 200, 3, 1};

    cont = 0;
    muy_ineficiente(arr, sizeof(arr)/sizeof(arr[0]));
    printf("Cantidad de vueltas del ciclo: %d\n", cont);

    cont = 0;
    vector_apariciones(arr, sizeof(arr)/sizeof(arr[0]));
    printf("Cantidad de vueltas del ciclo: %d\n", cont);
    
    return 0;
}
