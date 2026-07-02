#ifndef EJ1_H
#define EJ1_H

#include <stddef.h>

typedef struct libraryCDT * libraryADT; 
 
struct bookData { 
   char * title; 
   size_t stock; 
}; 
 
libraryADT newLibrary(void); 
 
void freeLibrary(libraryADT lib);
 
/** 
* Agrega -si no estaba- un nuevo libro a una sucursal. 
* Si ya existe ese título, incrementa el stock actual 
* El parámetro stock indica cuántos ejemplares se agregan de ese libro. 
* Si la sucursal es inválida retorna cero, si no retorna el stock actual  
* de ese libro 
*/ 
size_t addBook(libraryADT lib, size_t branch, const char * title, unsigned int stock);

/** 
* Retorna la cantidad de libros distintos que hay en una sucursal. 
* Si la sucursal es inválida retorna cero. 
*/ 
size_t books(const libraryADT lib, size_t branch); 
 
/** 
* Retorna la cantidad total de ejemplares disponibles en una sucursal. 
* Si la sucursal es inválida retorna cero. 
*/ 
size_t stock(const libraryADT lib, size_t branch); 
 
// Funciones para iterar por sucursal, alfabéticamente por título  
// Permite iterar en forma paralela por varias sucursales (ver test) 
void toBeginByBranch(libraryADT lib, size_t branch); 
 
/* 1 si hay siguiente libro para una sucursal, 0 si no */ 
int hasNext(const libraryADT lib, size_t branch); 
 
struct bookData next(libraryADT lib, size_t branch);

#endif // EJ1_H
