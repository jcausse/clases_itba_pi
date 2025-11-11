#include "busDriverADT.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef char * Driver;

typedef struct DriverListNode {         // Lista de conductores (ordenada alfabeticamente case-insensitive)
    Driver name;                        // Nombre del conductor
    struct DriverListNode * next;       // Proximo conductor en la lista
} DriverListNode;

typedef struct BusLine {                // Linea de colectivo
    bool created;                       // Indica si la linea se creo o no
    size_t driverCount;                 // Cantidad de conductores para esa linea (tamaño de la lista)
    DriverListNode * first;             // Puntero al primer nombre
} BusLine;

struct busDriverCDT {                   // El CDT en si
    size_t busLineCount;                // Cantidad de lineas de colectivo totales (cantidad de posiciones ocupadas en el array, que tienen created en true)
    size_t linesSize;                   // Tamaño del array. Coincide con 1 + el numero de la linea mas grande que se ingreso
    BusLine * lines;                    // Array dinamico de BusLine que se expande cuando se ingresa una linea con el mayor numero
};

busDriverADT newBusDriverADT() {
    return calloc(1, sizeof(struct busDriverCDT));
}

static void freeDriverList(DriverListNode * list) {
    if (list == NULL) {
        return;
    }
    DriverListNode * aux = list->next;
    free(list->name);
    free(list);
    freeDriverList(aux);
}

void freeBusDriverADT(busDriverADT adt) {
    for (size_t i = 0; i < adt->linesSize; i++) {
        if (adt->lines[i].created) {
            freeDriverList(adt->lines[i].first);
        }
    }
    free(adt->lines);
    free(adt);
}
 
/* !!! */
int newBusLine(busDriverADT adt, unsigned int busLine) {
    // Caso 1: Ingresan un numero de linea que ya tengo creada en heap, y ya esta creada
    if (busLine < adt->linesSize && adt->lines[busLine].created) {
        return 0;
    }

    // Caso 2: Ingresan una linea que no esta creada
    // Caso 2.1: La nueva linea tiene un numero mayor que la mas grande agregada hasta el momento -> Expando el array
    if (busLine >= adt->linesSize) {
        adt->lines = realloc(adt->lines, (busLine + 1) * sizeof(BusLine));
        for (size_t i = adt->linesSize; i < busLine + 1; i++) {
            adt->lines[i].created = false;
            adt->lines[i].driverCount = 0;
            adt->lines[i].first = NULL;
        }
        adt->linesSize = busLine + 1;
    }

    // Caso 2.2: Ya tenia la linea en el array, pero no estaba creada (+ Continuacion 2.1)
    adt->lines[busLine].created = true;
    (adt->busLineCount)++;
    return 1;
}

/* !!! */
int busLinesCount(const busDriverADT adt) {
    return adt->busLineCount;
}

static bool isValidLine(const busDriverADT adt, unsigned int busLine) {
    return busLine < adt->linesSize && adt->lines[busLine].created;
}

/* !!! */
int driversCount(const busDriverADT adt, unsigned int busLine) {
    return isValidLine(adt, busLine) ? adt->lines[busLine].driverCount : 0;
}
 
char ** drivers(const busDriverADT adt, unsigned int busLine) {
    if (!isValidLine(adt, busLine)) {
        return NULL;
    }
    BusLine line = adt->lines[busLine];
    char ** ret = malloc(line.driverCount * sizeof(Driver));

    size_t i;
    DriverListNode * current;
    for (i = 0, current = line.first; i < line.driverCount; i++, current = current->next) {
        ret[i] = strdup(current->name);
    }
    return ret;
}

static DriverListNode * addDriverToList(DriverListNode * list, const char * driver, bool * added) {
    int c;
    if (list == NULL || (c = strcasecmp(list->name, driver)) > 0) {
        DriverListNode * aux = malloc(sizeof(DriverListNode));
        aux->name = strdup(driver);
        aux->next = list;
        *added = true;
        return aux;
    }
    if (c == 0) {
        *added = false;
        return list;
    }
    list->next = addDriverToList(list->next, driver, added);
    return list;
}
  
void addDriver(busDriverADT adt, unsigned int busLine, const char * driver) {
    if (!isValidLine(adt, busLine)) {
        return;
    }
    bool added = false;
    adt->lines[busLine].first = addDriverToList(adt->lines[busLine].first, driver, &added);
    if (added) {
       (adt->lines[busLine].driverCount)++; 
    }
}

static DriverListNode * removeDriverFromList(DriverListNode * list, const char * driver, bool * removed) {
    int c;
    if (list == NULL || (c = strcasecmp(list->name, driver)) > 0) {
        *removed = false;
        return NULL;
    }
    if (c == 0) {
        DriverListNode * aux = list->next;
        free(list->name);
        free(list);
        *removed = true;
        return aux;
    }
    list->next = removeDriverFromList(list->next, driver, removed);
    return list;
}

void removeDriver(busDriverADT adt, unsigned int busLine, const char * driver) {
    if (!isValidLine(adt, busLine)) {
        return;
    }
    bool removed = false;
    adt->lines[busLine].first = removeDriverFromList(adt->lines[busLine].first, driver, &removed);
    if (removed) {
        (adt->lines[busLine].driverCount)--; 
    }
}
