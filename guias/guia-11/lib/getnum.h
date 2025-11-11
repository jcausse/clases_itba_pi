#include <stdarg.h>
/*
** Funciones para leer desde la entrada estandar un numero.
** Reciben como parametro una cadena de caracteres, la cual puede
** contener un formato igual al utilizado por la funcion printf.
** Imprimira en salida estandar dicha cadena antes de la lectura del numero
** En caso de escribir letras se quedan esperando hasta que
** se ingrese un numero.
** Si se ingresa un numero seguido de otros caracteres,
** devolveran el numero ignorando el resto de los caracteres
*/


#ifndef _getnum_h

#define _getnum_h

/* funcion que lee de la entrada estandar un numero entero
** Modo de uso: n = getint("Ingrese un numero entre %d y %d: ", 0, 10);
**              a = getint("");
*/
int getint(const char mensaje[], ...);

/* funcion que lee de la entrada estandar un numero entero de mayor tamaño (long)
** Modo de uso: n = getlong("Ingrese un numero entre %ld y %ld: ", 0L, 10L);
**              a = getlong("");
*/
long  getlong(const char mensaje[], ... );

/* funcion que lee de la entrada estandar un numero real
** Modo de uso: idem getint()
*/
float getfloat(const char mensaje[], ...);

/* funcion que lee de la entrada estandar un numero real de doble precision
** Modo de uso: idem getint()
*/
double getdouble(const char mensaje[], ...);


/* lee S,s,N, o n  */
int yesNo(const char mensaje[], ...);

#endif
