#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "counters.h"

int main(void) {
    countersADT terminalA = newCounters(10);
    enterCounter(terminalA, 5, "Foo"); // "Foo" ingresa a la cola del mostrador 5
    enterCounter(terminalA, 5, "Bar");
    enterCounter(terminalA, 5, "Bar");
    enterCounter(terminalA, 4, "Abc");
    enterCounter(terminalA, 4, "Xyz");
    // Se desea consultar los pasajeros que están esperando en el mostrador 5
    toBeginByCounter(terminalA, 5);
    // "Foo" es el primero que ingresó al mostrador 5
    assert(hasNextByCounter(terminalA, 5) == 1);
    assert(strcmp(nextByCounter(terminalA, 5), "Foo") == 0);
    assert(hasNextByCounter(terminalA, 5) == 1);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);
    toBeginByCounter(terminalA, 4);
    assert(hasNextByCounter(terminalA, 4) == 1);
    assert(strcmp(nextByCounter(terminalA, 4), "Abc") == 0);
    // Se pueden usar en simultáneo las funciones de iteración para consultar
    // los pasajeros que están esperando en distintos mostradores
    assert(hasNextByCounter(terminalA, 5) == 1);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);
    assert(hasNextByCounter(terminalA, 4) == 1);
    assert(strcmp(nextByCounter(terminalA, 4), "Xyz") == 0);
    assert(hasNextByCounter(terminalA, 5) == 0);
    assert(hasNextByCounter(terminalA, 4) == 0);
    // Se realiza, para cada mostrador, el checkIn del pasajero que está primero
    // esperando en la cola
    size_t checkInResultDim;
    struct checkInResult * checkInResultVec;
    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 2); // Se realizó el checkIn en dos mostradores: 4 y 5
    // Resultado del checkIn en el mostrador 4
    assert(checkInResultVec[0].counterNumber == 4);
    assert(checkInResultVec[0].waitingPassengers == 1);
    assert(strcmp(checkInResultVec[0].checkedInPassenger, "Abc") == 0);
    // Resultado del checkIn en el mostrador 5
    assert(checkInResultVec[1].counterNumber == 5);
    assert(checkInResultVec[1].waitingPassengers == 2);
    assert(strcmp(checkInResultVec[1].checkedInPassenger, "Foo") == 0);
    free(checkInResultVec);
    toBeginByCounter(terminalA, 5);
    toBeginByCounter(terminalA, 4);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);
    assert(strcmp(nextByCounter(terminalA, 4), "Xyz") == 0);
    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 2); // Se hizo checkIn en dos mostradores: 4 y 5
    // Resultado del checkIn en el mostrador 4
    assert(checkInResultVec[0].counterNumber == 4);
    assert(checkInResultVec[0].waitingPassengers == 0);
    assert(strcmp(checkInResultVec[0].checkedInPassenger, "Xyz") == 0);
    // Resultado del checkIn en el mostrador 5
    assert(checkInResultVec[1].counterNumber == 5);
    assert(checkInResultVec[1].waitingPassengers == 1);
    assert(strcmp(checkInResultVec[1].checkedInPassenger, "Bar") == 0);
    free(checkInResultVec);
    toBeginByCounter(terminalA, 5);
    toBeginByCounter(terminalA, 4);
    assert(strcmp(nextByCounter(terminalA, 5), "Bar") == 0);
    assert(hasNextByCounter(terminalA, 4) == 0);
    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 1);
    // Resultado del checkIn en el mostrador 5
    assert(checkInResultVec[0].counterNumber == 5);
    assert(checkInResultVec[0].waitingPassengers == 0);
    assert(strcmp(checkInResultVec[0].checkedInPassenger, "Bar") == 0);
    free(checkInResultVec);
    toBeginByCounter(terminalA, 5);
    toBeginByCounter(terminalA, 4);
    assert(hasNextByCounter(terminalA, 5) == 0);
    assert(hasNextByCounter(terminalA, 4) == 0);
    checkInResultVec = checkInCounters(terminalA, &checkInResultDim);
    assert(checkInResultDim == 0); // Ningún mostrador hizo checkIn
    assert(checkInResultVec == NULL);
    freeCounters(terminalA);

    puts("OK!");
    return 0;
}
