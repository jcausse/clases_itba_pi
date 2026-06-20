#ifndef __SETADTH_

#define __SETADTH_

#include "listADT.h"		// incluye elemType (usamos la versión que recibe la función de comparación)

typedef struct setCDT * setADT;

/* Retorna un nuevo conjunto vacío */
setADT newSet(int (*compare)(elemType, elemType));

void freeSet(setADT set);

int isEmptySet(setADT set);

int setContains(const setADT set, elemType element);

int addElement(setADT set, elemType element);

int deleteElement(setADT set, elemType element);

int sizeSet(const setADT set);

setADT unionSet(setADT set1, setADT set2);

setADT intersectionSet(setADT set1, setADT set2);

setADT diffSet(setADT set1, setADT set2);

#endif