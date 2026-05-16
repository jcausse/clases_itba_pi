#include <stdio.h>
#include <assert.h>

#define END -1

int sumMatch(const int * v) {
    if (*v == END) {
        return 0;
    }

    int ret = sumMatch(v + 1);

    // Si es un cero el retorno anterior, se inicia una nueva secuencia donde el actual es la suma
    // de todos los anteriores en la secuencia, devuelvo el actual (la suma).
    if (ret == 0) {
        return *v;
    }

    // Si el caso anterior no me devolvio cero, estoy dentro de una secuencia. Le resto el actual.
    return ret - *v;

}

void test_should_return_zero() {
    int v1[]={1,2,3,6,4,3,2,9,1,2,3,-1};
    int v2[]={1,1,2,4,5,5,14,-1};
    int v3[]={3,3,-1};
    int v4[]={1,1,2,2,90,90,-1};
    int v5[]={1,0,1,2,2,2,6,-1};
    int v6[]={-1};
    int v7[]={0,-1};
    int v8[]={1, 2, 3, 6, 7, 8, 9, 24, -1};

    assert(sumMatch(v1) == 0);
    assert(sumMatch(v2) == 0);
    assert(sumMatch(v3) == 0);
    assert(sumMatch(v4) == 0);
    assert(sumMatch(v5) == 0);
    assert(sumMatch(v6) == 0);
    assert(sumMatch(v7) == 0);
    assert(sumMatch(v8) == 0);   
}

void test_should_return_non_zero() {
    int v1[]={1,1,2,3,6,4,3,2,9,1,2,3,-1};
    int v2[]={1,1,2,4,5,5,14,10,-1};
    int v3[]={4,3,-1};
    int v4[]={1,-1};
    int v5[]={1,0,1,2,1,2,2,2,-1};

    assert(sumMatch(v1) != 0);
    assert(sumMatch(v2) != 0);
    assert(sumMatch(v3) != 0);
    assert(sumMatch(v4) != 0);
    assert(sumMatch(v5) != 0);
}

int main(void) {
    test_should_return_zero();
    test_should_return_non_zero();
    puts("OK!");
    return 0;
}
