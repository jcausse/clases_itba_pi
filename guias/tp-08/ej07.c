#include <stdio.h>
#include <stdlib.h>

#define BLOQUE 5
#define DIRECCIONES 8

#define ES_POSICION_VALIDA(fils, cols, i, j) ((i) >= 0 && (i) < (fils) && (j) >= 0 && (j) < (cols))

typedef enum {DER=0, IZQ, ABA, ARR, I_AR, I_AB, D_AR, D_AB } Tdireccion; 
 
struct posicion { 
    char * palabra; 
    size_t fila; 
    size_t columna;
    Tdireccion direccion;
};

typedef struct {
    size_t i;
    size_t j;
} Coordenada;

typedef struct {
    struct posicion * arr;
    size_t write;
} ArrayPosiciones;

/**
 * @brief   Busca una palabra determinada en una direccion determinada partiendo de una posicion determinada.
 * @details NO verifica la posicion inicial (se asume ya verificada)
 * @return  true o false segun la palabra coincide o no
 */
bool buscar_en_direccion (size_t fils, size_t cols, const char mat[fils][cols], char * palabra, Coordenada inicio, int deltaI, int deltaJ) {
    if (palabra[0] == '\0') {
        return false;
    }
    
    int i = (int) inicio.i + deltaI;
    int j = (int) inicio.j + deltaJ;
    size_t k = 1;

    while (ES_POSICION_VALIDA(fils, cols, i, j) && palabra[k] == mat[i][j]) {
        i += deltaI;
        j += deltaJ;
        k++;
    }
    return palabra[k] == '\0';
}

void buscar_en_posicion(size_t fils, size_t cols, const char mat[fils][cols], char * palabra, Coordenada inicio, ArrayPosiciones * ret) {
    static const int DELTAS[DIRECCIONES][2] = {
        {0, 1},     // DER
        {0, -1},    // IZQ 
        {1, 0},     // ABA
        {-1, 0},    // ARR
        {-1, -1},   // I_AR
        {1, -1},    // I_AB
        {-1, 1},    // D_AR
        {1, 1}      // D_AB
    };

    if (palabra[0] != mat[inicio.i][inicio.j]) {
        return;
    }
    
    for (size_t dir = 0; dir < DIRECCIONES; dir++) {
        if (buscar_en_direccion(fils, cols, mat, palabra, inicio, DELTAS[dir][0], DELTAS[dir][1])) {
            if (ret->write % BLOQUE == 0) {
                ret->arr = realloc(ret->arr, (ret->write + BLOQUE) * sizeof(struct posicion));
            }
            ret->arr[ret->write].palabra = palabra;
            ret->arr[ret->write].fila = inicio.i;
            ret->arr[ret->write].columna = inicio.j;
            ret->arr[ret->write].direccion = dir;
            ret->write++;
        }
    }
}

void buscar_en_matriz(size_t fils, size_t cols, const char mat[fils][cols], char * palabra, ArrayPosiciones * ret) {
    Coordenada inicio;
    for (size_t i = 0; i < fils; i++) {
        for (size_t j = 0; j < cols; j++) {
            inicio.i = i;
            inicio.j = j;
            buscar_en_posicion(fils, cols, mat, palabra, inicio, ret);            
        }
    }
}

struct posicion * resolverSopa(size_t fils, size_t cols, const char mat[fils][cols], char * diccionario[]) {
    ArrayPosiciones ret = {
        .arr = NULL,
        .write = 0
    };

    size_t i = 0;
    while (diccionario[i][0] != '\0') {
        buscar_en_matriz(fils, cols, mat, diccionario[i], &ret);
        i++;
    }

    // Redimensionar el array al tamaño necesario (write posiciones escritas
    // + 1 para el terminador)
    ret.arr = realloc(ret.arr, (ret.write + 1) * sizeof(struct posicion));

    // Asignar el terminador
    ret.arr[ret.write].palabra = NULL;

    return ret.arr;
}

const char * convertir_direccion(size_t i) {
    static const char * arr[] = {"DER", "IZQ", "ABA", "ARR", "I_AR", "I_AB", "D_AR", "D_AB"};
    return arr[i]; 
}

int main(void) {
    char * diccionario[] = {"ARRE", "CANCION", "CAPA", "ERROR", "ORCO", "PERRO", "PERTINAZ", "REA", "RIO", ""};

    char sopa[6][7] = { 
        {'X', 'X', 'X', 'O', 'X', 'X', 'X'}, 
        {'A', 'P', 'A', 'C', 'Y', 'Y', 'O'}, 
        {'Z', 'E', 'Z', 'R', 'Z', 'C', 'X'}, 
        {'E', 'R', 'R', 'O', 'R', 'X', 'X'}, 
        {'X', 'R', 'I', 'O', 'I', 'E', 'X'},
        {'X', 'O', 'X', 'X', 'O', 'X', 'X'}
    };

    size_t i = 0;
    struct posicion * ret = resolverSopa(6, 7, sopa, diccionario);

    while (ret[i].palabra != NULL) {
        printf("%s - (%lu, %lu) [%s]\n", ret[i].palabra, ret[i].fila, ret[i].columna, convertir_direccion(ret[i].direccion));
        i++;
    }

    free(ret);
}
