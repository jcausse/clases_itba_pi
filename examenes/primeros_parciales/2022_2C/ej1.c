/**
 * IDEA: Debido a que:
 * - cada fila debe tener numeros consecutivos no necesariamente ordenados
 * - los numeros de cada fila deben ser menores que los numeros de las filas siguientes
 * - cada numero debe aparecer una sola vez en la matriz
 * 
 * Podemos ver, para N = 4, por ejemplo, que los elementos de cada fila, deben ser, y no
 * necesariamente en ese orden, los siguientes:
 * - Fila 0:  1,  2,  3,  4
 * - Fila 1:  5,  6,  7,  8
 * - Fila 2:  9, 10, 11, 12
 * - Fila 3: 13, 14, 15, 16
 * 
 * Si vinculamos el numero de fila con el rango de numeros que aparecen, vemos que:
 * - Fila 0:  del   1 + 0 * N       al  (0 + 1) * N
 * - Fila 1:  del   1 + 1 * N       al  (1 + 1) * N
 * - Fila 2:  del   1 + 2 * N       al  (2 + 1) * N
 * - Fila 3:  del   1 + 3 * N       al  (3 + 1) * N
 * 
 * Podemos generalizar entre que numero y que numero deben estar los elementos de la fila i:
 * - Desde:         i * N + 1
 * - Hasta:         (i + 1) * N
 */

/********************************************************************************************/

#include <stdio.h>
#include <assert.h>

#define N 4
#define OK      1
#define NOT_OK  0

/**
 * @brief       Verifica una fila de la matriz
 * 
 * @details     Todos los elementos de la fila deben aparecer una sola vez
 *              y estar en el rango:
 *              - Desde: row_number * N + 1
 *              - Hasta: (row_number + 1) * N
 *              incluyendo ambos extremos
 * 
 * @param row           Una fila de la matriz
 * @param row_number    Que numero de fila de la matriz es
 * 
 * @return      Si la fila es valida o no
 */
bool check_row(int row[N], unsigned int row_number) {
    const int MIN = row_number * N + 1;         // Minimo del rango
    const int MAX = (row_number + 1) * N;       // Maximo del rango
    unsigned char appearances[N] = {0};         // Vector de apariciones

    for (unsigned int j = 0; j < N; j++){       // Para cada elemento en la fila
        if (row[j] < MIN || row[j] > MAX) {     // Chequeo que este en el rango adecuado
            return false;
        }
        if (appearances[row[j] - MIN]) {        // Chequeo que no se repita (ver NOTA abajo)
            return false;
        }
        appearances[row[j] - MIN] = 1;          // Marco la aparicion
    }
    
    return true;
}

/**
 * NOTA: La idea importante de por que se resta MIN a row[j] es la siguiente:
 * El vector de apariciones es de tamaño N. 
 * - MIN = row_number * N + 1
 * - MAX = (row_number + 1) * N
 * 
 * Pasado el chequeo del primer if, sabemos que el numero row[j] esta entre MIN y MAX (inclusive).
 * Entonces:
 *         MIN <= row[j] <= MAX
 *         MIN - MIN <= row[j] - MIN <= MAX - MIN
 *         0 <= row[j] - MIN <= (row_number + 1) * N - row_number * N - 1
 *         0 <= row[j] - MIN <= row_number * N + N - row_number * N - 1
 *         0 <= row[j] - MIN <= N - 1
 * 
 * Por lo tanto, row[j] - MIN es un indice valido del vector de apariciones para cualquier row_number.
 * Estoy mapeando los numeros row[j] que estan entre MIN y MAX siempre a un mismo intervalo
 * entre 0 y N - 1 para poder usar row[j] - MIN como indice del vector de apariciones
 */

int condition(int mat[N][N]) {
    for (unsigned int i = 0; i < N; i++){       // Para cada fila
        if (!check_row(mat[i], i)) {            // Verifico la fila, y si es invalida
            return NOT_OK;                      // devuelvo 0
        }
    }

    return OK;                                  // Devuelvo 1 si todo salio bien
}

int main(void) {
    int m1[N][N] = {
        { 3,   4,   1,   2}, 
        { 8,   7,   6,   5}, 
        { 9,  10,  11,  12}, 
        {15,  16,  13,  14}
    };
    assert(condition(m1) == 1);

    int m2[N][N] = {
        { 3,   1,   1,   2,}, 
        { 8,   7,   6,   5,}, 
        { 9,  10,  11,  12,}, 
        {15,  16,  13,  14,}
    };
    assert(condition(m2) == 0);

    int m3[N][N] = {
        { 3,   1,   4,   2}, 
        { 8,   7,   6,   5}, 
        { 9,  10,  11,  12}, 
        {15,  16,  13,  11}
    };
    assert(condition(m3) == 0);

    puts("OK!");
    return 0;
}
