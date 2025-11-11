#ifndef LIST_H
#define LIST_H

typedef struct listCDT * listADT;

typedef int elemType;                               // Tipo de elemento generico
typedef void (* FreeFn) (elemType);                 // Funcion que indica como liberar un elemento de tipo elemType
typedef void (* CompareFn) (elemType);              // Funcion que indica como comparar dos elementos de tipo elemType
typedef elemType (* MapperFn) (elemType);           // Funcion de mapeo

/**
 * @brief           Crea una lista vacia.
 * 
 * @param cmpFn     Funcion de comparacion para elementos de tipo elemType. NO PUEDE SER NULL.
 * @param freeFn    Funcion de liberacion de memoria para elementos de tipo elemType. Puede ser NULL en caso de que no sea necesario
 *                  utilizar una funcion de liberacion.
 * 
 * @return          Un nuevo TAD de lista en caso de exito, o NULL en caso de que cmpFn sea NULL.
 */
listADT newList(const CompareFn cmpFn, const FreeFn freeFn);

/**
 * @brief           Libera toda la memoria asociada a la lista.
 * @details         Se encarga tambien de liberar toda la memoria utilizada por los elemType, utilizando la funcion
 *                  de liberacion provista. Si la funcion provista es NULL, este paso no se realiza.
 */
void freeList(listADT l);

/**
 * @brief           Devuelve la cantidad de elementos de la lista
 */
size_t size(const listADT l);

/**
 * @brief           Indica si la lista esta vacia o no
 */
bool isEmpty(const listADT l);

// Insertar un elemento
listADT add(listADT l, elemType elem);

// Borrar un elemento
listADT delete(listADT l, elemType elem);

/**
 * @brief           Devuelve si un elemento pertenece o no a la lista
 * 
 * @param l         La lista
 * @param elem      El elemento a buscar, utilizando la funcion de comparacion
 */
bool belongs(const listADT l, elemType elem);

// Retorna el elemento en la posicion idx
// Precondicion idx < size(l) sino se arroja error
elemType get(const listADT l, size_t idx);

// Crea un arreglo con todos los elementos de la lista
// respetando el orden de aparición
elemType * toArray(const listADT l);

// A partir de un array, genera una lista con los mismos 
// elementos, en el mismo orden
listADT fromArray(const size_t dim, const elemType arr[dim]);

// Aplica una funcion a cada elemento de la lista
void map(listADT l, MapperFn f);

#endif //LIST_H
