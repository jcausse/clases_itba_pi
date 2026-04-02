#include <stdio.h>
#include <assert.h>

#define ERROR -1

#define ABS(x) ((x) >= 0 ? (x) : -(x))

/**
 * @brief Calcula x^n.
 * @details 0^n con n <= 0 no puede resolverse. En ese caso, devuelve -1.
 * @return x^n o -1 en caso de error.
 */
double potencia(const double x, const int n) {
    // Programacion defensiva
    if (x == 0) {
        return (n <= 0) ? ERROR : 0;
    }

    // Casos rapidos
    if (n == 0 || x == 1) {
        return 1;
    }

    // Caso general
    // Pasados los if, se que ni x ni n son cero
    double ret = 1;                     // Valor de retorno
    double delta = n > 0 ? x : 1/x;     // Numero a multiplicar (x si n > 0 o su inverso multiplicativo si n < 0)
    int iteraciones = ABS(n);

    for (int i = 0; i < iteraciones; i++) {
            ret *= delta;
    }

    return ret;
}

int main(void) {
    assert(potencia(2, 3) == 8);
    assert(potencia(2, 1) == 2);
    assert(potencia(2, 0) == 1);
    assert(potencia(0, 1) == 0);
    assert(potencia(1, -1) == 1);
    assert(potencia(1, -30) == 1);
    assert(potencia(2, -1) == 0.5);
    assert(potencia(2, -4) == 0.0625);
    assert(potencia(0, 1) == 0);
    assert(potencia(0, 0) == ERROR);
    assert(potencia(0, -1) == ERROR);

    puts("OK!");
}
