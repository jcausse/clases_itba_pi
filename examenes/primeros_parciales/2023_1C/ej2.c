#include <stdio.h>
#include <assert.h>

#define N 6
#define SUBMAT_SIZE 3
#define IS_VALID_ELEM(e) ((e) >= 1 && (e) <= (3 * N))

#define INVALID_SUBMAT -1

/**
 * @brief   Verifica que se cumplan las condiciones pedidas para una sub-matriz (de 3x3).
 * @details Verifica:
 *          - Que todos los elementos esten entre 1 y 3*N (segun definido en IS_VALID_ELEM).
 *          - Que no haya elementos repetidos.
 * @param   mat         La matriz original.
 * @param   fil_start   El indice sobre las filas donde inicia la submatriz.
 * @param   col_start   El indice sobre las columnas donde inicia la submatriz.
 * @return  Retorna:
 *          - La suma de todos los elementos si la submatriz es valida.
 *          - INVALID_SUBMAT si la submatriz no es valida.
 */
static int verificar_submatriz(const int mat[N][N], const unsigned int fil_start, const unsigned int col_start) {
    unsigned int apariciones[3 * N] = {0};

    int suma = 0;

    for (unsigned int i = fil_start; i < fil_start + SUBMAT_SIZE; i++) {
        for (unsigned int j = col_start; j < col_start + SUBMAT_SIZE; j++) {

            // 1. Verifico que el numero sea valido y no este repetido
            if (!IS_VALID_ELEM(mat[i][j]) || apariciones[mat[i][j] - 1] > 0) {
                return INVALID_SUBMAT;
            }
            
            // 2. Si es valido y no tiene apariciones previas, sumo una aparicion
            apariciones[mat[i][j] - 1]++;
            
            // 3. Sumo todos los elementos
            suma += mat[i][j];
        }
    }

    return suma;
}

#define OK 1
#define ERROR 0

int verifica(const int mat[N][N]) {
    int suma_submatriz = 0, aux;

    for (unsigned int i = 0; i < N; i += SUBMAT_SIZE) {
        for (unsigned int j = 0; j < N; j += SUBMAT_SIZE) {
            aux = verificar_submatriz(mat, i, j);

            if (aux == INVALID_SUBMAT || (suma_submatriz > 0 && suma_submatriz != aux)) {
                return ERROR;
            }
            
            suma_submatriz = aux;
        }
    }

    return OK;
}

int main(void) {
#if N == 3          // SOLO PARA N = 3 (CAMBIAR EL DEFINE DE ARRIBA Y VOLVER A COMPILAR Y CORRER)
    int m1[3][3] = {
        {1, 3, 2},
        {9, 8, 6},
        {4, 7, 5}
    };
    assert(verifica(m1) == 1);

    int m2[3][3] = {
        {1, 3, 2},
        {9, 8, 6},
        {4, 7, 15}
    };
    assert(verifica(m2) == 0);

#elif N == 6        // SOLO PARA N = 6 (CAMBIAR EL DEFINE DE ARRIBA Y VOLVER A COMPILAR Y CORRER)
    int m3[6][6] = {
        {10,  3 ,  2,   3 ,  8 ,  7},
        {12,  8 ,  6,   6 ,  2 ,  4},
        {4 ,  7 ,  5,   5 ,  12,  10},
        {2 ,  12,  6,   10,  4 ,  5},
        {5 ,  10,  3,   7 ,  2 ,  9},
        {8 ,  4 ,  7,   3 ,  6 ,  11}
    };
    assert(verifica(m3) == 1);

    int m4[6][6] = {
        {1, 3, 2, 3, 8, 5},
        {9, 8, 6, 6, 2, 4},
        {4, 7, 5, 5, 9, 3},
        {2, 9, 6, 1, 4, 5},
        {5, 1, 3, 7, 2, 8},
        {8, 4, 7, 3, 6, 9}
    };
    assert(verifica(m4) == 0);

#else
    printf("No hay testeos para N = %d\n", N);

#endif

    puts("OK!");
}
