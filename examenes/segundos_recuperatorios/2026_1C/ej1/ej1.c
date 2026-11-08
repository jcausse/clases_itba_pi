#include <stdio.h>
#include <assert.h>

#define END     -1
#define OK      1
#define NOT_OK  0

int sumOK(const int * v) {
    // Caso Base: En la posicion actual esta el terminador, por lo tanto
    // si llegue hasta aca quiere decir que todo estuvo OK
    if (*v == END) {
        return OK;
    }

    // Si el actual no es el terminador, hay 4 posibilidades:
    // 1. El siguiente (v + 1) es el terminador, y no pude formar el grupo de 3
    //    ---> NOT_OK
    // 2. El sub-siguiente (v + 2) es el terminador, y no pude formar el grupo de 3
    //    ---> NOT_OK
    // 3. Ni v + 1 ni v + 2 son el terminador, el grupo de 3 se forma, pero la suma no da
    // 4. Forme el grupo de 3, y la suma coincide (*v + *(v + 1) == *(v + 2))

    // Casos 1 y 2: Encontre un terminador sin poder formar un grupo de 3
    if (*(v + 1) == END || *(v + 2) == END) {
        return NOT_OK;
    }

    // Caso 3: Se forma el grupo de 3 pero la suma da mal
    if (*v + *(v + 1) != *(v + 2)) {
        return NOT_OK;
    }

    // Caso 4: Paso recursivo donde avanzo al (posible) siguiente grupo de 3
    return sumOK(v + 3);
}

int main(void) { 
    {   
        int v[] = {1, 2, 3, 2, 1, 3, 4, 3, 7, 2, 0, 2, -1}; 
        assert(sumOK(v));
    } 
    {   
        int v[] = {1, 2, 3, 2, 1, -1};                  // falta un elemento que sea 3 
        assert(!sumOK(v));
    } 
    {   
        int v[] = {1, 2, 3, 2, 2, 5, 2, 4, 6, -1};      // 2+2 no es 5 
        assert(!sumOK(v));
    } 
    {   
        int v[] = { -1};    
        assert(sumOK(v));     
    }

    puts("OK!");
    return 0; 
}
