#include <stdio.h>
#include <assert.h>
#include "busADT.h"

int compareInt(int a, int b) {
    return a - b;
}

int main(void) { 
    busADT buses = newBusADT(compareInt); 

    assert(busSize(buses)==0); 
    int aux; 
    assert(busInfo(buses, 104, &aux)==0); 

    busSet(buses, 104, 1040); // A la línea 140 se le asocia el entero 1040 
    busSetIfAbsent(buses, 104, 500); // No hace nada porque la línea 140 ya tiene info 

    assert(busInfo(buses, 104, &aux)==1); 
    assert(aux==1040); 
    assert(busSize(buses)==1); 

    busSetIfAbsent(buses, 29, 10); // Lo agrega pues no había línea 29 
    assert(busSize(buses)==2); 
    assert(busInfo(buses, 103, &aux)==0); 
    assert(busInfo(buses, 28, &aux)==0); 

    freeBusADT(buses); 
    puts("OK"); 
    return 0; 
}
