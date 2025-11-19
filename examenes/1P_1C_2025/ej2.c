#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

void eraseTop(char * s, char c, const unsigned int top) {
    if (top <= 0) {                 // Por eficiencia, termino si no
        return;                     // hay nada que eliminar
    }

    c = tolower(c);                 // Comparo siempre en minuscula.

    size_t read = 0;                // Indice para leer. Avanza siempre.
    size_t write = 0;               // Indice para escribir. Avanza solo cuando no hay coincidencias (copia y avanza).
    int erased = 0;                 // Cantidad que elimine actualmente

    // Parte 1: Aplico el algoritmo de eliminar ceros mientras:
    //          1. No se me termine el string, y
    //          2. No haya llegado a la cantidad de eliminaciones pedida
    while (s[read] != '\0' && erased < top) {

        // Caso 1: El caracter actual no es c. No lo elimino. Copio y avanzo.
        if (tolower(s[read]) != c) {
            s[write] = s[read];
            write++;
        }

        // Caso 2: El caracter actual es c. Sera sobreescrito mas adelante porque no copie y no incremente write.
        //         Esto elimina ese caracter, por lo que erased se incrementa.
        else {
            erased++;
        }

        // Siempre avanzo el de escritura.
        read++;
    }

    // Parte 2: Como la Parte 1 podia terminar por erased >= top antes de terminar de leer todo el string, debo
    //          seguir copiando el resto del string, independientemente de si me encuentro con c o no (porque si
    //          me lo encuentro da igual, porque no hay que volver a eliminar)
    while (s[read] != '\0') {
        s[write] = s[read];     // Copio
        read++;                 // Avanzo de forma incondicional
        write++;                // Avanzo de forma incondicional
    }

    s[write] = '\0';
}

int main(void) {
    char s[50];

    strcpy(s, "You play me like dun dun dun");
    eraseTop(s, 'n', 5);
    assert(strcmp(s, "You play me like du du du") == 0);

    strcpy(s, "You play me like dun dun dun");
    eraseTop(s, 'n', 2);
    assert(strcmp(s, "You play me like du du dun") == 0);

    strcpy(s, "You play me like dun dun dun");
    eraseTop(s, 'n', 0);
    assert(strcmp(s, "You play me like dun dun dun") == 0);

    strcpy(s, "You play me like dun dun dun");
    eraseTop(s, 'x', 3);
    assert(strcmp(s, "You play me like dun dun dun") == 0);

    strcpy(s, "You play me like dun dun dun");
    eraseTop(s, 'y', 1);
    assert(strcmp(s, "ou play me like dun dun dun") == 0);

    strcpy(s, "You play me like dun dun dun");
    eraseTop(s, 'Y', 2);
    assert(strcmp(s, "ou pla me like dun dun dun") == 0);

    strcpy(s, "You play me like dun dun dun");
    eraseTop(s, ' ', 4);
    assert(strcmp(s, "Youplaymelikedun dun dun") == 0);

    puts("OK!");
}
