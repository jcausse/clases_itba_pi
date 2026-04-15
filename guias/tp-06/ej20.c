#include <assert.h>
#include <stdio.h>

#define N 9
#define IS_VALID_ELEM(n) ((n) >= 1 && (n) <= 9)

static bool repeticion_cuadrado(const unsigned char m[N][N], const unsigned char fil_start, const unsigned char col_start) {
    unsigned char apariciones[N] = {0};

    for (unsigned int i = fil_start; i < fil_start + 3U; i++) {
        for (unsigned int j = col_start; j < col_start + 3U; j++) {
            if (apariciones[m[i][j] - 1] == 1) {
                return false;
            }
            apariciones[m[i][j] - 1] = 1;
        }
    }

    return true;
}

bool sudoku(const unsigned char m[N][N]) {
    for (unsigned int i = 0; i < N; i++) {

        unsigned char apariciones_filas[N] = {0};
        unsigned char apariciones_columnas[N] = {0};

        for (unsigned int j = 0; j < N; j++) {
            if (!IS_VALID_ELEM(m[i][j])) {
                return false;
            }

            if (apariciones_filas[m[i][j] - 1] == 1) {
                return false;
            }
            apariciones_filas[m[i][j] - 1] = 1;

            if (apariciones_columnas[m[j][i] - 1] == 1) {
                return false;
            }
            apariciones_columnas[m[j][i] - 1] = 1;

            if ((i % 3 == 0) && (j % 3 == 0) && !repeticion_cuadrado(m, i, j)) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    unsigned char valid[N][N] = {
        {3, 1, 6, 5, 7, 8, 4, 9, 2}, 
        {5, 2, 9, 1, 3, 4, 7, 6, 8}, 
        {4, 8, 7, 6, 2, 9, 5, 3, 1}, 
        {2, 6, 3, 4, 1, 5, 9, 8, 7}, 
        {9, 7, 4, 8, 6, 3, 1, 2, 5}, 
        {8, 5, 1, 7, 9, 2, 6, 4, 3}, 
        {1, 3, 8, 9, 4, 7, 2, 5, 6}, 
        {6, 9, 2, 3, 5, 1, 8, 7, 4}, 
        {7, 4, 5, 2, 8, 6, 3, 1, 9}
    };

    unsigned char row_repeat[N][N] = {
        {3, 3, 6, 5, 7, 8, 4, 9, 2}, 
        {5, 2, 9, 1, 3, 4, 7, 6, 8}, 
        {4, 8, 7, 6, 2, 9, 5, 3, 1}, 
        {2, 6, 3, 4, 1, 5, 9, 8, 7}, 
        {9, 7, 4, 8, 6, 3, 1, 2, 5}, 
        {8, 5, 1, 7, 9, 2, 6, 4, 3}, 
        {1, 3, 8, 9, 4, 7, 2, 5, 6}, 
        {6, 9, 2, 3, 5, 1, 8, 7, 4}, 
        {7, 4, 5, 2, 8, 6, 3, 1, 9}
    };

    unsigned char col_repeat[N][N] = {
        {3, 1, 6, 5, 7, 8, 4, 9, 2}, 
        {3, 2, 9, 1, 3, 4, 7, 6, 8}, 
        {4, 8, 7, 6, 2, 9, 5, 3, 1}, 
        {2, 6, 3, 4, 1, 5, 9, 8, 7}, 
        {9, 7, 4, 8, 6, 3, 1, 2, 5}, 
        {8, 5, 1, 7, 9, 2, 6, 4, 3}, 
        {1, 3, 8, 9, 4, 7, 2, 5, 6}, 
        {6, 9, 2, 3, 5, 1, 8, 7, 4}, 
        {7, 4, 5, 2, 8, 6, 3, 1, 9}
    };

    unsigned char sub_square_repeat[N][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9}, 
        {2, 3, 4, 5, 6, 7, 8, 9, 1}, 
        {3, 4, 5, 6, 7, 8, 9, 1, 2}, 
        {4, 5, 6, 7, 8, 9, 1, 2, 3}, 
        {5, 6, 7, 8, 9, 1, 2, 3, 4}, 
        {6, 7, 8, 9, 1, 2, 3, 4, 5}, 
        {7, 8, 9, 1, 2, 3, 4, 5, 6}, 
        {8, 9, 1, 2, 3, 4, 5, 6, 7}, 
        {9, 1, 2, 3, 4, 5, 6, 7, 8}
    };

    assert(sudoku(valid) == true);
    assert(sudoku(row_repeat) == false);
    assert(sudoku(col_repeat) == false);
    assert(sudoku(sub_square_repeat) == false);

    puts("OK!");
    return 0;
}
