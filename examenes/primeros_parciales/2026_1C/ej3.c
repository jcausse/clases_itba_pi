#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#define CANT_DIRECCIONES 8

typedef enum {
    NO_PIEZA = 0,
    BLANCA,
    NEGRA
} Color;

/**
 * @brief               Dada una posible pieza, me indica su color o NO_PIEZA si no es una pieza valida
 */
Color color(char pieza) {
    return pieza == ' ' ? NO_PIEZA : (islower(pieza) ? BLANCA : NEGRA);
}

/**
 * @brief               Dada una pieza, indicar si es una dama
 */
bool es_dama(char pieza) {
    return tolower(pieza) == 'd';
}

/**
 * @brief               Indica si una posicion es valida o no para el tablero
 */
bool es_posicion_valida(int fil, int col, unsigned int dim) {
    return fil >= 0 && fil < dim && col >= 0 && col < dim;
}

/**
 * @brief               Dada una dama en una posicion, y una direccion, verificar si la dama puede comer
 *                      alguna pieza moviendose en esa direccion
 * 
 * @param dim           Dimension del tablero
 * @param tablero       El tablero
 * @param color_dama    El color de la dama a verificar
 * @param posicion      Posicion [fil, col] donde esta la dama a verificar
 * @param direccion     Direccion en la cual moverse para verificar [delta fil, delta col]
 * 
 * @return              1 si puede comer, 0 en caso contrario
 */
int verificar_direccion (unsigned dim, const char tablero[dim][dim], Color color_dama, int posicion[2], const int direccion[2]) {
    int fil = posicion[0] + direccion[0];           // Arranco 1 lugar corrido para no verificar la posicion de la misma dama
    int col = posicion[1] + direccion[1];
    int puede_comer = 0;                            // Me indica si puede comer o no
    bool obstruido = false;                         // Me indica si una pieza del mismo color que la dama le tapa el camino
    Color color_pos_actual;

    // Condiciones para poder seguir verificando una direccion:
    // - No me vaya del tablero
    // - En la posicion actual no haya una pieza de mi mismo color (me tapa lo que esta atras)
    // - No haya ya podido comer una pieza (si ya puedo comer retorno inmediatamente)
    while (es_posicion_valida(fil, col, dim) && !obstruido && !puede_comer) {
        color_pos_actual = color(tablero[fil][col]);                                        // Determino el color de la casilla que estoy viendo
        puede_comer = color_pos_actual != NO_PIEZA && color_pos_actual != color_dama;       // Determino si es una pieza que puede comer
        obstruido = color_pos_actual == color_dama;

        fil += direccion[0];                                                                // Me muevo a la siguiente casilla en la misma direccion
        col += direccion[1];
    }

    return puede_comer;
}

/**
 * @brief               Dada una dama en una posicion, contar cuantas piezas puede comer esa dama
 * 
 * @param dim           Dimension del tablero
 * @param tablero       El tablero
 * @param posicion      Posicion [fil, col] donde esta la dama a verificar
 * 
 * @return              Cantidad de objetivos (piezas que puede comer) esa dama
 */
int cant_objetivos_dama(unsigned dim, const char tablero[dim][dim], int posicion[2]) {
    static const int DIRECCIONES[CANT_DIRECCIONES][2] = {
        {1, 0},                 // Abajo
        {1, 1},                 // Derecha - Abajo
        {0, 1},                 // Derecha
        {-1, 1},                // Derecha - Arriba
        {-1, 0},                // Arriba
        {-1, -1},               // Izquierda - Arriba
        {0, -1},                // Izquierda
        {1, -1},                // Izquierda - Abajo
    };
    int objetivos = 0;
    Color color_dama = color(tablero[posicion[0]][posicion[1]]);

    for (int i = 0; i < CANT_DIRECCIONES; i++) {
        objetivos += verificar_direccion(dim, tablero, color_dama, posicion, DIRECCIONES[i]);
    }

    return objetivos;
}

int damas(unsigned dim, const char tablero[dim][dim]) {
    int posibles_capturas = 0;
    int posicion[2];

    for (int fil = 0; fil < dim; fil++) {                           // Para cada posicion de la matriz
        for (int col = 0; col < dim; col++) {
            if (es_dama(tablero[fil][col])) {                       // Si en una posicion hay una dama

                // Sumo la cantidad de objetivos que tiene
                posicion[0] = fil;
                posicion[1] = col;
                posibles_capturas += cant_objetivos_dama(dim, tablero, posicion);         
            }
        }
    }

    return posibles_capturas;
}
 
void test_sin_damas() {
    char t[3][3] = { 
       {' ', ' ', 'a'}, 
       {' ', 'P', ' '}, 
       {' ', ' ', ' '} 
   }; 
   assert(damas(3,t) == 0); // No hay damas blancas ('d') ni negras ('D') 
} 
 
void test_captura() { 
   char t[3][3] = { 
       {'d', 'C', 'D'}, 
       {' ', ' ', ' '}, 
       {'A', 't', ' '} 
   }; // La dama blanca en [0][0] puede comer a [0][1] y [2][0] 
   assert(damas(3,t) == 2); 
} 
 
void test_bloqueo() { 
   char t[3][3] = { 
       {' ', 'p', ' '}, 
       {' ', 'd', ' '}, 
       {' ', 'P', ' '} 
   }; // La dama blanca en [1][1] puede comer a [2][1] 
   assert(damas(3,t) == 1); 
} 
 
void test_multiple_direcciones() { 
   char t[5][5] = { 
       {'A',' ',' ',' ','R'}, 
       {' ','P',' ','T',' '}, 
       {' ',' ','d',' ',' '}, 
       {' ','a',' ','t',' '}, 
       {'C',' ',' ',' ','A'} 
   }; // La dama blanca en [2][2] puede comer a [1][1] y [1][3] 
   assert(damas(5,t) == 2); 
} 
 
void test_varias_damas() { 
   char t[3][3] = { 
       {'D',' ','d'}, 
       {' ','p',' '}, 
       {'d',' ',' '} 
   }; 
   // La dama negra en [0][0] puede comer a [0][2], [1][1] y [2][0] 
   // La dama blanca en [0][2] puede comer a [0][0] 
   // La dama blanca en [2][0] puede comer a [0][0] 
   assert(damas(3,t) == 5); 
} 
 
int main(void) { 
   test_sin_damas(); 
   test_captura(); 
   test_bloqueo(); 
   test_multiple_direcciones(); 
   test_varias_damas(); 
   puts("OK!"); 
   return 0; 
}
