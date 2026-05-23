#ifndef __bstADT_h_
#define __bstADT_h_

typedef int elemType;
static int compare (elemType elem1, elemType elem2) {
   return elem1 - elem2;
}

typedef struct bstCDT * bstADT;

// Crea un arbol binario de busqueda
bstADT newBst(void);

// Libera toda la memoria reservada por el TAD
void freeBst(bstADT bst);

// Cantidad de nodos en el arbol
unsigned int size(const bstADT bst);

// Devuelve la altura del arbol (la longitud de la rama mas larga)
// Un arbol vacio tiene altura 0
unsigned int height(const bstADT bst);

// Retorna 1 si el elemento estaก en el arbol, cero si no esta
int belongs(const bstADT bst, elemType elem);

// Agrega un elemento respetando el orden
// Retorna 1 si lo pudo agregar (no estaba), cero si no (ya estaba)
int insert(bstADT bst, elemType elem);

// Retorna un vector con los elementos almacenados de acuerdo a un recorrido inorder
// La cantidad de elementos del vector esta dada por la funcion size
elemType * inorder(const bstADT bst);

// TODO: borrar un elemento, recorrido preorder, postorder
// Mas avanzado aun: verificar si es balanceado por altura o no, crear iteradores inorder, preorder, postorder


#endif
