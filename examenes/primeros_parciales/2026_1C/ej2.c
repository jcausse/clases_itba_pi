#include <stdio.h>
#include <assert.h>

/**
 * NOTA:
 * elemNumber = 0    --->  elemNumber / 2 = 0
 * elemNumber = 1    --->  elemNumber / 2 = 0
 * elemNumber = 2    --->  elemNumber / 2 = 1
 * elemNumber = 3    --->  elemNumber / 2 = 1
 * elemNumber = 4    --->  elemNumber / 2 = 2
 * y asi sucesivamente
 */

#define MASK            0x0F
#define NUM_ELEMS       16                          // 2^4
#define NO_REPEATED     -1

/**
 * @brief       Obtiene el elemento elemNumber de un packed array v que contiene elementos de 4 bits (2 por byte)
 * 
 * @param v             Packed Array
 * @param elemNumber    Numero de elemento (NO de byte)
 * 
 * @return      Elemento pedido
 */
int extractElement(const unsigned char * v, int elemNumber) {
    unsigned char byte = v[elemNumber / 2];         // Obtengo el byte correspondiente como elemNumber / 2 (NOTA)
    if (elemNumber % 2 == 0) {                      // Si el numero de elemento es par, hay que hacer >> 4
        byte >>= 4;                                 // byte = byte >> 4
    }
    return byte & MASK;                             // Me quedo con los ultimos 4 bits
}

// Funcion comun de vector de apariciones, sin preocuparse por como sacar el elemento del arreglo (eso lo hace la de arriba)
int firstRepeated(const unsigned char * v, unsigned dim, int * pos) {
    unsigned char currentValue;                     // Variable para guardar el valor actual a medida que itero
    unsigned char appearances[NUM_ELEMS] = {0};     // Vector de apariciones

    for (unsigned int i = 0; i < dim; i++) {        // Para cada indice de elemento
        currentValue = extractElement(v, i);        // Obtengo el elemento

        if (appearances[currentValue] == 1) {       // Si esta repetido
            * pos = i;                              // Digo donde
            return currentValue;                    // Retorno el valor del elemento repetido
        }

        appearances[currentValue] = 1;              // Marco el elemento como que ya salio
    }

    * pos = NO_REPEATED;                            // Caso no encontre ninguna repeticion, pongo que no hubo repetidos
    return NO_REPEATED;                             // Y retorno lo pedido
}

int main(void) { 
   int pos; 
   {    
       unsigned char arreglo[] = { 0x37, 0xF2, 0x03, 0x4A, 0xFF }; 
       assert(firstRepeated(arreglo, 10, &pos) == 3); // 3, 7, 15, 2, 0, 3, 4, 10, 15, 15 
       assert(pos == 5); 
       assert(firstRepeated(arreglo, 5, &pos) == -1); // 3, 7, 15, 2, 0 
       assert(pos == -1); 
   } 
   {    
       unsigned char arreglo[] = { 0x12, 0x34 }; 
       assert(firstRepeated(arreglo, 4, &pos) == -1); // 1, 2, 3, 4 
       assert(pos == -1); 
   } 
   { 
       unsigned char arreglo[] = { 0x56, 0x75 }; 
       assert(firstRepeated(arreglo, 4, &pos) == 5); // 5, 6, 7, 5 
       assert(pos == 3); 
   } 
   { 
       unsigned char arreglo[] = { 0x19, 0x90 }; 
       assert(firstRepeated(arreglo, 3, &pos) == 9); // 1, 9, 9 
       assert(pos == 2); 
       assert(firstRepeated(arreglo, 2, &pos) == -1 && pos == -1); // 1, 9 
       assert(firstRepeated(arreglo, 1, &pos) == -1 && pos == -1); // 1 
       assert(firstRepeated(arreglo, 0, &pos) == -1 && pos == -1); // Vector Vacío 
   } 
   { 
       unsigned char arreglo[] = { 0xBA, 0x88, 0x88 }; 
       assert(firstRepeated(arreglo, 6, &pos) == 8); // 11, 10, 8, 8, 8, 8 
       assert(pos == 3); 
   }

   puts("OK!"); 
   return 0; 
}
