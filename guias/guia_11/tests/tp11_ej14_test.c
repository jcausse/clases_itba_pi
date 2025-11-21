#include "tp11_ej14.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int compare (elemType e1, elemType e2) {
    return e1-e2;
}

#define STRESS_SIZE 10000    /* cantidad de elementos para la prueba masiva */

int
main(void) {
	
	/* ---------- tests básicos ---------- */
   listADT c = newList(compare); // una lista, en este caso de int
   toBegin(c);
   assert(!hasNext(c));
   assert(!hasNextAsc(c));
   add(c, 3);   add(c, 1);   add(c, 5);   add(c, 2);
   toBegin(c);         // iterador por orden de insercion
   int n = next(c);    // n = 3
   assert(n==3);
   n = next(c);        // n = 1
   assert(n==1);
  
   toBeginAsc(c);      // iterador por orden ascendente

   assert(hasNext(c));
   assert(hasNextAsc(c));

   n = nextAsc(c);     // n = 1
   assert(n==1);

   n = next(c);        // n = 5
   assert(n==5);

   n = next(c);        // n = 2
   assert(n==2);
   assert(!hasNext(c)); 

   n = nextAsc(c);     // n = 2
   assert(n==2);

   n = nextAsc(c);     // n = 3
   assert(n==3);

   n = nextAsc(c);     // n = 5
   assert(n==5);

   assert(! hasNextAsc(c));

   freeList(c);
   
   /* ---------- stress tests ---------- */
   listADT stress = newList(compare);

   /* insertamos 10 000 elementos en orden descendente (9999 … 0) */
   for (int i = STRESS_SIZE - 1; i >= 0; i--) {
       add(stress, i);
   }

   /* 1) Verificar orden de inserción (de 9999 a 0) */
   toBegin(stress);
   for (int i = STRESS_SIZE - 1; i >= 0; i--) {
       assert(hasNext(stress));
       assert(next(stress) == i);
   }
   assert(!hasNext(stress));

   /* 2) Verificar orden ascendente (de 0 a 9999) */
   toBeginAsc(stress);
   for (int i = 0; i < STRESS_SIZE; i++) {
       assert(hasNextAsc(stress));
       elemType v = nextAsc(stress);
       assert(v == i);
   }
   assert(!hasNextAsc(stress));

   freeList(stress);

   puts("OK!");

   return 0;
}