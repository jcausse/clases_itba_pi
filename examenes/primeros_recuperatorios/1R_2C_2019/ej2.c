#include <stdio.h>
#include <assert.h>

#define M 4
#define N 4

#define ES_VALIDO(n) (0 <= (n) && (n) <= 9)

bool calcularFila(const unsigned int fila[M], unsigned int * const result) {
    unsigned int potencia = 1;
    unsigned int ret = 0; 

    for (int i = M - 1; i >= 0; i--) {
        if (! ES_VALIDO(fila[i])) {
            return false;
        }
        ret += fila[i] * potencia;
        potencia *= 10;
    }
    *result = ret;
    return true;
}

unsigned int armaFilas(const unsigned int mat[N][M], unsigned int vec[N]) {
    unsigned int result, write = 0;

    for (int i = 0; i < N; i++) {
        if (calcularFila(mat[i], &result)) {
            vec[write] = result;
            write++;
        }
    }

    return write;
}

// TEST:

bool check_row(unsigned int dim, const unsigned int v1[dim], const unsigned int v2[dim]) {
    for (unsigned int i = 0; i < dim; i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    unsigned int vec[N];

    unsigned int m1[N][M] = {
        {16, 3 , 2 , 13}, 
        {5 , 10, 11, 8 },
        {9 , 6 , 7 , 12}, 
        {4 , 15, 14, 1 }
    };
    unsigned int res1[N] = {0};
    assert(armaFilas(m1, vec) == 0);
    assert(check_row(4, res1, vec));

    unsigned int m2[N][M] = {   
        {1, 3, 2, 5}, 
        {5, 0, 1, 8}, 
        {9, 6, 7, 2}, 
        {4, 5, 4, 1}
    };
    unsigned int res2[N] = {1325, 5018, 9672, 4541};
    assert(armaFilas(m2, vec) == 4);
    assert(check_row(4, res2, vec));

    unsigned int m3[N][M] = {
        {1, 3 , 2, 5}, 
        {5, 10, 1, 8}, 
        {9, 6 , 7, 2}, 
        {4, 5 , 4, 1}
    };
    unsigned int res3[N] = {1325, 9672, 4541};
    assert(armaFilas(m3, vec) == 3);
    assert(check_row(3, res3, vec));

    puts("OK!");
    return 0;
}
