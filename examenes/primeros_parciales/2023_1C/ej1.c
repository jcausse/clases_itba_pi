#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

void elimina(char v1[], const char v2[], const char v3[]) {
    bool v2_valid = true, v3_valid = true, v2_matches, v3_matches;
    unsigned int read = 0, write = 0;

    while (v1[read] != '\0' && (v2_valid || v3_valid)) {
        v2_valid = v2_valid && v2[read] != '\0';            // Indica si una lectura sobre v2 es valida
        v3_valid = v3_valid && v3[read] != '\0';            // Indica si una lectura sobre v3 es valida

        v2_matches = v2_valid && v2[read] == v1[read];      // v2[r] coincide con v1[r] solo si se podia leer sobre v2
        v3_matches = v3_valid && v3[read] == v1[read];      // v3[r] coincide con v1[r] solo si se podia leer sobre v2

        if (!v2_matches && !v3_matches){                    // Si ninguno coincidio,
            v1[write] = v1[read];                           // copiar
            write++;
        }

        read++;
    }

    while (v1[read] != '\0') {                              // Terminar de mover los elementos que faltaban de v1
        v1[write] = v1[read];                               // Este ciclo podria no ejecutar nunca si antes v1[read] se hizo '\0'
        read++;
        write++;
    }

    v1[write] = '\0';                                       // Agregar, como SIEMPRE, la marca de final
}

int main(void) {
    char s[] = "abc";
    
    elimina(s, "123", "cab");
    assert(strcmp(s, "abc") == 0); // No se eliminan caracteres

    elimina(s, "axc", "xbc");
    // Se elimina la a porque está en s2 en la misma posición
    // se elimina la b porque está en s3 en la misma posición
    // Se elimina la c porque está en s2 o en s3 en la misma posición
    assert(strcmp(s, "") == 0);

    char t[] = "abc 123";
    elimina(t, "b", "1");
    assert(strcmp(t, "abc 123") == 0); // No se eliminan caracteres
    
    elimina(t, "aaaaaaaaaaaaaaaaaaaaaa", "2222222222222222222");
    assert(strcmp(t, "bc 13") == 0);
    
    elimina(t, "", ""); // No se eliminan caracteres
    assert(strcmp(t, "bc 13") == 0);
    
    puts("OK!");
    return 0;
}
