#include <stdio.h>
#include <string.h>
#include <assert.h>

void eliminaRepetidas(char * s) {
    int read = 0, write = 0, last_c = -1;

    while(s[read] != '\0') {
        // Caso 1: Si el caracter actual en read no coincide con last_c, entonces es un caracter nuevo.
        //         Lo copio y avanzo. Ademas, me lo guardo en last_c.
        if (s[read] != last_c) {
            s[write] = s[read];         // Copio
            last_c = s[read];           // Lo guardo en last_c
            write++;                    // Avanzo write
        }

        // Caso 2: Si coincide el caracter actual con el guardado, solo avanza (+ continuacion Caso 1)
        read++;                         // Siempre avanzo sobre read para ir al caracter siguiente.
    }

    s[write] = '\0';
}

int main(void) {
    char s[50];

    strcpy(s, "Gooooooooooollllllll de Messiiiiiiii");
    eliminaRepetidas(s);
    assert(strcmp(s, "Gol de Mesi") == 0);

    strcpy(s, "aaaaaaaaaaaa aaaaa aa a");
    eliminaRepetidas(s);
    assert(strcmp(s, "a a a a") == 0);

    strcpy(s, "abcde");
    eliminaRepetidas(s);
    assert(strcmp(s, "abcde") == 0);

    strcpy(s, "");
    eliminaRepetidas(s);
    assert(strcmp(s, "") == 0);

    puts("OK!");
}
