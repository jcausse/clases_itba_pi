#include <stdio.h>
#include <assert.h>

void piramide(unsigned int * latas, unsigned int * altura) {
    if (*latas >= (*altura + 1) * (*altura + 1)) {      // Si llego a cubrir el nivel actual (como altura empieza en 1, el nivel actual)
        (*altura)++;                                    // Incremento la cantidad de niveles cubiertos
        *latas -= (*altura) * (*altura);                // Decremento la cantidad de latas restantes consumiendo las de este nivel
        piramide(latas, altura);
    }
}

int main(void) {
    unsigned int latas, altura;

    latas = 10;
    altura = 0;
    piramide(&latas, &altura);
    assert(latas == 5);
    assert(altura == 2);

    latas = 55;
    altura = 0;
    piramide(&latas, &altura);
    assert(latas == 0);
    assert(altura == 5);

    latas = 1;
    altura = 0;
    piramide(&latas, &altura);
    assert(latas == 0);
    assert(altura == 1);

    puts("OK!");
    return 0;
}
