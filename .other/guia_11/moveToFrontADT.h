#ifndef __movetofront__h
#define __movetofront__h

typedef struct moveToFrontCDT * moveToFrontADT;
 
typedef ... elemType;  	// Tipo de elemento a insertar
 
/*
** Retorna 0 si los elementos son iguales, negativo si e1 es "menor" que e2 y positivo 
** si e1 es "mayor" que e2
*/
typedef int (*compare) (elemType e1, elemType e2);
 
/* Retorna un nuevo conjunto de elementos genéricos. Al inicio está vacío */
moveToFrontADT newMoveToFront(compare cmp);

/* Libera toda la memoria reservada por el TAD */
void freeMoveToFront(moveToFrontADT moveToFront);
 
/* Inserta un elemento si no está. Lo inserta al final.
** Retorna 1 si lo agregó, 0 si no.
*/
unsigned int add(moveToFrontADT moveToFront, elemType elem);
  
/* Retorna la cantidad de elementos que hay en la colección */
unsigned int size(moveToFrontADT moveToFront);
 
/* Se ubica al principio del conjunto, para poder iterar sobre el mismo */
void toBegin(moveToFrontADT moveToFront);

/* Retorna 1 si hay un elemento siguiente en el iterador, 0 si no */
int hasNext(moveToFrontADT moveToFront);

/* Retorna el siguiente elemento. Si no hay siguiente elemento, aborta */
elemType next(moveToFrontADT moveToFront);

/* Retorna una copia del elemento. Si no existe retorna NULL.
** Para saber si el elemento está, usa la función compare. 
** Si el elemento estaba lo ubica al principio.
 */
elemType * get(moveToFrontADT moveToFront, elemType elem);
#endif