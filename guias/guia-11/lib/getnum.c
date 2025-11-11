#include <stdio.h>
#include "getnum.h"
#include <string.h>

#define BORRA_BUFFER while (getchar() != '\n')

/* lee un entero */
int 
getint(const char mensaje[], ... )
{
	int n, salir = 0;
	va_list ap;
		
	do	
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		if ( scanf("%d",&n) != 1)
		{
			printf("\nDato incorrecto\n");
			BORRA_BUFFER;
		}
		else
			salir = 1;
	} while (! salir);
	BORRA_BUFFER;
	return n;
}

long 
getlong(const char mensaje[], ... )
{
	long n;
	int salir = 0;
	va_list ap;
		
	do	
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		if ( scanf("%ld",&n) != 1)
		{
			printf("\nDato incorrecto\n");
			BORRA_BUFFER;
		}
		else
			salir = 1;
	} while (! salir);
	BORRA_BUFFER;
	return n;
}

/* lee un float */
float 
getfloat(const char mensaje[], ...)
{
	float n;
	int salir = 0;
	va_list ap;
		
	do	
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		if ( scanf("%g",&n) != 1)
		{
			printf("\nDato incorrecto\n");
			BORRA_BUFFER;
		}
		else
			salir = 1;
	} while (! salir);
	BORRA_BUFFER;
	return n;
}

/* lee un double */
double 
getdouble(const char mensaje[], ...)
{
	double n;
	int salir = 0;
	va_list ap;
		
	do	
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		if ( scanf("%lg",&n) != 1)
		{
			printf("\nDato incorrecto\n");
			BORRA_BUFFER;
		}
		else
			salir = 1;
	} while (! salir);
	BORRA_BUFFER;
	return n;
}

/* lee S,s,N, o n  */
int 
yesNo(const char mensaje[], ...)
{
	int op;
	int salir = 0;
	va_list ap;
		
	do	
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		op = getchar();
		if ( strchr("SsNn", op) == NULL)
		{
			printf("\nDato incorrecto\n");
			if (op != '\n')
				BORRA_BUFFER;
		}
		else
			salir = 1;
	} while (! salir);
	BORRA_BUFFER;
	return strchr("Ss", op) != NULL;
}
