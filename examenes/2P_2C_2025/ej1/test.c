#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "socialADT.h"

int main(void) { 
    socialADT social = newSocial(); 
    assert(addInfluencer(social, "Nerd123", 999) == 0); 
    assert(addInfluencer(social, "Marito", 3100) == 1); 
    assert(addInfluencer(social, "Cuzco", 3100) == 1); 
    char aux[20] = "Pachi"; 
    assert(addInfluencer(social, aux, 21100) == 1); 
    strcpy(aux, "Luli"); 
    assert(addInfluencer(social, aux, 3001) == 1); 
    size_t dim; 
    influencerData * v = influencers(social, 3, &dim); 
    assert(dim == 3); 
    assert(v[0].followers == 3001); // es Luli 
    assert(v[1].followers == 3100); // es Cuzco o Marito 
    assert(v[2].followers == 3100); // es Marito o Cuzco 
    for(int i=0; i< dim; i++) { 
        free(v[i].id); 
    } 
    free(v); 
    freeSocial(social); 
    puts("OK!"); 
    return 0; 
}
