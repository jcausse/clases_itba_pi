#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ej3.h"

static TList fromArray(const int v[], size_t dim) {
    TList ans = NULL;
    while (dim > 0) {
        TList aux = malloc(sizeof(node));
        aux->head = v[--dim];
        aux->tail = ans;
        ans = aux;
    }
    return ans;
}

static int checkElems(const TList list, const int v[], size_t dim) {
    size_t i;
    TList aux;
    for (i = 0, aux = list; i < dim && aux != NULL; i++, aux = aux->tail) {
        if (aux->head != v[i]) {
            return 0;
        }
    }
    return aux == NULL && i == dim;
}

static void freeList(TList list) {
    if (list == NULL) {
        return;
    }
    freeList(list->tail);
    free(list);
}

int main(void) {
    int count;

    // --- Ejemplos del enunciado del parcial ---

    // Ejemplo 1: 2 -> 5 -> 1 -> 5 -> 4 -> 5 -> 7 y value es 5
    // Resultado esperado: 2 -> 1 -> 4 -> 7, *count = 3
    {
        int v[] = {2, 5, 1, 5, 4, 5, 7};
        int expected[] = {2, 1, 4, 7};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        l = deleteAll(l, 5, &count);
        assert(count == 3);
        assert(checkElems(l, expected, sizeof(expected) / sizeof(expected[0])));
        freeList(l);
    }

    // Ejemplo 2: 2 -> 85 -> 1 -> 15 -> 4 -> 8 -> 7 y value es 5
    // Resultado esperado: queda igual, *count = 0
    {
        int v[] = {2, 85, 1, 15, 4, 8, 7};
        int expected[] = {2, 85, 1, 15, 4, 8, 7};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        count = 999; // aseguramos que sobreescribe valor previo
        l = deleteAll(l, 5, &count);
        assert(count == 0);
        assert(checkElems(l, expected, sizeof(expected) / sizeof(expected[0])));
        freeList(l);
    }

    // Ejemplo 3: lista vacía
    // Resultado esperado: vacía, *count = 0
    {
        TList l = NULL;
        count = -123;
        l = deleteAll(l, 5, &count);
        assert(l == NULL);
        assert(count == 0);
    }

    // Ejemplo 4: 5 -> 2 -> 1 -> 5 -> 5 -> 4 -> 8 -> 7 -> 5 y value es 5
    // Resultado esperado: 2 -> 1 -> 4 -> 8 -> 7, *count = 4
    {
        int v[] = {5, 2, 1, 5, 5, 4, 8, 7, 5};
        int expected[] = {2, 1, 4, 8, 7};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        l = deleteAll(l, 5, &count);
        assert(count == 4);
        assert(checkElems(l, expected, sizeof(expected) / sizeof(expected[0])));
        freeList(l);
    }

    // Ejemplo 5: 5 -> 5 -> 5 y value es 5
    // Resultado esperado: vacía, *count = 3
    {
        int v[] = {5, 5, 5};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        l = deleteAll(l, 5, &count);
        assert(l == NULL);
        assert(count == 3);
    }

    // --- Casos borde adicionales ---

    // Caso 1 elemento que coincide
    {
        int v[] = {42};
        TList l = fromArray(v, 1);
        l = deleteAll(l, 42, &count);
        assert(l == NULL);
        assert(count == 1);
    }

    // Caso 1 elemento que NO coincide
    {
        int v[] = {42};
        int expected[] = {42};
        TList l = fromArray(v, 1);
        l = deleteAll(l, 10, &count);
        assert(count == 0);
        assert(checkElems(l, expected, 1));
        freeList(l);
    }

    // Elementos a eliminar solo al principio
    {
        int v[] = {7, 7, 1, 2, 3};
        int expected[] = {1, 2, 3};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        l = deleteAll(l, 7, &count);
        assert(count == 2);
        assert(checkElems(l, expected, sizeof(expected) / sizeof(expected[0])));
        freeList(l);
    }

    // Elementos a eliminar solo al final
    {
        int v[] = {1, 2, 3, 7, 7};
        int expected[] = {1, 2, 3};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        l = deleteAll(l, 7, &count);
        assert(count == 2);
        assert(checkElems(l, expected, sizeof(expected) / sizeof(expected[0])));
        freeList(l);
    }

    // Elementos a eliminar con números negativos y ceros
    {
        int v[] = {-3, 0, -3, 5, -3};
        int expected[] = {0, 5};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        l = deleteAll(l, -3, &count);
        assert(count == 3);
        assert(checkElems(l, expected, sizeof(expected) / sizeof(expected[0])));
        freeList(l);
    }

    // Eliminar ceros
    {
        int v[] = {0, 0, 0, 1, 0};
        int expected[] = {1};
        TList l = fromArray(v, sizeof(v) / sizeof(v[0]));
        l = deleteAll(l, 0, &count);
        assert(count == 4);
        assert(checkElems(l, expected, sizeof(expected) / sizeof(expected[0])));
        freeList(l);
    }

    puts("OK!");
    return 0;
}
