#include "bstADT.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(void) {
	bstADT tree = newBst();
	assert(size(tree)==0);
	assert(height(tree)==0);

	assert(insert(tree, 50)==1);
	assert(height(tree)==1);
	int * ord = inorder(tree);
	assert(ord[0]==50);
	free(ord);

	assert(insert(tree, 20)==1);
	assert(height(tree)==2);
	assert(insert(tree, 70)==1);
	assert(insert(tree, 10)==1);
	assert(insert(tree, 25)==1);

	assert(belongs(tree, 50));
	assert(belongs(tree, 20));
	assert(belongs(tree, 70));
	assert(belongs(tree, 10));
	assert(belongs(tree, 70));
	assert(!belongs(tree, 5));
	assert(!belongs(tree, -5));
	assert(!belongs(tree, 100));

	assert(size(tree)==5);
	assert(height(tree)==3);

	ord = inorder(tree);
	assert(ord[0] == 10);
	assert(ord[1] == 20);
	assert(ord[2] == 25);
	assert(ord[3] == 50);
	assert(ord[4] == 70);
	free(ord);

	freeBst(tree);

	puts("You nailed it !!!");
	return 0;
}

