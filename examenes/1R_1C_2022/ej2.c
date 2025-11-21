#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

// Indica si cumple a la vez:
// 1. es una letra
// 2. es vocal
bool isvowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// Indica si cumple a la vez:
// 1. es una letra
// 2. es consonante
bool isconsonant(char c) {
    return isalpha(c) && ! isvowel(c);
}

bool shouldDelte(char * s, int r) {
    if (! isalpha(s[r])) {          // Caso 1: Los caracteres que NO son letras no se eliminan
        return false;
    }
    if (! isvowel(s[r])) {          // Caso 2: Las consonantes nunca se eliminan
        return false;
    }

    // Solo elimina cuando es una vocal y antes o despues tiene una consonante
    return (r > 0 && isconsonant(s[r - 1])) || isconsonant(s[r + 1]);
}

void eliminaVoc(char * s) {
    int read = 0, write = 0;

    while (s[read] != '\0') {
        if (! shouldDelte(s, read)) {       // Si el caracter que estoy viendo no debe ser eliminado (hay que mantenerlo)
            s[write] = s[read];             // Lo copio (se mantiene)
            write++;                        // Incremento el indice de escritura
        }
        read++;                             // Incremento lectura incondicionalmente
    }
    s[write] = '\0';
}

int main(void) {
    char s[50];

    strcpy(s, "hola mundo");
    eliminaVoc(s);
    assert(strcmp(s, "hl mnd") == 0);

    strcpy(s, "hola a todo el mundo");
    eliminaVoc(s);
    assert(strcmp(s, "hl a td l mnd") == 0);

    strcpy(s, "xyz");
    eliminaVoc(s);
    assert(strcmp(s, "xyz") == 0);

    strcpy(s, "aholoaaa");
    eliminaVoc(s);
    assert(strcmp(s, "hlaaa") == 0);

    strcpy(s, "");
    eliminaVoc(s);
    assert(strcmp(s, "") == 0);

    strcpy(s, "aa eo iu oa uo");
    eliminaVoc(s);
    assert(strcmp(s, "aa eo iu oa uo") == 0);

    strcpy(s, "pa po pi po pu");
    eliminaVoc(s);
    assert(strcmp(s, "p p p p p") == 0);

    strcpy(s, "aeiou");
    eliminaVoc(s);
    assert(strcmp(s, "aeiou") == 0);

    strcpy(s, "a,e,i,o,u");
    eliminaVoc(s);
    assert(strcmp(s, "a,e,i,o,u") == 0);

    puts("OK!");
}
