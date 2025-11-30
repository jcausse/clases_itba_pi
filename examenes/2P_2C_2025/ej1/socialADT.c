#include "socialADT.h"

#include <stdlib.h>
#include <string.h>

typedef struct Influencer {
    influencerData data;
    struct Influencer * next;
} Influencer;

typedef struct {
    Influencer * first;
    size_t size;
} InfluencerBucket;

struct socialCDT {
    InfluencerBucket * buckets;     // 0: 1000 a 1999 seguidores, 1: 2000 a 2999 seguidores, 2: 3000 a 3999 seguidores, ...
    size_t size;
};

socialADT newSocial(void) {
    return calloc(1, sizeof(struct socialCDT));
}

static void freeList(Influencer * l) {
    if (l == NULL) {
        return;
    }
    freeList(l->next);
    free(l->data.id);
    free(l);
}

void freeSocial(socialADT social) {
    // Libero todas las listas
    for (size_t i = 0; i < social->size; i++) {
        freeList(social->buckets[i].first);
    }

    // Libero los buckets
    free(social->buckets);

    // Libero el ADT
    free(social);
}

static Influencer * addToList(Influencer * l, Influencer * toAdd) {
    // Si tienen misma cantidad de seguidores, respeto el orden de insercion
    if (l == NULL || l->data.followers > toAdd->data.followers) {
        toAdd->next = l;
        return toAdd;
    }

    l->next = addToList(l->next, toAdd);
    return l;
}
 
int addInfluencer(socialADT social, const char * id, size_t followers) {
    // Chequeo de precondiciones: No puedo agregar influencers sin nombre, ni con menos de 1000 followers
    if (id == NULL || followers < MIN_FOLLOWERS) {
        return 0;
    }

    // Calculo en que bucket cae este influencer segun su cantidad de seguidores
    size_t bucket = followers / MIN_FOLLOWERS - 1;

    // Chequeo si debo extender el array dinamico
    if (bucket >= social->size) {
        social->buckets = realloc(social->buckets, (bucket + 1) * sizeof(InfluencerBucket));
        for (size_t i = social->size; i <= bucket; i++) {
            social->buckets[i].first = NULL;
            social->buckets[i].size = 0;
        }
        social->size = bucket + 1;
    }

    // Creamos el influencer a agregar
    Influencer * newInfluencer = malloc(sizeof(Influencer));
    newInfluencer->data.id = strdup(id);
    newInfluencer->data.followers = followers;
    newInfluencer->next = NULL;

    // Agrego el influencer al bucket que corresponde
    social->buckets[bucket].first = addToList(social->buckets[bucket].first, newInfluencer);
    (social->buckets[bucket].size)++;

    return 1;
}

int addFollowers(socialADT social, const char * id, size_t newFollowers) {
    return 0;   // NO IMPLEMENTADA PORQUE NO SE PIDE
}
 
influencerData * influencers(const socialADT social, size_t n, size_t * dim) {
    // Chequeo de precondiciones
    if (dim == NULL) {
        return NULL;
    }
    if (n == 0) {
        *dim = 0;
        return NULL;
    }

    // Convierto n a un indice valido del arreglo
    n--;

    // Obtengo el tamaño del array que voy a devolver
    size_t toReturnSize = social->buckets[n].size;

    // Crear el arreglo que voy a devolver
    influencerData * toReturn = malloc(toReturnSize * sizeof(influencerData));

    // Inicializo el array
    Influencer * current = social->buckets[n].first;
    for (size_t i = 0; i < toReturnSize; i++) {
        toReturn[i].id = strdup(current->data.id);
        toReturn[i].followers = current->data.followers;
        
        current = current->next;
    }

    // Devuelvo el array
    *dim = toReturnSize;
    return toReturn;
}
