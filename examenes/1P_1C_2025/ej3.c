#include <stdio.h>
#include <assert.h>

void cambio(
    unsigned int cant,
    unsigned int * const billetes100,   // Nota: El const aplica a las direcciones a las que apuntan los punteros, pero
    unsigned int * const billetes20,    //       NO a su contenido (si no fuera asi, no podria devolver la info usando los
    unsigned int * const billetes10,    //       parametros de salida).
    unsigned int * const monedas1 
) {
    *billetes100 = cant / 100;          // Cantidad de billetes de 100 es el cociente de dividir la cantidad por 100
    cant %= 100;                        // cant % 100 es el resto de esa division, lo que todavia me falta devolver

    *billetes20 = cant / 20;            // Cantidad de billetes de 20 es el cociente de dividir lo restante por 20
    cant %= 20;                         // cant % 20 es el resto de esa division, lo que todavia me falta devolver

    *billetes10 = cant / 10;            // Cantidad de billetes de 10 es el cociente de dividir lo restante por 10
    cant %= 10;                         // cant % 10 es el resto de esa division, lo que todavia me falta devolver

    *monedas1 = cant;                   // Como lo que me queda seguro es menor que 10, son la cantidad de monedas de 1
}

int main(void) {
    unsigned int cant, b100, b20, b10, m1;

    cant = 577;
    cambio(cant, &b100, &b20, &b10, &m1);
    assert(b100 == 5);
    assert(b20  == 3);
    assert(b10  == 1);
    assert(m1   == 7);

    cant = 1580;
    cambio(cant, &b100, &b20, &b10, &m1);
    assert(b100 == 15);
    assert(b20  == 4);
    assert(b10  == 0);
    assert(m1   == 0);

    cant = 19;
    cambio(cant, &b100, &b20, &b10, &m1);
    assert(b100 == 0);
    assert(b20  == 0);
    assert(b10  == 1);
    assert(m1   == 9);

    cant = 0;
    cambio(cant, &b100, &b20, &b10, &m1);
    assert(b100 == 0);
    assert(b20  == 0);
    assert(b10  == 0);
    assert(m1   == 0);

    puts("OK!");
}
