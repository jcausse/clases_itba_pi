#include <stdio.h>
#include <assert.h>
#include "complexADT.h"

#define EPS 0.01

int main(void) {
    complexADT comp1 = nuevoComp( 1, 2 ); // comp1 = 1 + 2i
	complexADT comp2 = nuevoComp( 2, -3 ); // comp2 = 2 - 3i
	complexADT ans;

	ans = sumaComp( comp1, comp2 );
	assert( parteRealComp(ans) - 3 < EPS && parteImagComp(ans) + 1 < EPS );
	liberaComp( ans );

	ans = restaComp( comp1, comp2 );
	assert( parteRealComp(ans) - 1 < EPS && parteImagComp(ans) - 5 < EPS );	
	liberaComp( ans );

	ans = multiplicaComp( comp1, comp2 );
	assert( parteRealComp(ans) - 8 < EPS && parteImagComp(ans) - 1 < EPS );
	liberaComp( ans );

	ans = divideComp( comp1, comp2 );
	assert( parteRealComp(ans) + 0.31 < EPS && parteImagComp(ans) - 0.54 < EPS );
	liberaComp( ans );

	ans = conjugadoComp( comp1 );
	assert( parteRealComp(ans) - 1 < EPS && parteImagComp(ans) + 2 < EPS );

	liberaComp( comp1 );
	liberaComp( comp2 );
	liberaComp( ans );

	printf("OK!\n");
}
