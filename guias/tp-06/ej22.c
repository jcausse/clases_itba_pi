#include <stdio.h>
#include <assert.h>

void secuenciaAsc(const int v[], int dim, int * comienzo, int * longitud) {
    
    /* Caso particular: array vacio o invalido */
    if (v == NULL || dim == 0) {
        *comienzo = 0;
        *longitud = 0;
        return;
    }

    int inicio_actual = 0;                      // Como el array tiene al menos 1 elemento, ese elemento representa por si solo una
    int largo_actual = 1;                       // secuencia de largo 1 que comienza en el indice 0

    int inicio_max;                             // Posicion de inicio de la secuencia mas larga
    int largo_max = 0;                          // Largo de la secuencia mas larga

    for (int i = 1; i < dim; i++) {             // Comparo desde el primero en adelante

        if (v[i] > v[i - 1]) {                  // Si estoy dentro de la secuencia ascendente, incremento el largo de la misma
            largo_actual++;
        }

        /* Fin de secuencia */
        else {                                  // Cuando dejo de tener una secuencia ascendente
            if (largo_actual > largo_max) {     // Guardo la secuencia actual como maxima, solo si es mas larga que la maxima
                inicio_max = inicio_actual;
                largo_max = largo_actual;
            }
            inicio_actual = i;                  // Reinicio la secuencia con inicio en la posicion actual y largo 1
            largo_actual = 1;
        }
    }

    if (largo_actual > largo_max) {             // Ultima oportunidad para que aquellas secuencias que no se hayan podido pasar
        inicio_max = inicio_actual;             // de las variables "_actual" a las variables "_max" se pasen. Esto configura
        largo_max = largo_actual;               // un "fin de secuencia" para las secuencias de largo 1 en un array de largo 1,
    }                                           // o para los casos donde el array entero es una sola secuencia ascendente

    *comienzo = inicio_max;                     // Dejar los valores "_max" en los parametros de salida
    *longitud = largo_max;
}

int main(void) {
    // Para el vector {1, 1, 3, 4, 4, 7, 10, 9, 11} el comienzo es 1 y su longitud es 3
    int v1[] = {1, 1, 3, 4, 4, 7, 10, 9, 11};
    int dim1 = sizeof(v1) / sizeof(v1[0]);
    int com1, lon1;
    secuenciaAsc(v1, dim1, &com1, &lon1);
    assert(com1 == 1 && lon1 == 3);

    // Para el vector vacío comienzo y longitud son 0 (cero)
    secuenciaAsc(v1, 0, &com1, &lon1);
    assert(com1 == 0 && lon1 == 0);

    // Para los vectores {3}, {2, 2, 2} y  {3, 2, 1, 0, -1}  el comienzo es 0 y la longitud es 1
    int v2[] = {3};
    int com2, lon2;
    secuenciaAsc(v2, 1, &com2, &lon2);
    assert(com2 == 0 && lon2 == 1);
    int v3[] = {2, 2, 2};
    int com3, lon3;
    secuenciaAsc(v3, 3, &com3, &lon3);
    assert(com3 == 0 && lon3 == 1);
    int v4[] = {3, 2, 1, 0, -1};
    int com4, lon4;
    secuenciaAsc(v4, 5, &com4, &lon4);
    assert(com4 == 0 && lon4 == 1);

    // Para el vector {1, 2, 3, 4, 5, 7, 10, 90, 111}  el comienzo es 0 y la longitud 9
    int v5[] = {1, 2, 3, 4, 5, 7, 10, 90, 111};
    int dim5 = sizeof(v5) / sizeof(v5[0]);
    int com5, lon5;
    secuenciaAsc(v5, dim5, &com5, &lon5);
    assert(com5 == 0 && lon5 == 9);
    
    // Para el vector {1, 2, 1, 4, 5, 7, 1, 90, 111}  el comienzo es 2 y la longitud 4
    int v6[] = {1, 2, 1, 4, 5, 7, 1, 90, 111};
    int dim6 = sizeof(v6) / sizeof(v6[0]);
    int com6, lon6;
    secuenciaAsc(v6, dim6, &com6, &lon6);
    assert(com6 == 2 && lon6 == 4);

    puts("OK!");
    return 0;
}
