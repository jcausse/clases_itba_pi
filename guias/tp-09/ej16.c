#include <stdio.h>
#include <assert.h>

#define END -1                  // Terminador

#define ORDER_ASC       1       // Ascendente
#define ORDER_DESC      -1      // Descendente
#define ORDER_UNKNOWN   0       // Desconocido

/*
Casos Base:
- Caso 1: El elemento actual (*arr) es el terminador ---> Array vacio ---> ORDER_UNKNOWN
- Caso 2: El elemento actual (*arr) no es el terminador pero el siguiente (*(arr + 1)) si 
          ---> Array con 1 solo elemento ---> ORDER_UNKNOWN
- Caso 3: Caso 1 y Caso 2 no se dieron, pero el subsiguiente del actual (*(arr + 2)) es el
          terminador ---> El elemento actual debe establecer el orden que los demas casos
          deben verificar que se cumpla ---> ORDER_ASC u ORDER_DESC

Observacion: Solo caigo en los Casos Base 1 y 2 si el arreglo era vacio o tenia un solo
             elemento desde un comienzo. Si tengo al menos dos elementos, siempre voy a
             caer en el Caso Base 3 antes que logre avanzar lo suficiente como para caer
             en el 1 o en el 2

Caso General:
Avanzo hasta el ante-ultimo elemento. Luego, al volver hacia atras, chequeo que el orden 
relativo entre el elemento actual y su siguiente coincida con el devuelto por la instancia 
siguiente de la funcion.
- Si coinciden ---> Devuelvo el mismo valor que recibi
- Si no coinciden ---> ORDER_UNKNOWN
*/

int orden(const int * arr) {
    // Casos Base 1 y 2
    if (*arr == END || *(arr + 1) == END) {
        return ORDER_UNKNOWN;
    }

    /**
     * Siendo que ni el actual ni el siguiente son el terminador, calculo actual - siguiente:
     * Positivo ---> actual - siguiente > 0 ---> actual > siguiente ---> ORDER_DESC
     * Negativo ---> actual - siguiente < 0 ---> actual < siguiente ---> ORDER_ASC
     * Cero -------> actual - siguiente = 0 ---> actual = siguiente ---> ORDER_UNKNOWN
     */
    int cmp = *arr - *(arr + 1);
    int ord = cmp == 0 ? ORDER_UNKNOWN : (cmp > 0 ? ORDER_DESC : ORDER_ASC);
    
    // Caso Base 3
    if (*(arr + 2) == END) {
        return ord;
    }

    // Caso general
    int ret = orden(arr + 1);
    return ord == ret ? ret : ORDER_UNKNOWN;
}

int main(void) {
    int v[] = {2, 1, 2, 8, 20, 12343, -1}; 
    int v2[] = {10, 10, 9, 5, 3, -1}; 
    
    assert(orden(v) == ORDER_UNKNOWN);
    assert(orden(v + 1) == ORDER_ASC);
    assert(orden(v2) == ORDER_UNKNOWN);
    assert(orden(v2 + 1) == ORDER_DESC);
    assert(orden(v2 + 4) == ORDER_UNKNOWN);

    puts("OK!");
    return 0;
}
