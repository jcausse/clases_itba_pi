#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

void eraseTop(char s[], char c, unsigned int top) {
    // Si top es cero no tengo nada que hacer, early return por eficiencia
    if (top == 0) {
        return;
    }

    // Paso el caracter a minuscula 1 sola vez para luego hacer la comparacion siempre en minusculas
    c = tolower(c);
    unsigned int read = 0, write = 0;
    while (s[read] != '\0') {
        
        // Si el caracter encontrado NO coincide con el que quiero eliminar
        // o no me quedan mas ocurrencias que pueda eliminar segun el top
        if (top == 0 || tolower(s[read]) != c) {
            s[write] = s[read];     // Copio
            write++;
        }

        // Si coincide
        else {              
            top--;                  // Al no copiar, elimine. Resto uno al top  
        }

        read++;                     // El indice de lectura se incrementa siempre
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
