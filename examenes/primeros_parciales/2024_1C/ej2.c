#include <stdio.h>
#include <assert.h>

#define QUEEN '1'
#define DIRECTION_COUNT 4

bool checkDirection(int dim, const char board[dim][dim], 
                    int start_i, int start_j, 
                    int delta_i, int delta_j
) { 
    // No chequeo la posicion (start_i, start_j) porque ahi esta la dama actual, y no tiene sentido
    int current_i = start_i + delta_i;      // Posicion actual i: Pos. dama actual en i, corrido delta i
    int current_j = start_j + delta_j;      // Posicion actual j: Pos. dama actual en j, corrido delta j

    // Mientas no me salga de los limites del tablero
    while (0 <= current_i && current_i < dim && 0 <= current_j && current_j < dim) {
        if (board[current_i][current_j] == QUEEN) {     // Si encuentro una dama, posicion invalida
            return false;
        }
        current_i += delta_i;                           // Sino, avanzo un delta en i y en j y sigo
        current_j += delta_j;
    }

    return true;                                        // Si llego a los limites y no habia dama,
}                                                       // la posicion es valida

/**
 * @brief   Verifica que una posicion del tablero de nQueens sea valido.
 * @details Una posicion es valida cuando, suponiendo que en dicha posicion hay una reina, la misma
 *          no amenaza a ninguna otra reina para las direcciones consideradas.
 */
bool checkPosition(unsigned int dim, const char board[dim][dim], unsigned int i, unsigned int j) {
    static int DIRECTIONS[DIRECTION_COUNT][2] = {{0, 1}, {1, 1}, {1, 0}, {-1, 1}};

    // Para cada direccion (las otras 4 que faltan no hacen falta porque si hubiera una dama
    // en alguna de esas direcciones, la otra dama ya hubiera encontrado antes a la actual)
    for (unsigned int dir = 0; dir < DIRECTION_COUNT; dir++) {

        // Si hay una dama en esa direccion, posicion invalida
        if (!checkDirection(dim, board, i, j, DIRECTIONS[dir][0], DIRECTIONS[dir][1])) {
            return false;
        }
    }

    // Si recorri las 4 direcciones y no habia otras damas, posicion valida
    return true;
}

int nQueens(unsigned int dim, const char board[dim][dim]) {
    unsigned int queen_count = 0;                           // Contar cuantas reinas me encuentro
    for (unsigned int i = 0; i < dim; i++) {                
        for (unsigned int j = 0; j < dim; j++) {            // Para cada casillero
            if (board[i][j] == QUEEN) {                     // Si es una reina
                queen_count++;                              // Anoto +1 reina
                if (!checkPosition(dim, board, i, j)) {     // Verifico la posicion de la reina (si
                    return 0;                               // amenaza a otra)
                }
            }
        }
    }
    return queen_count == dim;                              // Para retornar 1, debe haber tantas reinas
}                                                           // como dimension de la matriz

int main(void) {
    char board[][8] = {
        {'0', '0', '0', '0', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '1', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '1', '0'},
        {'1', '0', '0', '0', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '1'},
    };
    // por ejemplo, hay tres reinas en la columna 4 y dos en la fila 6
    assert(nQueens(8, board) == 0);
    
    char board2[][6] = {
        {'0', '0', '0', '1', '0', '0'},
        {'1', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0'},
        {'0', '1', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '1'},
        {'0', '0', '1', '0', '0', '0'}
    };
    // Hay 6 reinas y no se atacan, retorna true
    assert(nQueens(6, board2));
    
    char board3[][6] = {
        {'0', '0', '1', '0', '0', '0'},
        {'1', '0', '0', '0', '0', '0'},
        {'0', '1', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0'},
        {'0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '1'}
    };
    // Las reinas en (1,0) y (2,1) se amenazan en forma diagonal
    assert(nQueens(6, board3) == 0);
    
    char board4[][6] = {
        {'0', '0', '0', '1', '0', '0'},
        {'0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0'},
        {'0', '1', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '1'},
        {'0', '0', '1', '0', '0', '0'}
    };
    // No se amenazan pero hay menos de 6 reinas
    assert(nQueens(6, board4) == 0);
    
    // No hay solución para tableros de dimensión 2 o 3
    assert(nQueens(3, board2) == 0);
    assert(nQueens(2, board2) == 0);
    
    // En un tablero de 1x1 debe haber una reina
    char board1[][1] = {{'1'}};
    assert(nQueens(1, board1));
    
    puts("OK!");
    
    return 0;
}
