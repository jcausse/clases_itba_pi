#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ej1.h"

int main(void){ 
   libraryADT lb = newLibrary(); 
   // Sucursal 15 es inválida 
   assert(addBook(lb, 15, "Moby Dick english edition", 8)==0); 
 
   assert(addBook(lb, 20, "Moby Dick english edition", 8)==8); 
   assert(addBook(lb, 20, "Moby Dick english edition", 7)==15); 
 
   assert(addBook(lb, 30, "Moby Dick english edition", 18)==18); 
 
   assert(addBook(lb, 20, "Moby Dick ilustrado", 8)==8); 
 
   char aux[100]; 
   strcpy(aux, "Ficciones, Borges"); 
   assert(addBook(lb, 20, aux, 10)==10); 
   strcpy(aux, "1984"); 
   assert(addBook(lb, 20, aux, 1)==1); 
   strcpy(aux, "MOBY DICK english edition"); 
   assert(addBook(lb, 20, aux, 10)==25); // Había 15, se suman 10 
 
   assert(books(lb, 20)==4); 
   assert(stock(lb, 20)==44); 
 
   assert(books(lb, 30)==1); 
   assert(stock(lb, 30)==18); 
 
   assert(books(lb, 40)==0); 
   assert(stock(lb, 40)==0);

   toBeginByBranch(lb, 20); 
   struct bookData book; 
   book = next(lb, 20); 
   assert(book.stock == 1); 
   assert(strcmp(book.title, "1984")==0); 
   free(book.title); 
   book = next(lb, 20); 
   assert(book.stock == 10); 
   assert(strcmp(book.title, "Ficciones, Borges")==0); 
   free(book.title); 
   
   toBeginByBranch(lb, 30); 
 
   book = next(lb, 20); 
   assert(book.stock == 25); 
   assert(strcmp(book.title, "Moby Dick english edition")==0); 
   free(book.title); 
   book = next(lb, 20); 
   assert(book.stock == 8); 
   assert(strcmp(book.title, "Moby Dick ilustrado")==0); 
   free(book.title); 
 
   assert(hasNext(lb, 20)==0); 
   assert(hasNext(lb, 30)==1); 
 
   freeLibrary(lb); 
   puts("OK"); 
   return 0; 
}
