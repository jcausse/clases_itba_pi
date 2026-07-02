#include <stdio.h>
#include <assert.h>

#define COLS 6

/// @brief Devuelve si un vector es palindromo o no
/// @param v        Vector
/// @return         Valor booleano indicando el resultado
bool vectorPalindromo(char v[COLS]) {
    for (unsigned int i = 0; i < COLS / 2; i++) {
        if (v[i] != v[COLS - i - 1]) {
            return false;
        }
    }
    return true;
}

/// @brief Copia la fila de indice src de la matriz al indice dst
/// @param fils     Cantidad total de filas de la matriz
/// @param mat      La matriz
/// @param src      Origen
/// @param dst      Destino
void copiarFila(const unsigned int fils, char mat[fils][COLS], unsigned int src, unsigned int dst) {
    if (src >= fils || dst >= fils || src == dst) {     // src == dst impide que una fila se copie sobre si misma
        return;                                         // es mucho mas eficiente
    }

    for (unsigned int i = 0; i < COLS; i++) {
        mat[dst][i] = mat[src][i];
    }
}

unsigned int elimina(const unsigned int fils, char mat[fils][COLS]) {
    unsigned int read, write = 0;

    for (read = 0; read < fils; read++) {
        if (! vectorPalindromo(mat[read])) {
            copiarFila(fils, mat, read, write);
            write++;
        }
    }
    
    return write; // Como write siempre es el indice de la proxima fila a escribir, coincide con la cantidad de filas copiadas
}

//-------------------------------------------------------------
// TESTEO

bool checkMat(unsigned int fils, char mat[fils][COLS], char res[fils][COLS]) {
    for (unsigned int i = 0; i < fils; i++) {
        for (unsigned int j = 0; j < COLS; j++) {
            if (mat[i][j] != res[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    char mat[6][COLS] = {
        {'L', '#', 'B', 'B', '#', 'L'},
        {'3', '1', 'r', 'R', '1', '3'},
        {'3', '2', 'S', 'S', '2', '3'},
        {'R', 'L', 'A', 'H', 'N', 'N'},
        {'W', 'A', 'O', 'Y', 'U', 'T'},
        {'Q', 'S', 'G', 'S', 'M', 'A'}
    };

    char res[4][COLS] = {
        {'3', '1', 'r', 'R', '1', '3'},
        {'R', 'L', 'A', 'H', 'N', 'N'},
        {'W', 'A', 'O', 'Y', 'U', 'T'},
        {'Q', 'S', 'G', 'S', 'M', 'A'}
    };

    assert(elimina(6, mat) == 4);
    assert(checkMat(4, mat, res));

    puts("OK!");
}
