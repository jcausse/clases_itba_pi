#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * Recuerdo: rand() devuelve un numero pseudo-aleatorio entre 0 y RAND_MAX (cte simbolica), 
 * ambos extremos incluidos.
 * Antes de usar rand, se debe llamar a srand para inicializar la semilla de la sucesion
 * pseudo-aleatoria.
 */

/**
 *  @brief Genera un numero aleatorio entre a y b (incluido). Si a > b, los intercambia.
 *  @details La distribucion no es las mejor, porque se usa aritmetica modular.
 *  @param a Valor minimo.
 *  @param b Valor maximo.
 *  @return Numero aleatorio entre a y b.
 */
int rand_int_modulo(const int a, const int b) {
    return rand() % (MAX(a, b) - MIN(a, b) + 1) + MIN(a, b);
}

/**
 * @brief Genera un numero en el intervalo [0, 1)
 * @return Numero aleatorio
 */
double rand_normalize() {
    return rand() / ((double) RAND_MAX + 1);
}

/**
 *  @brief Genera un numero aleatorio entre a y b (incluido). Si a > b, los intercambia.
 *  @details La distribucion es buena, ya que usa rand_normalize.
 *  @param a Valor minimo.
 *  @param b Valor maximo.
 *  @return Numero aleatorio entre a y b.
 */
int rand_int(const int a, const int b) {
    return rand_normalize() * (MAX(a, b) - MIN(a, b) + 1) + MIN(a, b);
}

int main() {
    srand(time(NULL));
    printf("Usando rand_int_modulo: %d\n", rand_int_modulo(10, 50));
    printf("rand_normalize: %lg\n", rand_normalize());
    printf("Usando rand_int: %d\n", rand_int(10, 50));
}
