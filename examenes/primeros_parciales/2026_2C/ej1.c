#include <stdio.h>
#include <assert.h>

#define SIZE 16
#define MASK 0x0F
#define ELEM_SIZE 4

/*
IDEA: Necesito hacer una funcion de mapeo que tome un indice (numero de elemento al que quiero
acceder) y me devuelva exactamente en que byte esta ese elemento y en que nibble (0: izquierdo
o mas significativo, 1: derecho o menos significativo) dentro del byte

f(indice) = (byte, nibble)
f(0) -> (0, 0)
f(1) -> (0, 1)
f(2) -> (1, 0)
f(3) -> (1, 1)
f(4) -> (2, 0)
f(5) -> (2, 1)
f(6) -> (3, 0)
f(7) -> (3, 1)
...                 y asi sucesivamente

La funcion matematica que me sirve para hacer este mapeo es:

f(n) = (f1(n), f2(n)), con:
    f1(n) = n / 2
    f2(n) = n % 2

Luego, con esos datos, se hace lo siguiente para acceder al n-esimo elemento del packed-array:

- Para acceder al elemento n del packed-array, calculo f1(n) que es el numero de byte y accedo
  a esa posicion. Por ejemplo:
  - Elemento 0: v[0 / 2] = v[0]
  - Elemento 7: v[7 / 2] = v[3]
  - Elemento n: v[n / 2]

- Luego, con ese byte, debo acceder al nibble correspondiente. Calculo f2(n) y:
  - Si f2(n) es 0, quiere decir que tengo que acceder a los 4 bits de la izquierda:
    - Hago decalaje 4 veces a la derecha para posicionar los 4 bits de la izquierda del lado derecho
    - Aplico una mascara 0x0F con una operacion AND bit a bit, que me permite "matar" todos los bits
      excepto los 4 del lado derecho
  - Si f2(n) es 1, quiere decir que tengo que acceder a los 4 bits de la derecha:
    - Como los 4 bits que quiero acceder ya estan del lado derecho, no se necesita decalaje
    - Aplico una mascara 0x0F con una operacion AND bit a bit, que me permite "matar" todos los bits
      excepto los 4 del lado derecho
*/
unsigned char getElem(const unsigned char v[], unsigned int n) {
    unsigned int byteNumber = n / 2;                // f1(n)
    unsigned int nibbleNumber = n % 2;              // f2(n)

    unsigned char byte = v[byteNumber];

    if (nibbleNumber == 0) {                        // Aplico decalaje (solo para nibble 0)
        byte >>= ELEM_SIZE;
    }
    return byte & MASK;                             // Aplico mascara y retorno (ambos bytes)
}

/**
 * @brief           Recibe un vector vec de size elementos, y devuelve en que indice
 *                  se encuentra el elemento mayor (busqueda de maximo).
 * @details         Si existen dos elementos maximos (el maximo aparece mas de una vez),
 *                  se devuelve el indice de la primera de las apariciones.
 *                  Por ejemplo, para vec = [0, 3, 2, 1, 3], devuelve 1
 */
unsigned int maxIndex(unsigned int size, const unsigned int vec[size]) {
    if (size <= 1) {                                // Si el arreglo tiene 1 solo elemento,
        return 0;                                   // el primero es el maximo porque es el unico
    }
    
    unsigned int maxIx = 0;                         // Asumo que el mayor es el primer elemento

    for (unsigned int i = 1; i < size; i++) {       // Desde el segundo en adelante
        if (vec[i] > vec[maxIx]) {                  // Si el elemento en la posicion i es mayor que
            maxIx = i;                              // aquel en la posicion maxIx, guardo en maxIx el
        }                                           // valor de i, ya que en esa posicion esta el mayor
    }                                               // elemento visto hasta ahora

    return maxIx;                                   // En maxIx quedo la posicion del mas grande
}

void mostRepeated(const unsigned char v[], int dim, int * num, int * qty) {
    /* Caso borde: si dim == 0, no hago nada */
    if (dim == 0) {
        return;
    }

    int currentElem;

    /* Vector de apariciones */
    unsigned int appearances[SIZE] = {0};           // Vector de apariciones para los 16 posibles numeros, inicializado con ceros

    /* Contar la cantidad de apariciones de cada elemento 0..15 */
    for (unsigned int i = 0; i < dim; i++) {        // Para cada posicion del packed-array
        currentElem = getElem(v, i);                // Obtengo el elemento en esa posicion
        appearances[currentElem]++;                 // Le anoto una aparicion mas al elemento
    }

    /* Buscar el numero que mas aparece buscando el maximo del vector de apariciones */
    unsigned int maxIx = maxIndex(SIZE, appearances);

    /* Retornar cual fue el que mas aparecio y cuantas veces */
    *num = maxIx;                                   // El indice del vec. apariciones es igual al numero
    *qty = appearances[maxIx];                      // En ese indice se guarda cuantas veces aparecio
}

int main(void) { 
    unsigned char vec[] = { 0x34, 0xA3, 0xAA };
    int num=1000; 
    int qty=900; 
    mostRepeated(vec, 0, &num, &qty); 
    assert(num==1000); 
    assert(qty==900); 
 
    mostRepeated(vec, 1, &num, &qty); 
    assert(num==3); 
    assert(qty==1); 
 
    mostRepeated(vec, 2, &num, &qty); 
    assert(num==3 || num==4); 
    assert(qty==1);

    mostRepeated(vec, 5, &num, &qty); 
    assert(num==3 || num==10); 
    assert(qty==2); 
 
    mostRepeated(vec, 6, &num, &qty); 
    assert(num==10); 
    assert(qty==3); 
 
    puts("OK!"); 
    return 0; 
}
