#include <stdio.h>
#include <assert.h>

int sumaFila(unsigned int dim, int fil[dim]) {
    int suma = 0;
    for (unsigned int i = 0; i < dim; i++) {
        suma += fil[i];
    }
    return suma;
}

#define NOT_FOUND -1;

/**
 * @brief   Indica en que posicion del vector de sumas se encuentra una suma determinada, o -1 si no esta
 */
int indiceSuma(unsigned int sumasDistintas, int sumas[][2], int target) {
    for (unsigned int i = 0; i < sumasDistintas; i++) {
        if (sumas[i][0] == target) {
            return (int) i;
        }
    }
    return NOT_FOUND;
}

int escalar(unsigned int dim, int m[dim][dim]) {
    int sumaFilaActual, indiceSumaActual;

    int sumas[dim][2];              // Primer elemento: Todas las sumas distintas que hubo en las filas
                                    // Segunto elemento: En cuantas filas aparecio la suma del primer elemento
    unsigned int sumasDistintas = 0;            // La cantidad de sumas diferentes que hubo

    for (unsigned int i = 0; i < dim; i++) {
        sumaFilaActual = sumaFila(dim, m[i]);

        // Primero que nada, verifico que la suma sea valida (dim <= sumaFilaActual <= 2 * dim)
        if (sumaFilaActual < dim || sumaFilaActual > 2 * dim) {
            return 0;
        }

        indiceSumaActual = indiceSuma(sumasDistintas, sumas, sumaFilaActual);

        // Si ninguna fila sumo lo mismo que la actual hasta ahora, la agrego al vector de filas
        if (indiceSumaActual == -1) {
            sumas[sumasDistintas][0] = sumaFilaActual;
            sumas[sumasDistintas][1] = 1;
            sumasDistintas++;
        }

        // Si alguna fila anteriormente ya tenia dicha suma, pero no mas de 2 de ellas, le agrego una fila
        // que sumo ese valor
        else if (sumas[indiceSumaActual][1] < 2) {
            sumas[indiceSumaActual][1]++;
        }

        // Si mas de dos filas ya sumaron lo mismo que la actual, no es escalar
        else {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    int m1[3][3] = {
        {1, 2, 3},
        {3, 2, 2},
        {1, 1, 2}
    };
    assert(escalar(3, m1) == 0);

    int m2[3][3] = {
        {1,  2, 0},
        {3, -1, 1},
        {1,  1, 1}
    };
    assert(escalar(3, m2) == 0);

    int m3[3][3] = {
        {2, -1, 3},
        {3,  2, 0},
        {1,  1, 2}
    };
    assert(escalar(3, m3) == 1);

    int m4[2][2] = {
        {1, 1},
        {2, 2}
    };
    assert(escalar(2, m4) == 1);

    int m5[1][1] = {
        {1}
    };
    assert(escalar(1, m5) == 1);

    puts("OK!");

    return 0;
}
