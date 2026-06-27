#ifndef EJ2_H
#define EJ2_H

#include <stddef.h>

typedef struct randomCDT * randomADT; 
 
/** 
* TAD para almacenar números aleatorios entre 1 y maxValue inclusive 
* Si maxValue es 0 retorna NULL 
*/ 
randomADT newRandomADT(unsigned char maxValue);
 
/** 
* Crea y almacena qty números aleatorios menores o iguales a maxValue 
*/ 
void newRandoms(randomADT adt, size_t qty); 
 
/** 
* Crea y almacena un número aleatorio menor o igual a maxValue 
*/ 
void newRandom(randomADT adt); 
 
/** 
* Retorna cuántos números distintos se han almacenado 
*/ 
unsigned char numbers(const randomADT adt); 

/** 
* Retorna el número que más veces apareció (si hay más de uno cualquiera de ellos) 
* Si no se generó ningún número retorna -1 
*/ 
int mostFrequent(const randomADT adt);
 
void freeRandomADT(randomADT adt); 

#endif // EJ2_H
