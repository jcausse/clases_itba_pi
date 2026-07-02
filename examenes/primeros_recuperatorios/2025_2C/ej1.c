#include <stdio.h>

// IDEA: Tambien se puede rotar "por anillos", que es mucho mas eficiente que generar la copia, porque:
// 1. Recorre la matriz 1 sola vez en lugar de 2
// 2. Usa una variable como memoria auxiliar (1 solo int) en lugar de toda una matriz completa.
// Ejemplo para rotar el primer anillo (el mas externo):

/*
    unsigned int cant_anillos = dim / 2;

    for (unsigned int i = 0; i < dim - 1; i++) {
        int aux                     =   mat[0][i];
        mat[0][i]                   =   mat[dim - 1 - i][0];
        mat[dim - 1 - i][0]         =   mat[dim - 1][dim - 1 - i];
        mat[dim - 1][dim - 1 - i]   =   mat[i][dim - 1];
        mat[i][dim - 1]             =   aux;
    }
*/

//-----------------------------------------------------------------------------------------------

void copyMatrix(unsigned int dim, int target[dim][dim], int source[dim][dim]) {
    for (unsigned int i = 0; i < dim; i++) {
        for (unsigned int j = 0; j < dim; j++) {
            target[i][j] = source[i][j];
        }
    }
}

// rotations in {1, 2, 3}
unsigned int rowIndex(unsigned int dim, unsigned int original_row, unsigned int original_col, unsigned int rotations) {
    unsigned int ret;
    if (rotations == 1) {           // 90 grados
        ret = original_col;
    }
    else if (rotations == 2) {      // 180 grados
        ret = dim - 1 - original_row;
    }
    else {                          // 270 grados
        ret = dim - 1 - original_col;
    }
    return ret;
}

// rotations in {1, 2, 3}
unsigned int colIndex(unsigned int dim, unsigned int original_row, unsigned int original_col, unsigned int rotations) {
    unsigned int ret;
    if (rotations == 1) {           // 90 grados
        ret = dim - 1 - original_row;
    }
    else if (rotations == 2) {      // 180 grados
        ret = dim - 1 - original_col;
    }
    else {                          // 270 grados
        ret = original_row;
    }
    return ret;
}

void rotaN(unsigned int dim, int mat[dim][dim], unsigned int veces) {
    // Por cada 4 rotaciones, la matriz queda igual que la original
    // Solo tiene sentido realizar las rotaciones "excedentes"
    veces %= 4;

    // Caso 1: No hay que rotar
    if (veces == 0) {
        return;
    }

    // Copia de la matriz para poder rotar los elementos
    int copy[dim][dim];
    copyMatrix(dim, copy, mat);

    for (unsigned int i = 0; i < dim; i++) {
        for (unsigned int j = 0; j < dim; j++) {
            unsigned int new_row = rowIndex(dim, i, j, veces);
            unsigned int new_col = colIndex(dim, i, j, veces);
            mat[new_row][new_col] = copy[i][j];
        }
    }
}

void printMatrix(unsigned int f, unsigned int c, int mat[f][c]) {
    for (unsigned int i = 0; i < f; i++) {
        for (unsigned int j = 0; j < c; j++) {
            printf("%3d ", mat[i][j]);
        }
        puts("");
    }
}

#define DIM 4

int main(void) {
    int mat1[DIM][DIM] = {
        {1 ,    2,    3,    4}, 
        {5 ,    6,    7,    8}, 
        {9 ,   10,   11,   12}, 
        {13,   14,   15,   16}
    };

    int mat2[DIM][DIM] = {
        {1 ,    2,    3,    4}, 
        {5 ,    6,    7,    8}, 
        {9 ,   10,   11,   12}, 
        {13,   14,   15,   16}
    };

    int mat3[DIM][DIM] = {
        {1 ,    2,    3,    4}, 
        {5 ,    6,    7,    8}, 
        {9 ,   10,   11,   12}, 
        {13,   14,   15,   16}
    };

    printf("Original:\n");
    printMatrix(DIM, DIM, mat1);
    puts("");

    rotaN(DIM, mat1, 1);
    rotaN(DIM, mat2, 2);
    rotaN(DIM, mat3, 3);

    printf("1 rotacion:\n");
    printMatrix(DIM, DIM, mat1);
    puts("");

    printf("2 rotaciones:\n");
    printMatrix(DIM, DIM, mat2);
    puts("");

    printf("3 rotaciones:\n");
    printMatrix(DIM, DIM, mat3);
    puts("");

    return 0;
}

// Con rotaciones = 1
/*
 13   9   5   1 
 14  10   6   2 
 15  11   7   3 
 16  12   8   4
*/

// Con rotaciones = 2
/*
16  15    14   13 
12  11    10    9 
8    7     6    5 
4    3     2    1
*/

// Con rotaciones = 3
/*
4    8   12  16 
3    7   11  15 
2    6   10  14 
1    5    9  13
*/
