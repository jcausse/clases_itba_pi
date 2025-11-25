/**
 * Escribir una funcion eraseLast que reciba como unicos parametros:
 * - un string, s, que se sabe que solamente esta formado por caracteres US-ASCII (no ASCII extendido)
 * - un numero entero positivo o cero, n
 * 
 * La funcion debe dejar en el string las primeras n apariciones de cada caracter, eliminando
 * el resto de apariciones de aquellos que ya hayan aparecido n veces.
 * 
 * Ademas, debera devolver la cantidad de caracteres eliminados
 * 
 * Ejemplos:
 * - si s = "hola, buen dia!!!" y n = 1, s queda como "hola, buendi!" y devuelve 4
 * - si s = "hola, buen dia!!!" y n = 2, s queda como "hola, buen dia!!" y devuelve 1 
 * - si s = "hola, buen dia!!!" y n = 3, s no cambia y devuelve 0
 * - si s = "hola, buen dia!!!" y n = 0, s queda como "" (queda vacio pues permite 0 apariciones por caracter) y devuelve 17
 * - si s = "aaaaabbcdddeeeeffffff" y n = 3, s queda como "aaabbcdddeeefff" y devuelve 6
 * - si s = "una. manzana. roja.??" y n = 1, s queda como "una. mzroj?" y devuelve 10
 * - si s = NULL, devuelve 0 sin abortar
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX 128

// NOTA:
//
// Si la funcion no tuviera que devolver la cantidad de eliminados (supongamos que fuese void), un caso muy interesante de
// tratar aparte seria el caso con n = 0. Este caso se queda con las primeras 0 apariciones de cada caracter, es decir, no
// permite que haya ningun caracter en el string ya que cada uno puede aparecer, A LO SUMO 0 veces. Entonces elimina todo.
// Lo que se puede hacer es, debajo del chequeo de NULL, agregar a la funcion un if:
// if (n == 0) {
//     s[0] = '\0';
//     return;
// }
//
// Para la version donde se pide retornar la cantidad de eliminados, cuando n = 0, elimina todos los caracteres, por lo que
// el valor de retorno de eraseLast coincide con strlen(s). Si bien la funcion como esta implementada abajo cumple con el
// caso de n = 0 (porque el if de la linea 72 tiene una condicion que siempre es falsa cuando n = 0, y entonces la variable
// eliminados se incrementa en 1 por cada caracter), esto es un poco ineficiente ya que sabemos que el if en cuestion tiene
// una condicion falsa siempre, pero que igual la estamos verificando para cada caracter. En este caso, es mas sencillo y mas
// eficiente tratar este caso aparte agregando debajo del chequeo de NULL una condicion similar a la anterior que sea:
// if (n == 0) {
//     size_t len = strlen(s);
//     s[0] = '\0';
//     return len;
// }

size_t eraseLast(char * s, size_t n) {
    if (s == NULL) {                        // Chequeo de string nulo (necesario por el ultimo caso de prueba)
        return 0;
    }

    if (n == 0) {                           // Optimizacion para el caso n = 0 (ver NOTA arriba)
        size_t len = strlen(s);
        s[0] = '\0';
        return len;
    }

    // CASO GENERAL

    unsigned char apariciones[MAX] = {0};   // Vector de apariciones para todos los caracteres
    size_t r = 0, w = 0;                    // Indices para el string (r = read, w = write)
    size_t eliminados = 0;                  // Cantidad de caracteres eliminados
    unsigned int ix;                        // Indice para acceder sobre el arreglo

    while (s[r] != '\0') {                  // Para cada caracter en el string
        ix = s[r];                          // Calculo el indice de ese caracter sobre el vector de apariciones

        // CASO 1: No hay que eliminarlo
        if (apariciones[ix] < n) {          // Si la cantidad de apariciones de ese caracter aun no supera a n
            apariciones[ix]++;              // Le incremento en 1 la cantidad de apariciones, pero lo copio
            s[w] = s[r];                    // Copio igual que siempre en el algoritmo de elimina-ceros
            w++;
        }

        // CASO 2: Elimino cuando el caracter ya aprecio n o mas veces (apariciones[s[r]] >= n)
        else {
            eliminados++;                   // Incremento en 1 la cantidad de caracteres elmiminados
        }

        // PARA AMBOS CASOS
        r++;                                // Siempre (elimine o no) avanzo el puntero de lectura
    }

    s[w] = '\0';                            // Como siempre, agregamos el terminador al final
    return eliminados;                      // Retorno la cantidad de eliminados
}

int main(void) {
    char s[50];
    size_t e;

    strcpy(s, "hola, buen dia!!!");
    e = eraseLast(s, 1);
    assert(strcmp(s, "hola, buendi!") == 0);
    assert(e == 4);

    strcpy(s, "hola, buen dia!!!");
    e = eraseLast(s, 2);
    assert(strcmp(s, "hola, buen dia!!") == 0);
    assert(e == 1);

    strcpy(s, "hola, buen dia!!!");
    e = eraseLast(s, 3);
    assert(strcmp(s, "hola, buen dia!!!") == 0);
    assert(e == 0);

    strcpy(s, "hola, buen dia!!!");
    e = eraseLast(s, 0);
    assert(strcmp(s, "") == 0);
    assert(e == 17);

    strcpy(s, "aaaaabbcdddeeeeffffff");
    e = eraseLast(s, 3);
    assert(strcmp(s, "aaabbcdddeeefff") == 0);
    assert(e == 6);

    strcpy(s, "una. manzana. roja.??");
    e = eraseLast(s, 1);
    assert(strcmp(s, "una. mzroj?") == 0);
    assert(e == 10);

    e = eraseLast(NULL, 1);
    assert(e == 0);

    puts("OK!");
}
