#include <stdio.h>
#include <math.h>

#include "lib/getnum.h"

#define PARTITIONS 100000
#define EPSILON 0.0001

typedef struct {
    double start;
    double end;
    double step;
} Interval;

typedef struct {
    double start;
    double end;
} SingleRoot;

typedef struct {
    size_t size;
    Roots * roots;
} Roots;

typedef double (* Function) (double);

Interval * generate_interval(double start, double end) {
    if (double_compare(start, end) <= 0 ) {
        return NULL;
    }

    Interval * i = malloc(sizeof(Interval));
    i->start = start;
    i->end = end;
    i->step = (end - start) / PARTITIONS;
    return i;
}

/**
 * @brief           Funcion de comparacion de dos Double
 * 
 * @return          1 si a > b, -1 si a < b, 0 si a = b, considerando
 *                  un error de EPSILON debido a la conversion
 */
static int double_compare (double a, double b) {
    if (fabs(a - b) < EPSILON) {
        return 0;
    }
    return a > b ? 1 : -1;
}

Roots raices (Interval * i, Function f) {
    return;
}

int main(void) {

    return 0;
}
