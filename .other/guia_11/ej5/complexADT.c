#include "complexADT.h"
#include <stdlib.h>

typedef struct complexCDT {
    double re;
    double im;
} complexCDT;

complexADT nuevoComp(double re, double im) {
    complexADT z = malloc(sizeof(struct complexCDT));
    z->re = re;
    z->im = im;
    return z;
}

double parteRealComp(const complexADT z) {
    return z->re;
}

double parteImagComp(const complexADT z) {
    return z->im;
}

complexADT sumaComp(const complexADT z1, const complexADT z2) {
    return nuevoComp(parteRealComp(z1) + parteRealComp(z2), parteImagComp(z1) + parteImagComp(z2));
}

complexADT restaComp(const complexADT z1, const complexADT z2) {
    return nuevoComp(parteRealComp(z1) - parteRealComp(z2), parteImagComp(z1) - parteImagComp(z2));
}

// (a + bi) * (c + di) = (ac - bd) + i(bc + ad)
complexADT multiplicaComp(const complexADT z1, const complexADT z2) {
    double a = parteRealComp(z1);
    double b = parteImagComp(z1);
    double c = parteRealComp(z2);
    double d = parteImagComp(z2);
    return nuevoComp(a * c - b * d, b * c + a * d);
}

complexADT divideComp(const complexADT z1, const complexADT z2) {
    return nuevoComp(0, 0); // TODO
}

complexADT conjugadoComp(const complexADT z) {
    return nuevoComp(parteRealComp(z), -parteImagComp(z));
}

void liberaComp(complexADT z) {
    free(z);
}
