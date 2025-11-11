#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "busDriverADT.h"

int main(void) { 
   busDriverADT adt = newBusDriverADT(); 
   assert(busLinesCount(adt) == 0); // Inicialmente no hay líneas 
 
   // Agregamos líneas nuevas 
   assert(newBusLine(adt, 60) == 1); 
   assert(newBusLine(adt, 168) == 1); 
   assert(newBusLine(adt, 60) == 0); // ya estaba 
 
   assert(busLinesCount(adt) == 2); 
   assert(driversCount(adt, 60) == 0); 
   assert(driversCount(adt, 999) == 0); // línea inexistente 
   assert(driversCount(adt, 19) == 0);  // línea inexistente 
 
   // Agregamos choferes a la línea 60: Carlos, Ana y Bruno 
   addDriver(adt, 60, "Carlos"); 
   char auxName[20] = "Ana";  
   addDriver(adt, 60, auxName); 
   strcpy(auxName, "Bruno"); 
   addDriver(adt, 60, auxName); 
   addDriver(adt, 60, "Ana"); // repetido, no se agrega
   addDriver(adt, 60, "BRUNO"); // repetido, no se agrega
   addDriver(adt, 60, "carlos"); // repetido, no se agrega 
 
   assert(driversCount(adt, 60) == 3); 
 
   // Agregamos chofer a otra línea 
   addDriver(adt, 168, "Diana"); 
   assert(driversCount(adt, 168) == 1); 
 
   // No debería hacer nada si la línea no existe 
   addDriver(adt, 9, "Pedro"); 
   assert(driversCount(adt, 9) == 0); 
 
   // Verificamos orden alfabético de choferes línea 60: Ana, Bruno, Carlos 
   assert(driversCount(adt, 60) == 3); 
   char ** names = drivers(adt, 60); 
   assert(names != NULL); 
   assert(strcmp(names[0], "Ana") == 0); 
   assert(strcmp(names[1], "Bruno") == 0); 
   assert(strcmp(names[2], "Carlos") == 0); 
   free(names[0]); free(names[1]); free(names[2]); 
   free(names);

   // Verificamos choferes de línea inexistente 
   assert(drivers(adt, 1234) == NULL); 
   assert(drivers(adt, 15) == NULL); 
 
   // Quitamos un chofer de la línea 60 
   removeDriver(adt, 60, "Bruno"); 
   assert(driversCount(adt, 60) == 2); 
 
   // Intentamos quitar chofer inexistente o en línea inexistente 
   removeDriver(adt, 60, "Juan");  // no está 
   removeDriver(adt, 99, "Ana");  // línea no existe 
 
   // Verificamos choferes actuales en 60: Ana, Carlos 
   names = drivers(adt, 60); 
   assert(names != NULL); 
   assert(strcmp(names[0], "Ana") == 0); 
   assert(strcmp(names[1], "Carlos") == 0); 
   free(names[0]); free(names[1]); 
   free(names); 
 
   freeBusDriverADT(adt); 
   puts("OK"); 
   return 0; 
}
