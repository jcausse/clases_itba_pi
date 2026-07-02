#include <stdio.h> 

// Nota: compilar con -Wno-incompatible-pointer-types ya que, de otra forma, el compilador
//       dara error al compilar pues las dimensiones de las matrices de origen y recibidas por
//       la funcion no coinciden.
 
void imprimeFila(int mat[3][4], unsigned int fila) { 
    for(int i = 0; i < 4 ; i++) 
        printf("%d ", mat[fila][i]); 
    putchar('\n'); 
}
 
int main(void) { 
    int m[][3] ={ 
        {1,2,3},
        {4,5,6}, 
        {7,8,9},
        {10,11,12},                
        {13,14,15},
        {16}, 
        {17}, 
        {18,19} 
    };

    // Ver explicacion mas abajo

    imprimeFila(m, 0);  // 1 2 3 4
    imprimeFila(m, 2);  // 9 10 11 12
    imprimeFila(m, 4);  // 0 0 17 0
    
    return 0; 
}

/*
    EXPLICACION:

    Cuando la funcion recibe la matriz, lo que recibe en realidad es una direccion de memoria
    del inicio de la matriz (1er elemento de la 1ra fila).

    La informacion "mat[3][4]" que recibe la funcion, en realidad no es del todo necesaria. El
    compilador necesita el [4] (ya que es obligatorio especificar todas las dimensiones de los
    arreglos multidimensionales excepto la primera), pero no el [3] (por la misma razon).

    Cuando se haga mat[fila], la funcion cree que la matriz tiene 4 filas en lugar de 3, entonces,
    la cuenta que hace el compilador para acceder a la fila "fila" y columna "i" es:

                    dir_destino = mat + sizeof(int) * 4 * fila + sizeof(int) * i

    (1): Al estar todas las filas consecutivas en la memoria, la funcion interpreta a la primera fila
    como {1, 2, 3, 4}, la segunda como {5, 6, 7, 8}, y asi sucesivamente.

    (2): Ademas, al declarar la matriz en main(), le faltan algunos elementos. El compilador, cuando
    inicializo algunos elementos pero no todos, a todos los restantes les asigna un cero. De esta
    manera, es como si la matriz original fuese:

    int m[][3] ={ 
        {1,2,3},
        {4,5,6}, 
        {7,8,9},
        {10,11,12},                
        {13,14,15},
        {16, 0, 0}, 
        {17, 0, 0}, 
        {18,19, 0} 
    };

    Debido a lo dicho en (1) y en (2), la funcion interpreta la matriz como si fuese:

    int m[][4] ={ 
        {1,2,3,4},
        {5,6,7,8}, 
        {9,10,11,12},                
        {13,14,15,16},
        {0,0,17,0}, 
        {0,18,19,0} 
    };

    Finalmente:
    -> imprimeFila(m, 0) imprime "1 2 3 4"
    -> imprimeFila(m, 2) imprime "9 10 11 12"
    -> imprimeFila(m, 4) imprime "0 0 17 0"

*/
