#include <stdio.h>
#include <limits.h>
#include <assert.h>

void firstN(unsigned char v[], unsigned int dim, unsigned int n, int * final_dim, int * deleted_elems) {
    unsigned char apariciones[UCHAR_MAX + 1] = {0};         // UCHAR_MAX es 255
    unsigned int read, write = 0;

    if (n > 0) {                                    
        for (read = 0; read < dim; read++) {                // Leo todos
            if (apariciones[v[read]] < n) {                 // Los que tengan menos de n apariciones
                apariciones[v[read]]++;                     //    - les sumo 1 aparicion
                v[write] = v[read];                         //    - y los copio
                write++;
            }
        }
    }

    *final_dim = write;                 // Dimension final (write apunta al prox elemento a escribir)
    *deleted_elems = dim - write;       // Cantidad de eliminados dado como dimension inicial - dimension final
}

//--------------------------------------------------------------------------------------------------
// TEST

bool arrayEquals(unsigned int dim, const unsigned char arr1[dim], const unsigned char arr2[dim]) {
    for (unsigned int i = 0; i < dim; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int dim, del;

    unsigned char v[] = {1, 2, 1, 3, 1, 4, 5, 2};
    unsigned char result1[] = {1, 2, 1, 3, 1, 4, 5, 2};
    firstN(v, 8, 3, &dim, &del); // dim es 8, del es 0, v no cambia
    assert(dim == 8);
    assert(del == 0);
    assert(arrayEquals(8, v, result1));

    firstN(v, 8, 8, &dim, &del); // dim es 8, del es 0, v no cambia
    assert(dim == 8);
    assert(del == 0);
    assert(arrayEquals(8, v, result1));

    firstN(v, 8, 4, &dim, &del); // dim es 8, del es 0, v no cambia
    assert(dim == 8);
    assert(del == 0);
    assert(arrayEquals(8, v, result1));

    unsigned char result2[] = {1, 2, 3, 4, 5};
    firstN(v, 8, 1, &dim, &del); // dim=5, del=3, v = {1, 2, 3, 4, 5};
    assert(dim == 5);
    assert(del == 3);
    assert(arrayEquals(5, v, result2));

    unsigned char w[] = {1, 2, 1, 3, 1, 4, 5, 2};
    // El arreglo original no deberia modificarse, solo que como retorna dim en cero, ninguna
    // posicion del arreglo original contiene numeros validos, lo cual no quiere decir que "desaparezcan"
    // del array. El array, en este caso, queda como esta.
    unsigned char result3[] = {1, 2, 1, 3, 1, 4, 5, 2};
    firstN(w, 8, 0, &dim, &del); // dim=0, del=8, w = {}
    assert(dim == 0);
    assert(del == 8);
    assert(arrayEquals(8, w, result3));

    unsigned char t[] = {1, 2, 1, 3, 1, 4, 5, 2};
    unsigned char result4[] = {1, 2, 1, 3, 4, 5, 2};
    firstN(t, 8, 2, &dim, &del); // dim=7, del=1, t = {1, 2, 1, 3, 4, 5, 2}
    assert(dim == 7);
    assert(del == 1);
    assert(arrayEquals(7, t, result4));

    puts("OK!");

    return 0;
}
