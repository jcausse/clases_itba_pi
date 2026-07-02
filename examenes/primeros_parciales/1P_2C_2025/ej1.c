#include <stdio.h>
#include <assert.h>

/// @brief Devuelve si el elemento e pertenece (esta al menos una vez) a v
/// @param dim  Dimension del arreglo v
/// @param v    Arreglo donde buscar
/// @param e    Elemento a buscar
/// @return     true si pertenece, false en caso contrario
bool vectorContiene(const size_t dim, const int v[dim], const int e) {
    for (size_t i = 0; i < dim; i++) {
        if (v[i] == e) {
            return true;
        }
    }
    return false;
}

bool vectorFormado(
    const size_t dimC, const int vecC[dimC], 
    const size_t dimA, const int vecA[dimA], 
    const size_t dimB, const int vecB[dimB]
) {
    for (size_t i = 0; i < dimC; i++) {
        if (! (vectorContiene(dimA, vecA, vecC[i]) || vectorContiene(dimB, vecB, vecC[i])) ) {
            return false;
        }
    }
    return true;
}

int formada(const size_t fils, 
    const size_t colsC, const int matC[fils][colsC], 
    const size_t colsA, const int matA[fils][colsA], 
    const size_t colsB, const int matB[fils][colsB]
) {
    for (size_t i = 0; i < fils; i++) {
        if (! vectorFormado(colsC, matC[i], colsA, matA[i], colsB, matB[i])) {
            return 0;
        }
    }
    return 1;
}

int main() { 
    int M1[3][2] = { {1, 5}, {7, 8}, {0, 2} }; 
    int M2[3][3] = { {1, 3, 5}, {7, 0, 8}, {2, 4, 6} }; 
    int M3[3][1] = { {0}, {8}, {0} }; 
 
    // Se obtiene 1 pues cada fila f de M1 se forma a partir 
    // de la fila f de M2 y la fila f de M3 
    // Los parámetros de formada son: 
    // filas, columnas M1, M1, columnas M2, M2, columnas M3, M3 
    assert(formada(3, 2, M1, 3, M2, 1, M3) == 1); 
 
    int M4[3][2] = { {1, 9}, {7, 8}, {0, 2} }; 
    // Se obtiene 0 pues la fila 1 de M4 no se forma a partir 
    // de la fila 1 de M2 y la fila 1 de M3 
    // dado que el 9 de la fila 1 de M4 no está 
    // en la fila 1 de M2 ni en la fila 1 de M3 
    assert(formada(3, 2, M4, 3, M2, 1, M3) == 0); 
 
    int M5[3][3] = { {1, 5, 1}, {7, 9, 8}, {0, 2, 2} }; 
    int M6[3][2] = { {1, 9},    {7, 9},    {0, 2} }; 
    int M7[3][1] = { {5},       {8},       {9} }; 
    assert(formada(3, 3, M5, 2, M6, 1, M7) == 1); 
    
    puts("OK");

    return 0; 
}
