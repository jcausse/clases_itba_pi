#include <stdio.h>
#include <assert.h>

#define EMPTY '0'
#define QUEEN '1'
#define DIRECTION_QTY 8

int checkDirection(
    unsigned int n, char board[n][n],
    unsigned int row_start, unsigned int col_start,
    unsigned int row_delta, unsigned int col_delta
) {
    unsigned int row = row_start + row_delta;
    unsigned int col = col_start + col_delta;
    while (row >= 0 && row < n && col >= 0 && col < n) {
        if (board[row][col] == QUEEN) {
            return 0;
        }
        row += row_delta;
        col += col_delta;
    }
    return 1;
}

int checkPosition(
    unsigned int n, char board[n][n],
    unsigned int row_start, unsigned int col_start
) {
    static int directions [DIRECTION_QTY][2] = {
        { 0,  1},           // Este
        {-1,  0},           // Norte
        { 0, -1},           // Oeste
        { 1,  0},           // Sur
        {-1,  1},           // Nor-Este
        {-1, -1},           // Nor-Oeste
        { 1,  1},           // Sud-Este
        { 1, -1}            // Sud-Oeste
    };
    for (unsigned int i = 0; i < DIRECTION_QTY; i++) {
        if (! checkDirection(n, board, row_start, col_start, directions[i][0], directions[i][1])) {
            return 0;
        }
    }
    return 1;
}

int nQueens(unsigned int n, char board[n][n]) {
    unsigned int queen_count = 0;

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            if (board[i][j] == QUEEN) {
                queen_count++;

                // No se puede tener mas de n reinas
                if (queen_count > n) {
                    return 0;
                }
                
                // Verifico que no haya ninguna otra reina amenazando a la actual
                if (! checkPosition(n, board, i, j)) {
                    return 0;
                }
            }
        }
    }

    // No me puede dar mas que n (sale en el early return)
    // No debe tener menos de n reinas (deben ser exactamente n)
    return queen_count == n;
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
