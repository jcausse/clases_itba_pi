#include <stdlib.h>
#include "busADT.h"

#define BLOCK 5

typedef struct {
    elemType                info;
    bool                    inUse;
} busInfoElem;

struct busCDT {
    busInfoElem *           busInfoArray;   // Array dinamico de lineas de colectivos
    size_t                  arraySize;      // Tamaño total del array
    size_t                  totalInUse;     // Cantidad de lineas registradas
    elemTypeComparator      cmp;            // Funcion comparadora de info de lineas
};

busADT newBusADT(elemTypeComparator cmp) {
    busADT toReturn = calloc(1, sizeof(struct busCDT));
    toReturn->cmp = cmp;
    return toReturn;
}

void freeBusADT(busADT adt) {
    free(adt->busInfoArray);
    free(adt);
}

static void expandBusInfoArray(busADT adt, unsigned int busNumber) {
    if (busNumber >= adt->arraySize) {
        adt->busInfoArray = realloc(adt->busInfoArray, (busNumber + 1) * sizeof(busInfoElem));
        for (unsigned int i = adt->arraySize; i < busNumber + 1; i++) {
            adt->busInfoArray[i].inUse = false;
        }
        adt->arraySize = busNumber + 1;
    }
}

void busSet(busADT adt, unsigned int busNumber, elemType info) {
    expandBusInfoArray(adt, busNumber);
    adt->busInfoArray[busNumber].info = info;
    adt->totalInUse += adt->busInfoArray[busNumber].inUse ? 0 : 1;
    adt->busInfoArray[busNumber].inUse = true;
}

static bool isBusLineSet(busADT adt, unsigned int busNumber) {
    return busNumber < adt->arraySize && adt->busInfoArray[busNumber].inUse;
}

void busSetIfAbsent(busADT adt, unsigned int busNumber, elemType info) {
    if (!isBusLineSet(adt, busNumber)) {
        busSet(adt, busNumber, info);
    }
}

int busInfo(const busADT adt, unsigned int busNumber, elemType * info) {
    if (isBusLineSet(adt, busNumber)) {
        *info = adt->busInfoArray[busNumber].info;
        return 1;
    }
    return 0;
}

void removeBus(busADT adt, unsigned int busNumber) {
    if (isBusLineSet(adt, busNumber)) {
        adt->busInfoArray[busNumber].inUse = false;
        (adt->totalInUse)--;
    }
}

size_t busSize(const busADT adt) {
    return adt->totalInUse;
}

int * busCodes(const busADT adt, elemType info, size_t * dim) {
    int * toReturn = NULL;
    size_t write = 0;
    for (size_t i = 0; i < adt->arraySize; i++) {
        if (adt->busInfoArray[i].inUse && adt->cmp(adt->busInfoArray[i].info, info) == 0) {
            if (write % BLOCK == 0) {
                toReturn = realloc(toReturn, (write + BLOCK) * sizeof(int));
            }
            toReturn[write] = i;
            write++;
        }
    }
    if (write > 0) {
        toReturn = realloc(toReturn, write * sizeof(int));
    }
    *dim = write;
    return toReturn;
}
