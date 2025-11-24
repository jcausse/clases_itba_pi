#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ESTADO_INICIAL -1
#define MAX_DECIMALES 2

void normalizar(char * s) {
    unsigned int read = 0;
    unsigned int write = 0;
    
    int decimales = ESTADO_INICIAL;

    while (s[read] != '\0') {

        // ---------------------- LOGICA DE ESTADOS ---------------------------------------

        // CASO 1: Leo una coma
        // Si es la coma, reseteo el contador de decimales a -1 (estado inicial), indicando
        // que estoy leyendo la parte entera
        if (s[read] == ',') {
            decimales = ESTADO_INICIAL;
        }

        // CASO 2: Leo un punto
        // Si es el punto, seteo el contador de decimales a 0, indicando que
        // estoy empezando a leer decimales, pero todavia no lei ninguno
        else if (s[read] == '.') {  
            decimales = 0;
        }
        
        // CASO 3: Leo un numero de la parte decimal
        // Si no leo ni el punto ni la coma, lo que leo es un numero. En el caso en el que ese
        // numero forme parte de la parte decimal, sumo 1 al contador de decimales. Me doy cuenta que
        // el numero forma parte de la parte decimal porque "decimales" no es -1
        else if (decimales >= 0) {
            decimales++;
        }

        // CASO 4: Leo un numero de la parte entera
        // En el caso en el que leo un numero que no forma parte de la parte decimal, simplemente
        // no hago nada (solo incremento el contador de lectura al final)

        // ---------------------- LOGICA DE COPIADO ---------------------------------------

        // CASO 1: Todavia no lei la suficiente cantidad de decimales (si estoy en la parte decimal),
        //         o lei cualquier otra cosa (punto, coma, o numero de la parte entera). Copio siempre.
        // Si la cantidad de decimales que lei hasta ahora es menor o igual que la cantidad maxima
        // de decimales que quiero dejar por cada numero, hago la copia
        if (decimales <= MAX_DECIMALES) {
            s[write] = s[read];
            write++;
        }

        // CASO 2: Estoy en la parte decimal y lei ya la cantidad maxima de decimales
        // No hago nada en este caso (no copiar equivale a eliminar el caracter)

        // ---------------------------------------------------------------------------------

        // Siempre incremento el indice de lectura
        read++;
    }
    
    // Asigno el caracter nulo al final de la cadena, para que la misma quede recortada
    s[write] = '\0';
}

int main() {
    char s[50];

    strcpy(s, "12.33333,23.44444,1.0054,5.003,7.0");
    normalizar(s);
    assert(strcmp(s, "12.33,23.44,1.00,5.00,7.0") == 0);
    
    strcpy(s, "12.33,3.4,1.00,5.0,7.1");
    normalizar(s);
    assert(strcmp(s, "12.33,3.4,1.00,5.0,7.1") == 0);
    
    puts("OK!");

    return 0;
}
