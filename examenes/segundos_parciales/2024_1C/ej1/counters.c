#include "counters.h"

typedef struct PassengerNode {
    const char * name;
    struct PassengerNode * next;
} PassengerNode;

typedef struct {
    PassengerNode * firstPassenger;     // Primer pasajero en la lista (el primero que llego)
    PassengerNode * lastPassenger;      // Ultimo pasajero en la lista (el ultimo que llego)
    size_t waitingPassengers;           // Cantidad de pasajeros en la lista
    PassengerNode * currentPassenger;   // Pasajero actual (iterador) por cada Counter
} Counter;

struct countersCDT {
    Counter * counterArray;
    size_t size;
    size_t countersWithPassengers;
};

countersADT newCounters(size_t maxCounters) {
    countersADT ret = malloc(sizeof(struct countersCDT));
    ret->counterArray = calloc(maxCounters, sizeof(Counter));
    ret->size = maxCounters;
    ret->countersWithPassengers = 0;
    return ret;
}

static PassengerNode * newPassenger(const char * name) {
    PassengerNode * ret = malloc(sizeof(PassengerNode));
    
    ret->name = name;               /* OPCION 1: Copia del puntero                                                    */
    // ret->name = strdup(name);    /* OPCION 2: Copia del string (strdup)  CUIDADO: HAY QUE LIBERAR LA COPIA DESPUES */

    ret->next = NULL;
    return ret;
}

void enterCounter(countersADT counters, size_t counterNumber, const char * passenger) {
    // Verificacion de parametros
    if (counterNumber >= counters->size || passenger == NULL) {
        return;
    }

    // Creao nuevo pasajero
    PassengerNode * createdPassenger = newPassenger(passenger);

    // Counter vacio -> Agrego el primer pasajero
    if (counters->counterArray[counterNumber].waitingPassengers == 0) {
        counters->counterArray[counterNumber].firstPassenger = createdPassenger;
        (counters->countersWithPassengers)++;
    }

    // Counter que ya tenia al menos un pasajero
    else {
        counters->counterArray[counterNumber].lastPassenger->next = createdPassenger;
    }
    
    // Agrego el nuevo pasajero como ultimo
    counters->counterArray[counterNumber].lastPassenger = createdPassenger;

    // Incremento la cantidad de pasajeros del counter
    (counters->counterArray[counterNumber].waitingPassengers)++;
}

void toBeginByCounter(countersADT counters, size_t counterNumber) {
    if (counterNumber >= counters->size) {
        return;
    }
    counters->counterArray[counterNumber].currentPassenger = counters->counterArray[counterNumber].firstPassenger;
}

size_t hasNextByCounter(const countersADT counters, size_t counterNumber) {
    if (counterNumber >= counters->size) {
        return 0;
    }
    return counters->counterArray[counterNumber].currentPassenger != NULL;
}

const char * nextByCounter(countersADT counters, size_t counterNumber) {
    if (counterNumber >= counters->size) {
        return NULL;
    }
    const char * ret = counters->counterArray[counterNumber].currentPassenger->name;
    counters->counterArray[counterNumber].currentPassenger = counters->counterArray[counterNumber].currentPassenger->next;
    return ret;
}

/**
 * @brief       Quita y devuelve el primer pasajero esperando en un counter
 * @details     Decrementa en 1 el numero de pasajeros esperando en ese counter
 */
static const char * popFirstPassenger(Counter * c) {
    const char * ret = c->firstPassenger->name;

    PassengerNode * toFree = c->firstPassenger;
    c->firstPassenger = toFree->next;

    free(toFree);
    (c->waitingPassengers)--;
    if (c->waitingPassengers == 0) {
        c->lastPassenger = NULL;
    }

    return ret;
}

struct checkInResult * checkInCounters(countersADT counters, size_t * checkInResultDim) {
    if (checkInResultDim == NULL) {
        return NULL;
    }

    // Caso donde ningun counter tiene pasajeros
    if (counters->countersWithPassengers == 0) {
        *checkInResultDim = 0;
        return NULL;
    }

    struct checkInResult * ret = malloc(counters->countersWithPassengers * sizeof(struct checkInResult));
    *checkInResultDim = counters->countersWithPassengers;

    size_t j = 0;
    for (size_t i = 0; i < counters->size; i++) {               // Para cada mostrador i
        if (counters->counterArray[i].waitingPassengers > 0) {  // Si tengo al menos 1 pasajero esperando, le hago el check-in al primero
            ret[j].counterNumber = i;                           // El pasajero esta esperando en el mostrador i-esimo
            ret[j].checkedInPassenger = popFirstPassenger(&(counters->counterArray[i]));    // Elimino el pasajero de la lista y recupero el nombre
            ret[j].waitingPassengers = counters->counterArray[i].waitingPassengers;         // La funcion anterior ya decremento el numero de pasajeros esperando
            if (counters->counterArray[i].waitingPassengers == 0) {                         // Se me vacio un counter
                (counters->countersWithPassengers)--;
            }
            j++;
        }
    }
    return ret;
}

void freePassengerList(PassengerNode * l) {
    if (l == NULL) {
        return;
    }
    PassengerNode * next = l->next;
    free(l);
    freePassengerList(next);
}

void freeCounters(countersADT counters) {
    for (size_t i = 0; i < counters->size; i++) {
        if (counters->counterArray[i].waitingPassengers > 0) {
            freePassengerList(counters->counterArray[i].firstPassenger);
        }
    }
    free(counters->counterArray);
    free(counters);
}
