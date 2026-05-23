#ifndef __utillist__h
#define __utillist__h

typedef struct node * List; 

typedef struct node {
	int head;
	struct node * tail;
} TNode;


/*
** Funcion auxiliar para crear listas y poder testear las funciones
** Dado un vector, retorna una lista con sus elementos, en el mismo orden
*/
List fromArray(const int v[], unsigned int dim );

/*
** Funcion auxiliar para verificar los elementos de una lista
** Retorna 1 si la lista y el vector contienen los mismos elementos en el mismo orden
*/
int checkElems(const List list, const int v[], int dim);

/*
** Libera todos los nodos de la lista
*/
void freeList(List list);
#endif
