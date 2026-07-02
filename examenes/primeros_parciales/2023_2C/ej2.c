#include <stdio.h>
#include <assert.h>

#define M 6

int sumaBorde(int mat[M][M], unsigned int borde) {
    int suma = 0;
    for (unsigned int i = borde + 1; i <= M - borde - 2; i++) {
        suma += mat[borde][i] + mat[M - borde - 1][i];
        suma += mat[i][borde] + mat[i][M - borde - 1];
    }
    suma += mat[borde][borde];                      // Esquina superior izquierda
    suma += mat[borde][M - borde - 1];              // Esquina superior derecha
    suma += mat[M - borde - 1][borde];              // Esquina inferior izquierda
    suma += mat[M - borde - 1][M - borde - 1];      // Esquina inferior derecha
    return suma;
}

void bordes(int mat[M][M], int sumas[]) {
    for (unsigned int i = 0; i < M / 2; i++){
        sumas[i] = sumaBorde(mat, i);
    }
}

int main(void) {
    printf("TEST PARA M = %d\n", M);

#if M == 4
    int mat1[M][M] = {
        {-2,    2,   -2,    2},
        { 4,    1,    2,   -4},
        { 0,    1,    2,    0},
        {-2,   -2,    2,    2}
    };
    int sumas1[M / 2] = {0};
    bordes(mat1, sumas1);
    assert(sumas1[0] == 0);
    assert(sumas1[1] == 6);

#elif M == 2
    int mat2[M][M] = {
        {1, 2},
        {3, 3}
    };
    int sumas2[M / 2] = {0};
    bordes(mat2, sumas2);
    assert(sumas2[0] == 9);

#elif M == 6
    int mat3[M][M] = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 3, 3, 2, 1},
        {1, 2, 3, 3, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1}
    };
    int sumas3[M / 2] = {0};
    bordes(mat3, sumas3);
    assert(sumas3[0] == 20);
    assert(sumas3[1] == 24);
    assert(sumas3[2] == 12);

#else
    printf("No hay test para M = %d\n", M);

#endif
    puts("OK!");
}
