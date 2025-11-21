#include "rankingADT.h"

#define BLOCK 5

struct rankingCDT {
    elemType * ranking;             // Vector de elementos del ranking
    size_t size;                    // Cantidad de elementos usados
    compare cmp;                    // Funcion de comparacion de elementos
};

/*
dim -> cantidad de bloques
0 -> 0
1 -> 1
2 -> 1
3 -> 1
4 -> 1
5 -> 1
6 -> 2
10 -> 2
11 -> 3

dim / BLOCK + (dim % BLOCK > 0)  // Me da la cantidad inicial de bloques a reservar
*/

/**
 * @brief       Sube el n-esimo elemento 1 lugar en el ranking.
 * @details     Si el el elemento es el tope del ranking, queda donde esta. Intercambia el elemento con su inmediato superior
 * 
 * @param ranking   El TAD del ranking en si
 * @param n         El indice del elemento a subir en el ranking. CUIDADO: Empiezan en 1.
 */
static void upByRanking(rankingADT ranking, size_t n) {
    if (n > 1) {   // Si n es 1, no hago nada. Si es 0 (posicion invalida), tampoco hago nada
        elemType aux = ranking->ranking[n - 1];                 // Elemento que quiero subir es el n - 1 
        ranking->ranking[n - 1] = ranking->ranking[n - 2];      // Su inmediato superior es el n - 2
        ranking->ranking[n - 2] = aux;
    }
}

rankingADT newRanking(elemType elems[], size_t dim, compare cmp) {
    rankingADT aux = calloc(1, sizeof(struct rankingCDT));
    aux->cmp = cmp;

    size_t block_qty = dim / BLOCK + (dim % BLOCK > 0);                 // Cantidad de bloques iniciales a reservar
    if (block_qty > 0) {                                                // Si la cantidad de bloques es mayor que cero, inicializo
        aux->ranking = malloc(block_qty * BLOCK * sizeof(elemType));    // Creo el arreglo dinamico con la cantidad de BLOQUES justa
        aux->size = dim;                                                // Guardo los elementos usados
        for (size_t i = 0; i < dim; i++) {                              // Inicializo el array
            aux->ranking[i] = elems[i];
        }
    }                                                                   // Caso contrario, ranking queda en NULL y size en 0

    return aux;
}

void addRanking(rankingADT ranking, elemType elem) {
    int pos = position(ranking, elem);                  // Consulto la posicion del elemento, para saber si estaba
    
    // Caso 1: Si no esta, lo agrego
    if (pos == 0){
        if (ranking->size % BLOCK == 0) {               // Si necesito, extiendo
            ranking->ranking = realloc(ranking->ranking, (ranking->size + BLOCK) * sizeof(elemType));
        }
        ranking->ranking[ranking->size] = elem;         // Lo agrego al final
        (ranking->size)++;                              // Incremento el size
    }

    // Caso 2: Si ya estaba, sube un puesto
    else {
        upByRanking(ranking, pos);
    }
}

size_t size(const rankingADT ranking) {
    return ranking->size;
}

int getByRanking(rankingADT ranking, size_t n, elemType * elem) {
    if (n == 0 || n > ranking->size) {
        return 0;
    }
    *elem = ranking->ranking[n - 1];                    // Obtengo el elemento para retornarlo (ANTES DE SUBIRLO)
    upByRanking(ranking, n);                            // Lo subo una posicion
    return 1;
}

elemType * getTopRanking(const rankingADT ranking, size_t * top) {
    if (ranking->size == 0 || *top == 0) {
        *top = 0;
        return NULL;
    }

    size_t elems_to_return = *top < ranking->size ? *top : ranking->size;   // Minimo entre *top y ranking->size
    elemType * aux = malloc(elems_to_return * sizeof(elemType));            // Creo el array en HEAP
    for (size_t i = 0; i < elems_to_return; i++) {                          // Lo lleno con los primeros elems_to_return elementos
        aux[i] = ranking->ranking[i];
    }
    *top = elems_to_return;                                                 // Guardo la cantidad que devuelvo
    return aux;
}

int contains(rankingADT ranking, elemType elem) {
    int pos = position(ranking, elem);                  // Consulto la posicion del elemento
    if (pos == 0) {                                     // Si el elemento no esta, devuelvo 0                            
        return 0;
    }
    upByRanking(ranking, pos);                          // Pos es una posicion que arranca en 1
    return 1;
}

void downByRanking(rankingADT ranking, size_t n) {
    if (n == 0 || n >= ranking->size) {     // Si n es 0 o mayor que ranking->size, es invalido
        return;                             // Si n es igual que ranking->size, es el ultimo elemento, y no lo puedo bajar
    }
    upByRanking(ranking, n + 1);            // Puedo bajar en el ranking el elemento n haciendo que suba el n + 1
}

void freeRanking(rankingADT r) {
    free(r->ranking);
    free(r);
}

int position(const rankingADT r, elemType elem) {
    for (size_t i = 0; i < r->size; i++) {                  // Busco el elemento
        if (r->cmp(r->ranking[i], elem) == 0) {             // Usando la funcion comparadora
            return i + 1;                                   // Si lo encuentro devuelvo su posicion (numerada desde 1)
        }
    }
    return 0;                                               // Si no esta en el ranking, devuelvo 0
}
