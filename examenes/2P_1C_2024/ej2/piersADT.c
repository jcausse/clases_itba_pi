#include "piersADT.h"

// Posibles estados de un muelle
typedef enum {
    DOCK_NOT_CREATED,       // Todavia no se creo
    DOCK_EMPTY,             // Esta creado, pero no tiene barco
    DOCK_FULL               // Esta creado, y tiene barco
} Dock;

// Posibles estados de un puerto
typedef enum {
    PIER_NOT_CREATED,       // Todavia no se creo
    PIER_CREATED            // Ya creado
} PierStatus;

typedef struct {
    PierStatus status;      // Estado de ese puerto (creado o no creado)
    Dock * docks;           // Arreglo dinamico de muelles por cada puerto
    size_t dockArraySize;   // Tamaño del arreglo (muelles creados + no creados)
    size_t dockCount;       // Cantidad de muelles que hay CREADOS en el puerto (<= dockArraySize)
    size_t shipCount;       // Cantidad total de barcos amarrados en todos los muelles del puerto (<= dockCount)
} Pier;

struct piersCDT {
    Pier * pierArray;       // Arreglo dinamico de puertos
    size_t pierArraySize;   // Tamaño del arreglo (puertos creados + no creados)
};

piersADT newPiers(void) {
    return calloc(1, sizeof(struct piersCDT));
}

static void initializePier(Pier * p) {
    p->status = PIER_NOT_CREATED;
    p->docks = NULL;
    p->dockArraySize = 0;
    p->dockCount = 0;
    p->shipCount = 0;
}

size_t addPier(piersADT piers, size_t pierNumber) {
    // Caso 1: Puerto ya creado
    if (pierNumber < piers->pierArraySize && piers->pierArray[pierNumber].status == PIER_CREATED) {
        return 0;
    }

    // Caso 2: Puerto no creado o hay que expandir
    // Caso 2.1: Chequeo si tengo que expandir
    if (pierNumber >= piers->pierArraySize) {
        piers->pierArray = realloc(piers->pierArray, (pierNumber + 1) * sizeof(Pier));  // Expando el array
        for (size_t i = piers->pierArraySize; i < pierNumber + 1; i++) {
            initializePier(&(piers->pierArray[i]));
        }
        piers->pierArraySize = pierNumber + 1;
    }

    // Caso 2.2: No habia que expandir (+ continuacion del 2.1)
    piers->pierArray[pierNumber].status = PIER_CREATED;
    return 1;
}

size_t addPierDock(piersADT piers, size_t pierNumber, size_t dockNumber) {
    return 0;
}

size_t dockShip(piersADT piers, size_t pierNumber, size_t dockNumber) {
    return 0;
}

int shipInDock(const piersADT piers, size_t pierNumber, size_t dockNumber) {
    return 0;
}
size_t pierShips(const piersADT piers, size_t pierNumber) {
    return 0;
}

size_t pierDocks(const piersADT piers, size_t pierNumber) {

}

size_t undockShip(piersADT piers, size_t pierNumber, size_t dockNumber) {
    return 0;
}

void freePiers(piersADT piers) {
}
