#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mostPopularADT.h"

int main(void) { 
    mostPopularADT tad = newMostPopular((CompareFn) strcmp); 
    assert(size(tad) == 0); // Al principio, está vacío 
    
    // Agregamos elementos 
    assert(add(tad, "perro") == 1); 
    assert(add(tad, "gato") == 1); 
    assert(add(tad, "loro") == 1); 
    assert(add(tad, "gato") == 0); // ya estaba 
    
    assert(size(tad) == 3);
    
    // Verificamos el orden: perro, gato, loro 
    const char * expected1[] = {"perro", "gato", "loro"}; 
    toBegin(tad); 
    for (int i = 0; i < 3; i++) { 
        assert(hasNext(tad)); 
        const char * elem = next(tad); 
        assert(strcmp(elem, expected1[i]) == 0); 
    } 
    assert(!hasNext(tad)); 
    
    // Consultamos "gato" → debe pasar al principio 
    int ok = exist(tad, "gato"); 
    assert(ok == 1); 
    
    // Verificamos nuevo orden: gato, perro, loro 
    const char * expected2[] = {"gato", "perro", "loro"}; 
    toBegin(tad); 
    for (int i = 0; i < 3; i++) { 
        assert(hasNext(tad)); 
        const char * elem = next(tad); 
        assert(strcmp(elem, expected2[i]) == 0); 
    }
    assert(!hasNext(tad)); 
 
    // consulta de uno que no está → 0 
    assert(exist(tad, "pez") == 0); 
    
    // Consultamos "loro" → pasa al principio 
    ok = exist(tad, "loro"); 
    assert(ok == 1); 
    
    // Nuevo orden: loro, gato, perro 
    const char * expected3[] = {"loro", "gato", "perro"}; 
    toBegin(tad); 
    for (int i = 0; i < 3; i++) { 
        assert(hasNext(tad)); 
        const char * elem = next(tad); 
        assert(strcmp(elem, expected3[i]) == 0); 
    } 
    assert(!hasNext(tad)); 
    
    freeMostPopular(tad); 
    puts("OK"); 
    return 0; 
}
