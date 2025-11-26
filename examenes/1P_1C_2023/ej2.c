#include <stdio.h>
#include <assert.h>

#define N 6
#define SUBMAT_SIZE 3
#define IS_VALID_ELEM(e) ((e) >= 1 && (e) <= (3 * N))

/// @brief      Verifica la condicion pedida en el ejercicio para 1 submatriz de tamaño 3x3
/// @param mat  La matriz
/// @return     -1 en caso de no cumplir alguna condicion, la suma de todos los elementos de la submatriz 
///             si cumple con todo
int verificar_submatriz(const int mat[N][N], const unsigned int fil_start, const unsigned int col_start) {
    unsigned char apariciones[3 * N] = {0};
    int suma = 0;

    for (unsigned int i = fil_start; i < fil_start + SUBMAT_SIZE; i++) {
        for (unsigned int j = col_start; j < col_start + SUBMAT_SIZE; j++) {

            // Chequeo que el numero sea valido (este entre 1 y 3N inclusive)
            if(! IS_VALID_ELEM(mat[i][j])) {
                return -1;
            }

            // Chequeo que no este repetido
            if (apariciones[mat[i][j] - 1] == 1) {
                return -1;
            }
            apariciones[mat[i][j] - 1] = 1;             // Me anoto la aparicion

            suma += mat[i][j];                          // Acumulo la suma de los elementos
        }
    }

    return suma;
}

int verifica(const int mat[N][N]) {
    const unsigned int N_MATRIZ_SUBMATS = N / SUBMAT_SIZE;
    int suma = -1;
    int aux;

    for (unsigned int i = 0; i < N_MATRIZ_SUBMATS; i++) {
        for (unsigned int j = 0; j < N_MATRIZ_SUBMATS; j++) {
            if ((aux = verificar_submatriz(mat, i * 3, j * 3)) == -1) { // Si la funcion devuelve -1, hubo un error
                return 0;                                               // retorno 0
            }

            // Si no hubo error, en aux tengo la suma de los elementos de la submatriz actual
            if (suma != -1 && aux != suma) {    // Si alguna submatriz no suma lo mismo que las anteriores,
                return 0;                       // retorno un error. suma != -1 es para ver que ya se haya calculado
            }                                   // la suma de alguna submatriz con anterioridad
            else if (suma == -1) {              // Solo la primera vez, seteo la suma
                suma = aux;
            }
        }
    }
    return 1;
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
