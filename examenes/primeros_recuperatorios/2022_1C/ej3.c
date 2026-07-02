#include <stdio.h>
#include <assert.h>

bool verificarSumas(int * target, int suma_filas, int suma_columnas) {
    // Caso 1: Se esta verificando la suma de la primera fila y primera columna
    //         En este caso, target sera -1.
    //         - Guardamos en target la suma de la fila (o la de columnas, es lo mismo)
    //           (no me importa si no coinciden porque esMagica retorna inmediatamente en caso de que no sea asi)
    //         - Devolvemos si la primera fila sumo lo mismo que la primera columna
    if (*target == -1) {
        *target = suma_filas;
        return suma_filas == suma_columnas;
    }

    // Caso 2: Se esta verificando una fila / columna que no son la primera
    //         Tanto la suma de la fila, como de la columna, como el target deben dar lo mismo
    return *target == suma_filas && *target == suma_columnas;
}

// N debiera ser un #define en lugar de un parametro.
// Esto lo hice asi por los testeos y nada mas.
bool esMagica(const unsigned int N, const int mat[N][N]) {
    unsigned char apariciones[N * N];
    for (unsigned int i = 0; i < N * N; i++) {      // Este for puede eliminarse
        apariciones[i] = 0;                         // al usar un #define, siendo
    }                                               // reemplazado por "= {0}".
    int target = -1;                                // Suma que debe dar cualquier fila y cualquier columna (se setea 1 vez)
    int suma_actual_fila;
    int suma_actual_columna;

    for (unsigned int i = 0; i < N; i++) {

        suma_actual_fila = 0;                       // Inicio las sumas parciales en cero
        suma_actual_columna = 0;

        for (unsigned int j = 0; j < N; j++) {

            // Retorno falso si:
            // 1. El elemento esta por debajo del minimo (1)
            // 2. El elemento esta por encima del maximo (N * N)
            // 3. El elemento esta repetido. Cualquier repeticion que haya genera que ese numero
            //    que esta repetido "le roba el lugar" a otro, por lo que no van a poder estar
            //    todos los elementos del 1 al N * N (inclusive ambos extremos)
            if (mat[i][j] < 1 ||  mat[i][j] > N * N || apariciones[mat[i][j] - 1] > 0) {
                return false;
            }
            apariciones[mat[i][j] - 1] = 1;         // Marco que el elemento ya aparecio

            suma_actual_fila    += mat[i][j];       // Sumo el elemento de la fila
            suma_actual_columna += mat[j][i];       // Y de la columna
        }

        if (! verificarSumas(&target, suma_actual_fila, suma_actual_columna)) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int m1[4][4] = {
        {16,  3,  2,  13}, 
        {5,  10, 11,  8},
        {9,  6,  7,  12},
        {4,  15, 14,  1}
    };
    assert(esMagica(4, m1));

    int m2[4][4] = {
        {16,  4,  5,  10}, 
        {11,  2, 3,  6},
        {12,  9,  13,  15},
        {7,  8, 1,  14}
    };
    assert(! esMagica(4, m2));

    int m3[3][3] = {
        {4, 9, 2},
        {3, 5, 7},
        {8, 1, 6}
    };
    assert(esMagica(3, m3));

    int m4[3][3] = {
        {4, 9, 2},
        {4, 5, 6},
        {7, 1, 7}
    };
    assert(! esMagica(3, m4));

    puts("OK!");
}
