/**
 * Diseñar e implementar la funcion top_3_letters que recibe un texto formado unicamente por caracteres del
 * alfabeto ingles, tanto en mayuscula como en minuscula, y espacios (no hace falta validarlo), del cual se 
 * asume que tiene al menos 3 caracteres distintos
 * 
 * La funcion debe determinar cuales son las 3 letras que mas aparecen y cuantas veces aparecen (el espacio
 * cuenta como letra)
 * 
 * La funcion recibe un texto (en forma de array de char terminado en cero), y dos vectores de salida de tamaño 3:
 * - Uno de 3 char llamado top_letters
 * - Uno de 3 int llamado letter_count
 * 
 * En top_letters deben estar, en orden, las letras que mas aparecen (en caso de empate, la de menor valor ASCII)
 * En letter_count, la cantidad de veces que aparece cada letra del top
 * 
 * NOTA: Es interesante (y mucho mas dificil) plantear el ejercicio de manera que el vector de apariciones tenga
 * exactamente el tamaño necesario, en lugar de hacer un vector de 256 posiciones para cada posible char
 * 
 * SOLUCION: https://github.com/jcausse/clases_itba_pi/tree/main/extras/primer_parcial/top_3_letters.c
 */

#include <stdio.h>
#include <assert.h>

static unsigned int max_index(const int v[], const unsigned int dim) {
    unsigned int ret = 0;
    for (unsigned int i = 1; i < dim; i++) {
        if (v[i] > v[ret]) {
            ret = i;
        }
    }
    return ret;
}

/***************************************************************************************/

#define SPACE 0
#define UPPERCASE_START 1
#define UPPERCASE_END 26
#define LOWERCASE_START 27
#define LOWERCASE_END 52

/**
 * @brief Get the index for a given character c in the count vector (forward mapping)
 * @details Distribution:
 *          - 0: space
 *          - 1-26: uppercase letters
 *          - 27-52: lowercase letters
 * @return Returns the index corresponding to c, or -1 on error
 */
static int index_mapper(const char c) {
    if (c == ' ') {
        return SPACE;
    }
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + UPPERCASE_START;
    }
    if ('a' <= c && c <= 'z') {
        return c - 'a' + LOWERCASE_START;
    }
    return -1;
}

/**
 * @brief Get the character for a given index i in the count vector (reverse mapping)
 * @details Distribution:
 *          - 0: space
 *          - 1-26: uppercase letters
 *          - 27-52: lowercase letters
 * @return Returns the character corresponding to i, or '\0' on error
 */
static char character_mapper(const int i) {
    if (i == SPACE) {
        return ' ';
    }
    if (UPPERCASE_START <= i && i <= UPPERCASE_END) {
        return 'A' + i - UPPERCASE_START;
    }
    if (LOWERCASE_START <= i && i <= LOWERCASE_END) {
        return 'a' + i - LOWERCASE_START;
    }
    return '\0';
}

/***************************************************************************************/

#define TOP_SIZE 3

#define UPPERCASE_LETTERS 26
#define LOWERCASE_LETTERS 26
#define OTHER_CHARACTERS  1
#define COUNT_VECTOR_DIM UPPERCASE_LETTERS + LOWERCASE_LETTERS + OTHER_CHARACTERS

#define MARK -1

// We assume that the phrase is always composed of US-ASCII letters and spaces
void top_3_letters(const char phrase[], char top_letters[TOP_SIZE], int letter_count[TOP_SIZE]) {

    // Allow negatives to mark top values so they are not selected twice
    int count_vector[COUNT_VECTOR_DIM] = {0};

    unsigned int i = 0, j;
    char c;
    while((c = phrase[i]) != '\0') {
        count_vector[index_mapper(c)]++;
        i++;
    }

    for (i = 0; i < TOP_SIZE; i++) {
        j = max_index(count_vector, COUNT_VECTOR_DIM);
        top_letters[i] = character_mapper(j);
        letter_count[i] = count_vector[j];
        count_vector[j] = MARK;
    }
}

/***************************************************************************************/

int main(void) {
    char top_letters[TOP_SIZE];
    int letter_count[TOP_SIZE] = {0};

    // -------------------------------------------------------------------------
    // CASO 1: Frase
    // -------------------------------------------------------------------------

    top_3_letters("La musica es una forma de vida", top_letters, letter_count);

    assert(top_letters[0] == ' ');
    assert(top_letters[1] == 'a');
    assert(top_letters[2] == 'd');

    assert(letter_count[0] == 6);
    assert(letter_count[1] == 5);
    assert(letter_count[2] == 2);

    // -------------------------------------------------------------------------
    // CASO 2: Empate masivo (Prueba estricta de la regla del menor ASCII)
    // El texto tiene 4 caracteres distintos que aparecen exactamente 1 vez.
    // ASCII: 'Y' (89), 'Z' (90), 'y' (121), 'z' (122).
    // Deberían ganar los 3 de menor valor ASCII.
    // -------------------------------------------------------------------------

    top_3_letters("zZyY", top_letters, letter_count);
    
    assert(top_letters[0] == 'Y');
    assert(top_letters[1] == 'Z');
    assert(top_letters[2] == 'y');
    
    assert(letter_count[0] == 1);
    assert(letter_count[1] == 1);
    assert(letter_count[2] == 1);

    // -------------------------------------------------------------------------
    // CASO 3: Case Sensitivity y competencia con espacios
    // Frecuencias: ' ' (5 veces), 'A' (3 veces), 'a' (3 veces).
    // Hay un empate en el 2do y 3er puesto entre 'A' (65) y 'a' (97).
    // 'A' debe quedar segunda por tener menor ASCII.
    // -------------------------------------------------------------------------
    
    top_3_letters("A a A a A a", top_letters, letter_count);
    
    assert(top_letters[0] == ' ');
    assert(top_letters[1] == 'A');
    assert(top_letters[2] == 'a');
    
    assert(letter_count[0] == 5);
    assert(letter_count[1] == 3);
    assert(letter_count[2] == 3);

    // -------------------------------------------------------------------------
    // CASO 4: Inversión de orden de aparición
    // Frecuencias: 'c' (3), 'b' (2), 'a' (1)
    // Para asegurar que el algoritmo no dependa del orden de lectura o del ASCII 
    // para ordenar ganadores claros.
    // -------------------------------------------------------------------------
    
    top_3_letters("c b c b c a", top_letters, letter_count);
    
    // 'c' aparece 3 veces, ' ' aparece 5, 'b' aparece 2, 'a' aparece 1
    // Top 3: ' ' (5), 'c' (3), 'b' (2)
    assert(top_letters[0] == ' ');
    assert(top_letters[1] == 'c');
    assert(top_letters[2] == 'b');
    
    assert(letter_count[0] == 5);
    assert(letter_count[1] == 3);
    assert(letter_count[2] == 2);

    puts("OK!");

    return 0;
}
