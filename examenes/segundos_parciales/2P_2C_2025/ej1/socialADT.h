#ifndef _SOCIAL_ADT_H_
#define _SOCIAL_ADT_H_

#include <stddef.h>

#define MIN_FOLLOWERS 1000  // Cantidad minima de seguidores que tiene cada influencer del TAD

typedef struct socialCDT * socialADT; 
 
typedef struct influencerData { 
   char * id; 
   size_t followers; 
} influencerData; 
 
socialADT newSocial(void);
 
void freeSocial(socialADT social);
 
/** 
* Agrega un influencer 
* id: identifica al influencer 
* followers: cantidad de seguidores 
* El influencer no debería existir, pero eso el TAD no lo valida. Si ya existe lo 
* vuelve a agregar 
* Si followers es menor a 1000, no lo agrega 
*/ 
int addInfluencer(socialADT social, const char * id, size_t followers); 
 
/** 
* Le agrega una cantidad de seguidores al influencer. Si no existe retorna cero 
*/ 
int addFollowers(socialADT social, const char * id, size_t newFollowers);
 
/** 
* Retorna un vector con los influencers que tienen "n miles" de seguidores 
* Por ejemplo si n es 1 los que tienen entre 1000 y 1999 seguidores 
* si n es 11, los que tienen entre 11000 y 11999 seguidores
* si n es 0 o no hay influencers en ese rango, retorna NULL y asigna cero a *dim  
* En cada posición del vector deja una copia del id y la cantidad de seguidores 
* El vector debe estar ordenado en forma ascendente por cantidad de seguidores 
* Si dos o más influencers tienen la misma cantidad de seguidores no es necesario 
* desempatar por otro criterio 
*/ 
influencerData * influencers(const socialADT social, size_t n, size_t * dim);

#endif // _SOCIAL_ADT_H_
