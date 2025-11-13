#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "piersADT.h"

int main(void) {
    piersADT piersAdt = newPiers();
    assert(addPier(piersAdt, 5) == 1); // Agrega el puerto 5
    assert(addPierDock(piersAdt, 5, 4) == 1); // Agrega el muelle 4 del puerto 5
    assert(addPierDock(piersAdt, 5, 7) == 1);

    assert(pierDocks(piersAdt, 5) == 2);            // LO AGREGUE YO
    assert(pierShips(piersAdt, 5) == 0);            // LO AGREGUE YO

    assert(addPier(piersAdt, 10) == 1);
    assert(addPierDock(piersAdt, 10, 1) == 1);
    assert(addPierDock(piersAdt, 10, 7) == 1);

    // No hay una embarcación amarrada en el muelle 4 del puerto 5
    assert(shipInDock(piersAdt, 5, 4) == 0);
    assert(shipInDock(piersAdt, 5, 7) == 0);
    assert(pierShips(piersAdt, 5) == 0);
    assert(shipInDock(piersAdt, 10, 1) == 0);
    assert(shipInDock(piersAdt, 10, 7) == 0);
    assert(pierShips(piersAdt, 10) == 0);

    assert(pierDocks(piersAdt, 10) == 2);           // LO AGREGUE YO
    assert(addPierDock(piersAdt, 10, 7) == 0);      // LO AGREGUE YO
    assert(pierDocks(piersAdt, 10) == 2);           // LO AGREGUE YO
    assert(addPierDock(piersAdt, 10, 5) == 1);      // LO AGREGUE YO
    assert(pierDocks(piersAdt, 10) == 3);           // LO AGREGUE YO

    // Se amarra una embaración en el muelle 4 del puerto 5
    assert(dockShip(piersAdt, 5, 4) == 1);
    assert(shipInDock(piersAdt, 5, 4) == 1);
    assert(shipInDock(piersAdt, 5, 7) == 0);
    assert(pierShips(piersAdt, 5) == 1);
    assert(dockShip(piersAdt, 5, 7) == 1);
    assert(shipInDock(piersAdt, 5, 4) == 1);
    assert(shipInDock(piersAdt, 5, 7) == 1);
    assert(pierShips(piersAdt, 5) == 2);

    // Se desamarra la embaración del muelle 7 del puerto 5
    assert(undockShip(piersAdt, 5, 7) == 1);
    assert(shipInDock(piersAdt, 5, 4) == 1);
    assert(shipInDock(piersAdt, 5, 7) == 0);
    assert(pierShips(piersAdt, 5) == 1);
    freePiers(piersAdt);
    return 0;
}
