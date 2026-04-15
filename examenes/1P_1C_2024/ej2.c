#include <stdio.h>
#include <assert.h>

#define QUEEN '1'
#define DIRECTION_COUNT 4

bool checkDirection(int dim, const char board[dim][dim], int start_i, int start_j, int delta_i, int delta_j) {    
    int current_i = start_i + delta_i;
    int current_j = start_j + delta_j;

    while (0 <= current_i && current_i < dim && 0 <= current_j && current_j < dim) {
        if (board[current_i][current_j] == QUEEN) {
            return false;
        }
        current_i += delta_i;
        current_j += delta_j;
    }

    return true;
}

/**
 * @brief   Verifica que una posicion del tablero de nQueens sea valido.
 * @details Una posicion es valida cuando:
 *          - Hay una reina, pero no amenaza a ninguna otra reina para las direcciones consideradas.
 *          - No hay reina.
 */
bool checkPosition(unsigned int dim, const char board[dim][dim], unsigned int i, unsigned int j) {
    static int DIRECTIONS[DIRECTION_COUNT][2] = {{0, 1}, {1, 1}, {1, 0}, {-1, 1}};

    for (unsigned int dir = 0; dir < DIRECTION_COUNT; dir++) {
        if (!checkDirection(dim, board, i, j, DIRECTIONS[dir][0], DIRECTIONS[dir][1])) {
            return false;
        }
    }
    return true;
}

int nQueens(unsigned int dim, const char board[dim][dim]) {
    unsigned int queen_count = 0;
    for (unsigned int i = 0; i < dim; i++) {
        for (unsigned int j = 0; j < dim; j++) {
            if (board[i][j] == QUEEN) {
                queen_count++;
                if (!checkPosition(dim, board, i, j)) {
                    return 0;
                }
            }
        }
    }
    return queen_count == dim;
}

int main(void) {
    char board[][8] = {
        {'0', '0', '0', '0', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '1', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '1', '0'},
        {'1', '0', '0', '0', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '1'},
    };
    // por ejemplo, hay tres reinas en la columna 4 y dos en la fila 6
    assert(nQueens(8, board) == 0);
    
    char board2[][6] = {
        {'0', '0', '0', '1', '0', '0'},
        {'1', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0'},
        {'0', '1', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '1'},
        {'0', '0', '1', '0', '0', '0'}
    };
    // Hay 6 reinas y no se atacan, retorna true
    assert(nQueens(6, board2));
    
    char board3[][6] = {
        {'0', '0', '1', '0', '0', '0'},
        {'1', '0', '0', '0', '0', '0'},
        {'0', '1', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0'},
        {'0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '1'}
    };
    // Las reinas en (1,0) y (2,1) se amenazan en forma diagonal
    assert(nQueens(6, board3) == 0);
    
    char board4[][6] = {
        {'0', '0', '0', '1', '0', '0'},
        {'0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0'},
        {'0', '1', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '1'},
        {'0', '0', '1', '0', '0', '0'}
    };
    // No se amenazan pero hay menos de 6 reinas
    assert(nQueens(6, board4) == 0);
    
    // No hay solución para tableros de dimensión 2 o 3
    assert(nQueens(3, board2) == 0);
    assert(nQueens(2, board2) == 0);
    
    // En un tablero de 1x1 debe haber una reina
    char board1[][1] = {{'1'}};
    assert(nQueens(1, board1));
    
    puts("OK!");
    
    return 0;
}
