#include <stdio.h>
#include <assert.h>

#define COLS 4

char toLowercase(char c) {         // O bien tolower de <ctype.h>
    return ('A' <= c && c <= 'Z') ? c - 'A' + 'a' : c;
}

bool equalsInsensitive(char a, char b) {
    return toLowercase(a) == toLowercase(b);
}

/**
 * @brief       Analiza si un paso de la escalera (cambio de una palabra a otra) es valido
 * @details     Un paso es valido cuando cambia exactamente una letra entre word1 y word1
 * 
 * @param[in]   word1       Primera palabra
 * @param[in]   word2       Segunda palabra
 * @param[out]  change      Indice de la letra que cambio   
 */
bool isValidStep(unsigned int wordLen, char word1[wordLen], char word2[wordLen], unsigned int * change) {
    bool foundChange = false;
    for (unsigned int i = 0; i < wordLen; i++) {            // Para cada posicion
        if (! equalsInsensitive(word1[i], word2[i])) {      // Si encuentro un cambio
            if (foundChange) {                              // No es step valido si ya habia un cambio
                return false;                               // previo
            }
            foundChange = true;                             // Anoto que encontre el cambio
            *change = i;                                    // Y donde lo encontre
        }
    }
    return true;
}

bool isWordLadder(unsigned int words, unsigned int wordLen, char mat[words][wordLen]) {
    // Si no hay palabras o son de longitud 0, no formaran escalera (nada que analizar)
    if (words == 0 || wordLen == 0) {
        return false;
    }

    // Una escalera de 1 sola palabra es escalera
    if (words == 1) {
        return true;
    }

    // Calculo la posicion del primer cambio
    unsigned int previousChange, currentChange;
    if(! isValidStep(wordLen, mat[0], mat[1], &previousChange)) {
        return false;
    }

    // Para la segunda palabra en adelante
    for (unsigned int i = 1; i < words - 1; i++) {
        // Me fijo que sea un cambio valido
        if(! isValidStep(wordLen, mat[i], mat[i + 1], &currentChange)) {
            return false;
        }
        // Y que no sea el mismo cambio que el anterior
        if (previousChange == currentChange) {
            return false;
        }
        previousChange = currentChange;
    }

    return true;
}

int main(void) {
    char wordMatrix[][COLS] = {
        {'T', 'e', 'S', 't'},
        {'b', 'e', 'S', 'T'},
        {'B', 'E', 's', 'o'},
        {'B', 'E', 'S', 'A'}
    };

    // Considerando todas las filas no es escalera
    // pues los últimos dos cambios son en la última letra
    assert(!isWordLadder(4, 4, wordMatrix));

    // Considerando una sola fila es escalera
    assert(isWordLadder(1, 4, wordMatrix) == 1);

    // Considerando las tres primeras filas es escalera
    assert(isWordLadder(3, 4, wordMatrix) == 1);

    char wordMatrix2[][3] = {
        {'T', 'e', 'S'},
        {'t', 'b', 'e'},
        {'S', 'b', 'E'},
        {'B', 'b', 'e'}
    };

    // TeS -> Tbe cambian dos letras
    assert(!isWordLadder(4, 3, wordMatrix2));

    char wordMatrix3[][3] = {
        {'a', 'm', 'o'},
        {'a', 'r', 'o'},
        {'o', 's', 'a'}
    };

    // aro -> osa cambian tres letras
    assert(!isWordLadder(3, 3, wordMatrix3));

    puts("OK!");
    return 0;
}
