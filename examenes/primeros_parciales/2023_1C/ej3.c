#include <stdio.h>
#include <assert.h>

#define FILS 6
#define COLS 5

// Cantidad de letras mayusculas
#define LETTERS 26

#define ACIERTO 'V'
#define EQUIVOCADA 'A'
#define ERRONEA 'G'

#define NO_WIN -1

/**
 * @brief   Procesa una fila de la matriz de intentos. Deja en la matriz de salida 'G', 'A' o 'V' segun corresponda.
 * 
 * @warning Asumo que todas las letras en la palabra y en el intento son mayusculas.
 * 
 * @param palabra   Palabra secreta.
 * @param intento   Un intento de adivinar la palabra, que proviene de la matriz de intentos original.
 * @param salida    Una fila de la matriz de salida para modificarla y llenarla con 'G', 'A' o 'V' segun corresponda.
 * 
 * @return  Retorna true si todas las posiciones de la fila procesada estan en verde.
 */
bool wordle_fila (const char palabra[COLS], const char intento[COLS], char salida[COLS]) {
  
    // Cargar apariciones de las letras de la palabra
    char apariciones[LETTERS] = {0};
    for (unsigned int i = 0; i < COLS; i++) {
        apariciones[palabra[i] - 'A']++;
    }

    bool todos_aciertos = true;

    // Lleno la matriz de salida
    for (unsigned int i = 0; i < COLS; i++) {

        // Si en el intento hay la misma letra que la palabra, es un acierto
        if (intento[i] == palabra[i]) {
            salida[i] = ACIERTO;
        }

        // En caso de no acertar
        else {
            todos_aciertos = false;

            // Si no es la misma letra, pero la letra esta en la palabra, es posicion equivocada
            if (apariciones[intento[i] - 'A'] > 0) {
                salida[i] = EQUIVOCADA;
            }

            // Si la letra no coincide (no acierta) ni esta en la palabra (no es equivocada), es erronea
            else {
                salida[i] = ERRONEA;
            }
        }   
    }

    return todos_aciertos;
}

int wordle(const char palabra[COLS], const char intentos[FILS][COLS], const unsigned int cant, char salida[FILS][COLS]) {
    int ret = NO_WIN;

    for (unsigned int i = 0; i < cant; i++) {
        if (wordle_fila(palabra, intentos[i], salida[i]) && ret == NO_WIN) {
            ret = (int) i + 1;
        }
    }

    return ret;
}

bool check_mat(const unsigned int fils, const unsigned int cols, const char m1[fils][cols], const char m2[fils][cols]) {
    for (unsigned int i = 0; i < fils; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            if (m1[i][j] != m2[i][j]) {
                printf("Expected %c but got %c at (%d, %d)\n", m1[i][j], m2[i][j], i, j);
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    char * palabra = "ROSAS";

    char intentos[FILS][COLS] = {
        {'F', 'A', 'R', 'O', 'L'},
        {'S', 'A', 'C', 'O', 'S'},
        {'R', 'A', 'T', 'O', 'S'},
        {'R', 'O', 'S', 'A', 'S'},
        {'C', 'O', 'S', 'A', 'S'},
        {'T', 'E', 'C', 'L', 'A'}
    };

    char salida[FILS][COLS];

    char salida_esperada[4][COLS] = {
        {'G', 'A', 'A', 'A', 'G'},
        {'A', 'A', 'G', 'A', 'V'},
        {'V', 'A', 'G', 'A', 'V'},
        {'V', 'V', 'V', 'V', 'V'}
    };

    assert(wordle(palabra, intentos, FILS, salida) == 4);
    assert(check_mat(4, COLS, salida_esperada, salida) == true);

    puts("OK!");
}
