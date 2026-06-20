#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "rankingADT.h"

// Utilizamos const char * como elemType y strcmp como compare

int main(void) {
  rankingADT r = newRanking(NULL, 0, strcmp);
  addRanking(r, "Footloose");
  addRanking(r, "Footloose");  // no hace nada
  addRanking(r, "Footloose");  // no hace nada
  addRanking(r, "Yesterday");
  addRanking(r, "La bamba");
  addRanking(r, "Sucio y desprolijo");
  addRanking(r, "Ride of the Valkyries");
  addRanking(r, "Yesterday");
  addRanking(r, "Ride of the Valkyries");

  const char * aux = "default";
  int n;
  n = getByRanking(r, 6, &aux);
  assert( n == 0 && !strcmp(aux, "default") );

  n = getByRanking(r, 1, &aux); 
  assert( n == 1 && !strcmp(aux, "Yesterday") );

  n = getByRanking(r, 0, &aux); 
  assert( n == 0 && !strcmp(aux, "Yesterday") );

  n = getByRanking(r, 2, &aux); 
  assert( n == 1 && !strcmp(aux, "Footloose") );

  n = getByRanking(r, 1, &aux); 
  assert( n == 1 && !strcmp(aux, "Footloose") );
 
  assert( contains(r, "Ride of the Valkyries") ); 
  assert( contains(r, "Sucio y desprolijo") ); 
  assert( contains(r, "Desarma y sangra") == 0 );

  size_t dimTop = 10;
  char ** top = getTopRanking(r, &dimTop);
  assert(dimTop == 5 && !strcmp(top[0], "Footloose") && !strcmp(top[1], "Yesterday"));
  assert(!strcmp(top[2], "Ride of the Valkyries") && !strcmp(top[3], "Sucio y desprolijo"));
  assert(strcmp(top[4], "La bamba") == 0);
  free(top);

  downByRanking(r, 1);
  dimTop = 2;
  top = getTopRanking(r, &dimTop);
  assert( dimTop == 2 && !strcmp(top[0], "Yesterday") && !strcmp(top[1], "Footloose") );

  free(top);
  freeRanking(r);
  
  // Creamos un ranking con miles de elementos
  int qty = 5000;
  char * songs[qty];
  
  for(int i=0; i<qty; i++) {
	  songs[i] = malloc(100);
	  sprintf(songs[i], "Cancion %04d", i+1);
  }
  r = newRanking(songs, qty, strcmp);  
  assert(size(r)==qty);
  
  assert(position(r, "Cancion 0001")==1);
  assert(position(r, "Cancion 4500")==4500);
  
  assert( contains(r, "Cancion 0001") ); 
  assert(position(r, "Cancion 0001")==1);
  assert( contains(r, "Cancion 1234") ); 
  assert(position(r, "Cancion 1234")==1233);
  assert(position(r, "Cancion 1233")==1234);
  assert(position(r, "Cancion 5000")==5000);
  assert(position(r, "Cancion xxx")==0);
  assert(size(r)==qty);
  
  
  for(int i=0; i<qty; i++) {
	  free(songs[i]);
  }
  freeRanking(r);
  
  puts("rankingADT: OK!");
  return 0;
}
