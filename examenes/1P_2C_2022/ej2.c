#include <stdio.h>
#include <assert.h>

#define CANT_DIRS 8

#define N 6
#define VALID_INDEX(x) (0 <= (x) && (x) < N)

/**
 * @brief   Verifica si el string esta en una direccion determinada a partir de un elemento determinado de la matriz.
 * @details No se verifica la posicion dada como inicial, solo a partir de la segunda posicion para los dados delta_i y delta_j.
 */
static bool checkDirection(const char mat[N][N], const char * string, int start_i, int start_j, int delta_i, int delta_j) {
    int k = 1;
    int current_i = start_i + delta_i;
    int current_j = start_j + delta_j;

    while (string[k] != '\0' && VALID_INDEX(current_i) && VALID_INDEX(current_j)) {
        if (mat[current_i][current_j] != string[k]) {
            return false;
        }
        k++;
        current_i += delta_i;
        current_j += delta_j;
    }
    return string[k] == '\0';
}

int palEnMat(const char mat[N][N], int fil, int col, const char * string) {
    // Caso string vacio
    if (string[0] == '\0') {
        return 1;
    }

    // Caso fila o columna fuera de rango o primera letra no coincide
    if (!VALID_INDEX(fil) || !VALID_INDEX(col) || mat[fil][col] != string[0]) {
        return 0;
    }

    // Caso general
    int DIRECCIONES[CANT_DIRS][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    for (unsigned int i = 0; i < CANT_DIRS; i++) {
        if (checkDirection(mat, string, fil, col, DIRECCIONES[i][0], DIRECCIONES[i][1])) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    char mat[N][N] = {
        {'L', 'O', 'B', 'R', 'A', 'Z'}, 
        {'F', 'H', 'R', 'G', 'O', 'R'}, 
        {'C', 'O', 'S', 'A', 'D', 'A'}, 
        {'R', 'L', 'A', 'H', 'N', 'N'}, 
        {'W', 'A', 'O', 'Y', 'U', 'T'}, 
        {'Q', 'S', 'G', 'S', 'M', 'A'}
    };

    assert(palEnMat(mat, 5, 1, "SAL") == 1);    
    assert(palEnMat(mat, 2, 0, "COSA") == 1);    
    assert(palEnMat(mat, 2, 0, "CHB") == 1);
    assert(palEnMat(mat, 2, 0, "CLOS") == 1);
    assert(palEnMat(mat, 2, 0, "") == 1);
    assert(palEnMat(mat, 2, 0, "C") == 1);

    assert(palEnMat(mat, 5, 1, "sal") == 0);
    assert(palEnMat(mat, 5, 1, "SALA") == 0);
    assert(palEnMat(mat, 2, 0, "COSADAS") == 0);
    assert(palEnMat(mat, 6, 1, "HOLA") == 0);

    puts("OK!");
}
