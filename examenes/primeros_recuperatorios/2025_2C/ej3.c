#include <stdio.h>
#include <assert.h>

void secuenciaAsc(
    unsigned int dim, int vec[dim], unsigned int * const comienzo, unsigned int * const longitud
) {
    *comienzo = 0;
    *longitud = 0;
    
    if (dim == 0) {
        return;
    }

    unsigned int comAux = 0, longAux = 1;

    for (unsigned int i = 1; i < dim; i++) {
        if (vec[i] > vec[i - 1]) {
            longAux++;
        }
        else {
            if (longAux > *longitud) {
                *comienzo = comAux;
                *longitud = longAux;
            }

            comAux = i;
            longAux = 1;
        }
    }

    if (longAux > *longitud) {
        *comienzo = comAux;
        *longitud = longAux;
    }
}

int main(void) {
    unsigned int comienzo;
    unsigned int longitud;

    int v1[] = {1, 1, 3, 4, 4, 7, 10, 9, 11};
    unsigned int dim1 = sizeof(v1) / sizeof(v1[0]);
    secuenciaAsc(dim1, v1, &comienzo, &longitud);
    assert(comienzo == 1);
    assert(longitud == 3);

    secuenciaAsc(0, NULL, &comienzo, &longitud);
    assert(comienzo == 0);
    assert(longitud == 0);

    
    int v2[] = {3};
    unsigned int dim2 = sizeof(v2) / sizeof(v2[0]);
    secuenciaAsc(dim2, v2, &comienzo, &longitud);
    assert(comienzo == 0);
    assert(longitud == 1);
    
    int v3[] = {2, 2, 2};
    unsigned int dim3 = sizeof(v3) / sizeof(v3[0]);
    secuenciaAsc(dim3, v3, &comienzo, &longitud);
    assert(comienzo == 0);
    assert(longitud == 1);
    
    int v4[] = {3, 2, 1, 0, -1};
    unsigned int dim4 = sizeof(v4) / sizeof(v4[0]);
    secuenciaAsc(dim4, v4, &comienzo, &longitud);
    assert(comienzo == 0);
    assert(longitud == 1);

    int v5[] = {1, 2, 3, 4, 5, 7, 10, 90, 111};
    unsigned int dim5 = sizeof(v5) / sizeof(v5[0]);
    secuenciaAsc(dim5, v5, &comienzo, &longitud);
    assert(comienzo == 0);
    assert(longitud == 9);

    int v6[] = {1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2};
    unsigned int dim6 = sizeof(v6) / sizeof(v6[0]);
    secuenciaAsc(dim6, v6, &comienzo, &longitud);
    assert(comienzo == 7);
    assert(longitud == 6);

    puts("OK!");
    return 0;
}
