#ifndef COUNTERS_H
#define COUNTERS_H

#include <stdlib.h>

typedef struct countersCDT * countersADT;

/* Crea un sistema de administración de mostradores a partir de la cantidad
* máxima #maxCounters de mostradores que tendrá el aeropuerto.
* Se asume que la gran mayoría de los mostradores serán utilizados por las aerolíneas.
* Si maxCounters es cero retorna NULL.
*/
countersADT newCounters(size_t maxCounters);

/* Ingresa al pasajero #passenger en la cola de espera del mostrador #counterNumber
* para luego poder hacer el checkIn de su vuelo.
* Un mismo pasajero puede ingresar múltiples veces al mismo mostrador o a varios
* mostradores distintos.
* Se asume que los nombres de los pasajeros son cortos.
* Falla si #counterNumber es mayor o igual a la cantidad máxima de mostradores.
*/
void enterCounter(countersADT counters, size_t counterNumber, const char * passenger);

/* Funciones de iteración para poder consultar para un mostrador los pasajeros que están
* esperando, en ORDEN DE LLEGADA (ver ejemplo en programa de prueba)
*/
void toBeginByCounter(countersADT counters, size_t counterNumber);

size_t hasNextByCounter(const countersADT counters, size_t counterNumber);

const char * nextByCounter(countersADT counters, size_t counterNumber);

/* Para cada mostrador, realiza el checkIn del pasajero que está esperando primero en la
* cola, si es que hay al menos un pasajero esperando en ese mostrador.
* Retorna un arreglo donde, para cada mostrador donde se hizo checkIn, se indica:
* - El número del mostrador
* - El nombre del pasajero que hizo checkIn en el mostrador y salió de la cola de espera
* - La cantidad de pasajeros esperando en el mostrador luego de la operación
* respetando el ORDEN ASCENDENTE por número de mostrador
* Deja en un parámetro de entrada/salida la dimensión del vector de retorno
*/
struct checkInResult {
    size_t counterNumber;
    const char * checkedInPassenger;
    size_t waitingPassengers;
};
struct checkInResult * checkInCounters(countersADT counters, size_t * checkInResultDim);

/* Libera los recursos utilizados por el TAD
*/
void freeCounters(countersADT counters);

#endif // COUNTERS_H
