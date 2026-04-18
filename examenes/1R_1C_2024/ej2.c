#include <stdio.h>
#include <assert.h>

int asignaRampas(int v[], unsigned int dim, int aerolinea, unsigned int cant) {
    unsigned int write = 0, asignadas = 0;

    // Elimina-ceros clasico
    for (unsigned int read = 0; read < dim; read++) {
        if (v[read] != 0) {
            v[write] = v[read];
            write++;
        }
    }

    while (write < dim) {
        if (asignadas < cant) {
            v[write] = aerolinea;
            asignadas++;
        }
        else {
            v[write] = 0;
        }
        write++;
    }

    return asignadas;   // Retorna min{dim - write, cant}
}

//----------------------------------------------------------------------------------

bool arrayEquals(unsigned int dim, const int arr1[dim], const int arr2[dim]) {
    for (unsigned int i = 0; i < dim; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int v[] = {0, 44, 44, 0, 0, 0, 1};
    int n = asignaRampas(v, 7, 56, 2); // 2 rampas libres para la 56
    assert(n == 2);
    int res1[] = {44, 44, 1, 56, 56, 0, 0};
    assert(arrayEquals(7, v, res1));

    n = asignaRampas(v, 7, 1, 3); // 3 rampas más para la 1
    assert(n == 2);
    int res2[] = {44, 44, 1, 56, 56, 1, 1};
    assert(arrayEquals(7, v, res2));

    n = asignaRampas(v, 7, 88, 3); 
    assert(n == 0);
    assert(arrayEquals(7, v, res2));

    int v2[] = {44, 0, 1, 44, 44, 1, 0, 44};
    n = asignaRampas(v2, 8, 56, 1);
    assert(n == 1);
    int res3[] = {44, 1, 44, 44, 1, 44, 56, 0};
    assert(arrayEquals(8, v2, res3));

    puts("OK!");

    return 0;
}
