#include <stdio.h>
#include <assert.h>

#define DIM 4
 
typedef enum colors {black=0, white, blue, red, purple, orange}; 

/**
 * IDEA: Recorro de 2 en 2 (con un vector imaginario de 2 casilleros en horizontal).
 * Para las filas pares, el primer casillero (izquierda) tiene que ser del color 1 y el segundo (derecha) del color 2.
 * Para las impares, el primer casillero debe ser de color 2 y el segundo de color 1.
 * En ambos casos, el casillero de la derecha (el segundo) puede ser del color indicado o puede no existir (si DIM es impar).
 */

int checkBoard(const unsigned char m[DIM][DIM]) {
    const unsigned char COLOR_1 = m[0][0];
    const unsigned char COLOR_2 = m[0][1];

    if (COLOR_1 == COLOR_2) {       // Importante: El caso general del algoritmo requiere dos colores distintos
        return 0;                   // Necesito esta verificacion inicial
    }

    for (unsigned int fil = 0; fil < DIM; fil++) {

        // Me fijo que color voy a tener en los casilleros izquierdos y derechos segun la fila que estoy procesando
        unsigned char color_izq = fil % 2 == 0 ? COLOR_1 : COLOR_2;
        unsigned char color_der = fil % 2 == 0 ? COLOR_2 : COLOR_1;

        for (unsigned int col = 0; col < DIM; col += 2) {
            if (m[fil][col] != color_izq) {     // Los casilleros izquierdos del vector imaginario tienen que coincidir con el color iquierdo
                return 0;                       // Nota: el casillero izquierdo es siempre valido
            }
            if (col + 1 < DIM && m[fil][col + 1] != color_der){     // Si la posicion derecha existe y no tiene el color derecho, no es valida
                return 0;
            }
        }
    }

    return 1;
}

int main(void) { 
   unsigned char t[DIM][DIM] = {  
           {black, white, black, white}, 
           {white, black, white, black}, 
           {black, white, black, white}, 
           {white, black, white, black}}; 
   // Es un tablero válido 
   assert(checkBoard(t) == 1); 
 
   unsigned char t2[DIM][DIM] = {  
           {black, white, black, white}, 
           {white, black, white, black}, 
           {black, white, black, white}, 
           {white, black, white, blue}}; 
   // No es válido pues se usaron más de dos colores 
   assert(checkBoard(t2) == 0);  
 
   unsigned char t3[DIM][DIM] = {  
           {black, white, black, white}, 
           {white, black, white, black}, 
           {white, black, white, black},
           {black, white, black, white}}; 
   // No es válido pues hay dos posiciones adyacentes del mismo color 
   assert(checkBoard(t3) == 0);

   puts("OK!");
 
   return 0; 
}
