#include "tp11_ej17.h"
#include <stdio.h>
#include <assert.h>

int
main(void) {
    // Reserva los recursos para contabilizar las ardillas del parque
    // agrupando las cantidades en bloques (manzanas) de 100 metros x 100 metros.
    // Por ejemplo:
    // - El bloque 0,0 comprende de [0, 100) metros en vertical y de [0, 100) metros en horizontal
    // - El bloque 0,1 comprende de [0, 100) metros en vertical y de [100, 200) metros en horizontal
    // - El bloque 1,0 comprende de [100, 200) metros en vertical y de [0, 100) metros en horizontal
    squirrelCensusADT centralPark = newSquirrelCensus(100);

    // Se registra a una ardilla a
    // - 299 metros en línea vertical del extremo superior izquierdo del parque
    // - 120 metros en línea horizontal del extremo superior izquierdo del parque
    // de forma que se contabilizará a la ardilla en el bloque 2,1
    assert(countSquirrel(centralPark, 299, 120) == 1);
    // Se registra a otra ardilla en el mismo bloque que la invocación anterior
    assert(countSquirrel(centralPark, 201, 140) == 2);

    // Se registra a una ardilla en el bloque 0,0
    assert(countSquirrel(centralPark, 15, 98) == 1);

    // Se consulta la cantidad de ardillas del bloque de las primeras dos invocaciones a countSquirrel
    assert(squirrelsInBlock(centralPark, 250, 150) == 2);
    // Se consulta la cantidad de ardillas del bloque de la tercera invocación a countSquirrel
    assert(squirrelsInBlock(centralPark, 0, 0) == 1);
    // Se consulta la cantidad de ardillas en un bloque distinto a los dos anteriores, el bloque 29,15
    assert(squirrelsInBlock(centralPark, 2965, 1540) == 0);

    int cant = 10000;
    for(int i=1; i <= cant; i++) {
        assert(countSquirrel(centralPark, 90001, 89000) == i);
    }
    assert(squirrelsInBlock(centralPark, 90001, 89000) == cant);
    assert(squirrelsInBlock(centralPark, 90030, 89070) == cant);


    for(int i=7000; i< 80000; i+=2) {
        for(int j=0; j < 100000; j+=100) {
            assert(squirrelsInBlock(centralPark, i, j) == 0);
        }
    }

    // Libera los recursos utilizados para contabilizar las ardillas del parque
    freeSquirrelCensus(centralPark);

    puts("OK!");
    return 0;
}