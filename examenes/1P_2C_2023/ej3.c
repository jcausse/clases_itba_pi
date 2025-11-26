#include <stdio.h>
#include <assert.h>

// Por simplicidad, asumo que siempre son letras minusculas
bool anagrama(const char * s1, const char * s2) {
    unsigned char apariciones['z' - 'a' + 1] = {0};
    unsigned int i = 0;
    unsigned int cant_letras = 0;

    while (s1[i] != '\0') {                         // Para cada caracter en s1
        if (s1[i] != ' '){                          // No considero los espacios
            apariciones[s1[i] - 'a']++;             // Armo el vector de apariciones, para que me diga cuantas letras de cada una hay
            cant_letras++;                          // Agrego que tuve una letra mas
        }
        i++;
    }

    i = 0;
    while (s2[i] != '\0') {                         // Para cada caracter en s2, voy quitando apariciones del vector
        if (s2[i] != ' ') {                         // No considero los espacios
            // Si en algun momento aparece una letra que en el vector tiene valor 0, quiere decir que aparece
            // mas veces esa letra en s2 que en s1. No son anagramas.
            // Tampoco son anagramas si en algun momento la cantidad de letras que contamos llega a cero
            if (apariciones[s2[i] - 'a'] == 0 || cant_letras == 0) {    
                return false;                       
            }
            apariciones[s2[i] - 'a']--;             // Decremento la cantidad de apariciones
            cant_letras--;                          // Decremento el numero de letras
        }
        i++;
    }

    return cant_letras == 0;                        // Al final, se deben haber consumido todos los elementos del vector de apariciones
}

int main(void) {
    char * s = "anagrama";

    assert(anagrama(s, "amar gana"));
    assert(anagrama("enrique", "quieren"));
    assert(anagrama(s, s));
    assert(anagrama(" ", ""));
    assert(anagrama("amar gana", s));
    assert(anagrama("", ""));
    assert(anagrama("a gentleman", "elegant man"));
    assert(anagrama("a", "") == 0);
    assert(anagrama("mar", "amar") == 0);

    puts("OK!");
}
