#include <stdio.h>
#include <assert.h>

#define END -1

#define ORDER_ASC       1       // Ascendente
#define ORDER_DESC      -1      // Descendente
#define ORDER_UNKNOWN   0       // Desconocido

// Una instancia no puede decidir si:
// Caso 1: Es el terminador (el terminador no decide por caso base)
// Caso 2: Es el ultimo elemento (no puede decidir porque no tiene con quien compararse)

// Si no caigo en alguno de los anteriores dos casos puestos en el caso base, entonces quiere
// decir que estoy parado en el ante-ultimo elemento o alguno anterior

// En ese caso, si mi siguiente invocacion devolvio ORDEN_UNKNOWN quiere decir que:
// Caso 1: No pudo decidir, pues es el ultimo. Este caso esta caracterizado porque el sub-siguiente es
//         el terminador. En este caso, decido yo
// Caso 2: El array tiene algun elemento que no coincide con el orden que debiera tener. En este caso,
//         propago ORDER_UNKNOWN para atras (hacia las invocaciones previas)

// Si no me devolvieron ORDER_UNKNOWN, debo chequear que el orden relativo entre el elemento actual y
// su siguiente (ord) coincida con el devuelto por la instancia siguiente de la funcion (ret). Si
// coinciden propago ese valor, sino, indico ORDER_UNKNOWN

int orden(const int * arr) {
    // Caso base
    if (*arr == END || *(arr + 1) == END) {
        return ORDER_UNKNOWN;
    }

    // Caso general
    int ret = orden(arr + 1);
    int actual = *arr, siguiente = *(arr + 1), subsiguiente = *(arr + 2);
    int ord = siguiente == actual ? ORDER_UNKNOWN : (siguiente > actual ? ORDER_ASC : ORDER_DESC);

    if (ret == ORDER_UNKNOWN) {
        return subsiguiente == END ? ord : ORDER_UNKNOWN;
    }

    return ord == ret ? ret : ORDER_UNKNOWN;
}

int main(void) {
    int v[] = {2, 1, 2, 8, 20, 12343, -1}; 
    int v2[] = {10, 10, 9, 5, 3, -1}; 
    
    assert(orden(v) == 0);
    assert(orden(v + 1) == 1);
    assert(orden(v2) == 0);
    assert(orden(v2 + 1) == -1);
    assert(orden(v2 + 4) == 0);

    puts("OK!");
    return 0;
}
