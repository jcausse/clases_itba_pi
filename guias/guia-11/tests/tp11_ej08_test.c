#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tp11_ej08.h" 

/* Utilizamos char * como elemType y strcmp como compare */
int main(void) {
	setADT set1 = newSet(strcmp);
	setADT set2 = newSet(strcmp);
	setADT ans;
	int ok;
	ok = addElement( set1, "amelia" );
	assert( ok && setContains( set1, "amelia" ) );
	ok = addElement( set1, "amelia" );
	assert( ok == 0 );
	addElement( set1, "belen" );
	addElement( set1, "carlos" ); // set1 = {"amelia", "belen", "carlos"}
	addElement( set2, "carlos" );
	addElement( set2, "daniel" );
	addElement( set2, "emilia" ); // set2 = {"carlos", "daniel", "emilia"}

	ans = unionSet( set1, set2 ); 
	assert( setContains(ans, "amelia") && setContains(ans, "daniel"));
	freeSet(ans);

	ans = intersectionSet( set1, set2 );
	assert( setContains(ans, "carlos") && setContains(ans, "amelia") == 0 );
	freeSet(ans);

	ans = diffSet( set1, set2 );
	assert( setContains(ans, "amelia") && setContains(ans, "carlos") == 0 );
	freeSet(ans);

	deleteElement( set1, "carlos" );
	ans = intersectionSet(set1, set2);
	assert( isEmptySet(ans) );

	freeSet(set1);
	freeSet(set2);
	freeSet(ans);
	
	// test con conjuntos de un elemento
	set1 = newSet(strcmp);
	set2 = newSet(strcmp);
	ok = addElement( set1, "amelia" );
	ok = addElement( set2, "amelia" );
	ans = intersectionSet( set1, set2 );
	assert( setContains(ans, "amelia") == 1 );
	assert(sizeSet(ans)==1);
	freeSet(ans);
	
	ans = unionSet( set1, set2 );
	assert( setContains(ans, "amelia") == 1 );
	assert(sizeSet(ans)==1);
	freeSet(ans);

    // Diferencia de un conjunto con un solo elemento
	freeSet(set2);
	set2 = newSet(strcmp);
	ans = diffSet( set1, set2 );
	assert(sizeSet(ans)==1);

    freeSet(ans);
    freeSet(set1);
	freeSet(set2);
	
	puts("OK!");
}
