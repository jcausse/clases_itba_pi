#include <stdio.h>
#include <assert.h>

#define END -1
#define COLS 5

void copyRemaining(int v[COLS], unsigned int read, int v3[COLS], unsigned int * write) {
    while (v[read] != END) {
        v3[*write] = v[read];
        read++;
        (*write)++;
    }
}

void difSimVec(int v1[COLS], int v2[COLS], int v3[COLS]) {
    unsigned int r1 = 0, r2 = 0, w = 0; // Read para v1 y v2, Write para v3

    // CASO 1: Tengo elementos en ambos arreglos
    while (v1[r1] != END && v2[r2] != END) {
        // CASO 1.1: Son iguales, no copio y avanzo
        if (v1[r1] == v2[r2]) {
            r1++;
            r2++;
        }

        // CASO 1.2: El de v1 es mas chico. Copio el de v1 y avanzo
        else if (v1[r1] < v2[r2]) {
            v3[w] = v1[r1];
            r1++;
            w++;
        }

        // CASO 1.3: El de v2 es mas chico. Copio el de v2 y avanzo
        else {
            v3[w] = v2[r2];
            r2++;
            w++;
        }
    }

    // CASO 2: Alguno de los dos arreglos (o los dos) se quedo sin elementos
    //         Siempre alguno de los dos copyRemaining no hace nada (o los dos, si se acabaron a la vez)
    copyRemaining(v1, r1, v3, &w);
    copyRemaining(v2, r2, v3, &w);

    // Al final, agrego el terminador
    v3[w] = END;
}

void difSim(unsigned int fils, int m1[fils][COLS], int m2[fils][COLS], int m3[fils][COLS]) {
    for (unsigned int i = 0; i < fils; i++) {
        difSimVec(m1[i], m2[i], m3[i]);
    }
}

// ------------------------------------------------------------------------------------------------
// TESTEO. EL EJERCICIO TERMINA ARRIBA.


int checkResultRow(int toCheckRow[COLS], int resultRow[COLS]) {
    unsigned int i = 0;
    do {
        if (toCheckRow[i] != resultRow[i]) {
            return 0;
        }
    } while(resultRow[i++] != END);
    return 1;
}

int checkResult(unsigned int fils, int toCheck[fils][COLS], int result[fils][COLS]) {
    for (unsigned int i = 0; i < fils; i++) {
        if (! checkResultRow(toCheck[i], result[i])) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int m1 [6][COLS] = {
        {1, 2, 3, 4, END},
        {3, 4, 5, END},
        {10, 15, 20, END},
        {END},
        {END},
        {5, 6, 7, END}
    };

    int m2 [6][COLS] = {
        {1, 2, 5, 6, END},
        {END},
        {15, END},
        {1, 2, 3, 4, END},
        {END},
        {1, 2, 5, 6, END}
    };

    int m3 [6][COLS];

    int result [6][COLS] = {
        {3, 4, 5, 6, END},
        {3, 4, 5, END},
        {10, 20, END},
        {1, 2, 3, 4, END},
        {END},
        {1, 2, 7, END}
    };
    
    difSim(6, m1, m2, m3);
    assert(checkResult(6, m3, result) == 1);

    puts("OK!");

    return 0;
}
