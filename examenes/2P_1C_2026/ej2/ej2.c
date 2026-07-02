#include "ej2.h"
#include <stdlib.h>

/**
 * Definida en el test
 */
extern unsigned char randIntTest(unsigned char min, unsigned char max);

/**
 * Funcion de generacion de numeros aleatorios interna del TAD
 */
static unsigned char randInt(unsigned char min, unsigned char max) {
    return randIntTest(min, max);
}

struct randomCDT {
    size_t * occurrences;               // Vector de apariciones
    size_t distinctNumbers;             // Cantidad de numeros distintos insertados
    unsigned char mostFrequent;         // El mas frecuente
    unsigned char maxValue;
};

randomADT newRandomADT(unsigned char maxValue){
    if (maxValue == 0) {
        return NULL;
    }

    randomADT ret = malloc(sizeof(struct randomCDT));
    ret->occurrences = calloc(maxValue, sizeof(size_t));
    ret->distinctNumbers = 0;
    ret->mostFrequent = 1;
    ret->maxValue = maxValue;

    return ret;
}

void newRandoms(randomADT adt, size_t qty) {
    for (size_t i = 0; i < qty; i++) {
       newRandom(adt);
    }
}

void newRandom(randomADT adt) {
    /* Genero numero aleatorio */
    unsigned char n = randInt(1, adt->maxValue);

    /* Solo para la primera vez que se inserta un numero, establecer el mas frecuente como ese numero */
    if (adt->distinctNumbers == 0) {
        adt->mostFrequent = n;
    }

    /* Si no tenia apariciones, es un numero nuevo */
    if (adt->occurrences[n - 1] == 0) {
        (adt->distinctNumbers)++;
    }
    
    /* Le agrego una aparicion */
    (adt->occurrences[n - 1])++;

    /* Actualizo el mas frecuente */
    if (adt->occurrences[n - 1] > adt->occurrences[adt->mostFrequent - 1]) {
        adt->mostFrequent = n;
    }
}

unsigned char numbers(const randomADT adt){
    return adt->distinctNumbers;
}

int mostFrequent(const randomADT adt){
    return adt->distinctNumbers > 0 ? adt->mostFrequent : -1;
}
 
void freeRandomADT(randomADT adt){
    free(adt->occurrences);
    free(adt);
}
