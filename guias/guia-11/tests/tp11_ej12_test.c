#include "tp11_ej12.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

int main (void) {
	socialADT soc = newSocial();
	char ** rel;
	rel = persons(soc); // rel = {NULL}
	assert( rel[0] == 0 );
	free(rel);

	rel = related(soc, "carlitos"); // rel = {NULL};
	assert( rel[0] == NULL );
	free(rel);

	char aux[30] = "juan";
	addPerson(soc, aux); // soc contiene a "juan"
	strcpy(aux,"luisa");
	addPerson(soc, aux); // soc contiene a "juan" y "luisa"
	strcpy(aux,"ana");
	addRelated(soc, "juan", "pedro");
	addRelated(soc, "juan", aux);
	addRelated(soc, "juan", "juana");
	char ** juanFriends = related(soc, "juan"); // juanFriends es {"ana", "juana", "pedro", NULL};
	assert( !strcmp(juanFriends[0], "ana") && !strcmp(juanFriends[1], "juana"));
	assert( !strcmp(juanFriends[2], "pedro") && juanFriends[3] == NULL );
	for(int i=0; juanFriends[i] != NULL; i++)
		free(juanFriends[i]);
	free(juanFriends);

	addPerson(soc, "andres");
	addPerson(soc, "analia");
	char **p = persons(soc); // p={"analia","andres","juan","luisa",NULL}
	assert( !strcmp(p[0], "analia") && !strcmp(p[1], "andres"));
	assert( !strcmp(p[2], "juan") && !strcmp(p[3], "luisa") && p[4] == NULL );
	for(int i=0; p[i] != NULL; i++)
		free(p[i]);
	free(p);

	addRelated(soc, "juan", "john"); // Ahora los amigos de juan son "ana", "john", "juana" y "pedro"
	addRelated(soc, "juan", "john"); // Ahora los amigos de juan son "ana", "john", "john", juana" y "pedro"
	juanFriends = related( soc, "juan" );
	assert( !strcmp(juanFriends[0], "ana") && !strcmp(juanFriends[1], "john") && !strcmp(juanFriends[2], "john"));
	assert( !strcmp(juanFriends[3], "juana") && !strcmp(juanFriends[4], "pedro") && juanFriends[5] == NULL);
	for(int i=0; juanFriends[i] != NULL; i++)
		free(juanFriends[i]);
	free(juanFriends);

	freeSocial(soc);
	puts("OK!");
	
	// El enunciado decía que a lo sumo eran 20 chars lo que tenía cada nombre
	// Pero si el TAD aplica programación defensiva no debería causar problemas el pasarle un
	// nombre de mayor longitud, a lo sumo podría cortarlo.
    soc = newSocial();	
    addPerson(soc, "012345678901234567890123456789");
    p = persons(soc);
    assert(!strncmp(p[0],"01234567890123456789", 20 ));
    for(int i=0; p[i] != NULL; i++)
		free(p[i]);
	free(p);
    freeSocial(soc);

	puts("Great!");
	return 0;
}