#ifndef __tp11_ej10_h

#define __tp11_ej10_h

#include <string.h>
typedef struct bagCDT * bagADT;
 
typedef const char * elemType;	// Tipo de elemento a insertar, cambiar al que sea necesario
 
/**
** Retorna 0 si los elementos son iguales 
*/
typedef int (*compare) (elemType e1, elemType e2);

/* Libera toda la memoria reservada por el TAD */
void freeBag( bagADT bag);
 
/* Retorna un nuevo bag de elementos genéricos. Al inicio está vacío */
bagADT newBag(compare cmp);
 
/* Inserta un elemento. Retorna cuántas veces está
** elem en el conjunto luego de haberlo insertado (p.e. si es la primera inserción retorna 1).
*/
unsigned int add(bagADT bag, elemType elem);

/* Remueve una aparición de un elemento. Retorna cuántas veces está
** elem en el conjunto luego de haberlo borrado
*/
unsigned int delete(bagADT bag, elemType elem);

/* Retorna cuántas veces aparece el elemento en el bag */
unsigned int count(const bagADT bag, elemType elem);
 
/* Retorna la cantidad de elementos distintos que hay en el bag */
unsigned int size(const bagADT bag);
 
/* Retorna el elemento que aparece más veces. Si hay más de uno 
** con esa condición, retorna cualquiera de los dos. 
** Precondicion: el bag no debe estar vacio. En caso de estar vacío, aborta
** la ejecución
*/
elemType mostPopular(bagADT bag);

#endif