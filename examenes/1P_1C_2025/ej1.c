#include <stdio.h>
#include <assert.h>

#define COLS 4

/**
 * @brief   Devuelve si v contiene a elem
 */
bool contiene(unsigned int dim, int v[dim], int elem) {
    for (unsigned int i = 0; i < dim; i++) {
        if (v[i] == elem) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Devuelve si todos los elementos de v1 estan en v2
 */
bool vectorContenido(unsigned int dim, int v1[dim], int v2[dim]) {
    for (unsigned int i = 0; i < dim; i++) {
        if (!contiene(dim, v2, v1[i])) {
            return false;
        }
    }
    return true;
}

bool vectoresEspejo(unsigned int dim, int v1[dim], int v2[dim]) {
    return vectorContenido(dim, v1, v2) && vectorContenido(dim, v2, v1);
}

int matricesEspejo(unsigned int fils, unsigned int cols, int m1[fils][cols], int m2[fils][cols]) {
    for (unsigned int i = 0; i < fils; i++) {
        if (!vectoresEspejo(cols, m1[i], m2[i])) {
            return 0;
        }
    }
    return 1;
}
 
int main(void) { 
    int m1[][COLS] = { 
        {5, 3, 4, 3},      // elementos 3, 4 y 5 
        {1, 2, 1, 1},      // elementos 1 y 2  
        {6, 7, 8, 9}       // elementos 6, 7, 8 y 9 
    }; 
    int m2[][COLS] = { 
        {3, 4, 3, 5},      // elementos 3, 4 y 5 
        {1, 1, 2, 1},      // elementos 1 y 2  
        {9, 8, 7, 6}       // elementos 6, 7, 8 y 9 
    }; 
    assert(matricesEspejo(3, 4, m1, m2) == 1); 
 
    int m3[][3] = { 
        {5, 3, 3},        // elementos 3 y 5     (*) 
        {5, 4, 3},        // elementos 3, 4 y 5 
        {6, 7, 9}         // elementos 6, 7 y 9 
    }; 
    int m4[][3] = { 
        {3, 5, 4},        // elementos 3, 4 y 5  (*) 
        {4, 3, 5},        // elementos 3, 4 y 5 
        {6, 9, 7}         // elementos 6, 7 y 9 
    }; 
    assert(! matricesEspejo(3, 3, m3, m4)); 
    puts("OK!"); 
    return 0; 
}
