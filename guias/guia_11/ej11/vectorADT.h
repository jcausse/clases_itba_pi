#ifndef vectorADT_h
#define vectorADT_h

#include <stdio.h>

#define ELEM_NOT_FOUND -1

typedef struct vectorCDT * vectorADT;

typedef int elemType; // Tipo de elemento a insertar

/**
 * Funcion de comparacion "estandar". Recibe dos elemType, y devuelve:
 * - un valor positivo si source > target, segun el criterio de comparacion
 * - un valor negativo si source < target, segun el criterio de comparacion
 * - cero si source = target, segun el criterio de comparacion
 */
typedef int (* CompareFunction)(elemType source, elemType target);
typedef void (* FreeFunction)(elemType);

/* Crea un nuevo vector dinámico de elementos genéricos
** Inicialmente el vector está vacío
** Cada elemento a insertar será de tipo elemType
** Si no se pudo crear retorna NULL.
** La función compare retorna negativo si source es "menor" que target,
** positivo si source es "mayor""que target o cero si se los considera iguales
** (la misma convención que strcmp)
*/
vectorADT newVector(CompareFunction cmpFn, FreeFunction freeFn);

/* Libera todos los recursos reservados por el TAD */
void freeVector(vectorADT v);

/* Almacena los elementos de elems a partir de la posición index, donde elems es
un vector de dim elementos.
** En caso de ser necesario agranda el vector.
** El resto de los elementos del vector no se modifican y permanecen en la misma
posición.
** Si se recibe NULL o no se pudo insertar retorna cero.
** Si alguna posición está ocupada, la deja como estaba.
** Retorna cuántos elementos pudo almacenar.
** Ejemplo:
** si v tiene ocupadas las posiciones 1,3 y 6
** se invoca con index=2, dim=5
** el vector actual quedará con los mismos elementos en las posiciones 1, 3 y 6
** pero además v[2]=elems[0], v[4]=elems[2], v[5]=elems[3]
** y la función retorna 3
*/
size_t put(vectorADT v, elemType * elems, size_t dim, size_t index);

/* Retorna el índice en el cual está insertada la primera aparicion el elemento, o ELEM_NOT_FOUND si no lo
encuentra */
int getIdx(vectorADT v, elemType elem);

/* Elimina el elemento en la posición index. Si index está fuera del vector no
hace nada */
void deleteElement(vectorADT v, size_t index);

/* Retorna cuántos elementos hay insertados en el vector */
int elementCount(vectorADT v);

#endif
