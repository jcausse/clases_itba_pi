#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MASK_N2 0x0F
#define NUM_SIZE_BITS 4

#define GET_N1(x) ((x) >> NUM_SIZE_BITS)
#define GET_N2(x) ((x) & MASK_N2)

/**
 * @brief Obtener el i-esimo elemento de un array como el de la consigna
 * @details El array tiene los elementos pares en las posiciones altas y los impares en las bajas
 *          Cuando i es par, se obtiene la posicion alta del elemento i/2 del vector
 *          Cuando i es impar, se obtiene la posicion baja del elemento i/2 del vector
 * @return Retorna el numero en la posicion i (considerando que cada posicion real del vector contiene 2 numeros)
 */
static unsigned char get_elem(const unsigned char vector[], const int i) {
    return i % 2 == 0 ? GET_N1(vector[i / 2]) : GET_N2(vector[i / 2]);
}

static double average(const unsigned char vector[], const int dim) {    
    double sum = 0;
    
    for (int i = 0; i < dim; i++) {
        sum += get_elem(vector, i);
    }

    return sum / dim;
}

/* Calcula la desviacion estandar */
double desv(const unsigned char vector[], const int dim) {
    if (dim <= 1) {
        return 0;
    }

    const double avg = average(vector, dim);
    
    unsigned char elem;
    double sum = 0;

    for (int i = 0; i < dim; i++) {
        elem = get_elem(vector, i);
        sum += (elem - avg) * (elem - avg);
    }

    return sqrt(sum / dim);
}

int main(void) {
    unsigned char arreglo2[] = { 0x33, 0x33, 0x33, 0x33, 0x33 };
    for(int i=0; i <= 10; i++){
        assert(desv(arreglo2, i)==0);
    }

    unsigned char arreglo[] = { 0x37, 0xF2, 0x03, 0x4A, 0xFF };
    assert(desv(arreglo, 1)==0);
    assert(desv(arreglo, 2)==2.0);

    assert(desv(arreglo, 3) > 4.98 && desv(arreglo, 3) < 4.99);

    assert(desv(arreglo, 10) > 5.6071 && desv(arreglo, 3) < 5.6072);

    puts("OK!");
}
