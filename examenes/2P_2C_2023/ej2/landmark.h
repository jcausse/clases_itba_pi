#ifndef LANDMARK_H
#define LANDMARK_H

#include <stdlib.h>

#define CHUNK_SIZE 100
#define NO_SUCH_LANDMARK -1

typedef const char * landmarkType;
typedef struct landmarkCDT * landmarkADT;
typedef int (*landmarkTypeComparator) (landmarkType, landmarkType);

/**
* Crea una nueva colección de sitios de interés. Sólo se registrará un sitio cada
* 100 metros (uno entre los 0 y 99 metros, posiblemente otro entre los 100 y 199, etc.)
*/
landmarkADT newLandmark(landmarkTypeComparator cmp);

/**
* Agrega un punto de interés #site a #meters metros del origen. Si ya había
* un sitio, sólo queda #site (ver programa de testeo)
*/
void addLandmark(landmarkADT landmark, size_t meters, landmarkType site);

/*
* Retorna 1 si a esa distancia aproximada hay un sitio de interés. Ejemplo: si
* meters es 135 retorna 1 si se registró algún sitio de interés entre los 100 y 199
* metros), 0 sinó
*/
int hasLandmark(const landmarkADT landmark, size_t meters);

/*
* Retorna la distancia aproximada en la cual se encuentra el sitio de interés
* o -1 si no existe. Ejemplo: si el sitio de interés se indicó que está a 135
* metros retorna 100, si se indicó a 1240 metros retorna 1200
*/
int distance(const landmarkADT landmark, landmarkType site);

/*
* Retorna cuántos sitios de interés se registraron
*/
size_t landmarkCount(const landmarkADT landmark);

/*
* Retorna un vector con los sitios de interés, en orden ascendente por distancia
* al origen. Si no hubiera sitios de interés retorna NULL
*/
landmarkType * landmarks(const landmarkADT landmark);

/*
* Retorna un vector con los sitios de interés entre dos distancias,
* en orden ascendente por distancia al origen, dejando en *dim la cantidad
* Si from es mayor que to o no hay sitios de interés en ese rango retorna NULL y
* deja *dim en cero
*/
landmarkType * landmarksBetween(const landmarkADT landmark, size_t from, size_t to, size_t *dim);

void freeLandmark(landmarkADT landmark);

#endif // LANDMARK_H
