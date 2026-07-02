#include "ej1.h"
#include <stdlib.h>
#include <string.h>     // strdup
#include <strings.h>    // strcasecmp

#define INDEX(b) ((b) / 10 - 1)

/* Vector dinamico de listas */
/* Cada elemento del vector dinamico es una sucursal de la cadena */
/* Cada elemento de la lista es un libro */

/* Lista de libros */
typedef struct Book {
    struct bookData data;
    struct Book * next;
} Book;

typedef struct {            // Indica si esta branch ya fue inicializada o no
    bool created;

    /* Lista de libros */
    Book * firstBook;       // Lista de libros de esa sucursal
    
    /* Iterador */
    Book * iterator;        // Iterador de la sucursal

    /* Datos computados */
    size_t totalStock;      // Stock total de la sucursal (sumatoria de stocks de todos sus libros)
    size_t bookCount;       // Cantidad de libros diferentes de la sucursal (la longitud de la lista)
} Branch;

struct libraryCDT {
    Branch * branches;
    size_t size;
};

/**************************************************/
// Funciones helper

/**
 * @brief   Returns whether a branch number is valid for the library or not
 * 
 * @param[in] l                 Library ADT
 * @param[in] b                 Branch number (10, 20, 30, ..., 130, ...), 0 es invalido
 * @param[in] shouldExist       When set true, the branch must exist to be considered valid
 * 
 * @returns Boolean indicating result
 */
static bool isValidBranch(libraryADT l, size_t b, bool shouldExist) {
    if (b == 0 || b % 10 != 0) {
        return false;
    }

    size_t index = INDEX(b);
    if (shouldExist && (index >= l->size || (! l->branches[index].created))) {
        return false;
    }

    return true;
}

/**************************************************/

 
libraryADT newLibrary(void) {
    return calloc(1, sizeof(struct libraryCDT));
}

static void freeList(Book * l) {
    if (l == NULL) {
        return;
    }
    freeList(l->next);
    free(l->data.title);    // Porque en addBook duplico el string a la hora de insertar un nuevo libro
    free(l);
}

void freeLibrary(libraryADT lib) {
    for (size_t i = 0; i < lib->size; i++) {
        if (lib->branches[i].created) {
            freeList(lib->branches[i].firstBook);
        }
    }
    free(lib->branches);
    free(lib);
}

static void ensureBranchExists(libraryADT l, size_t targetIndex) {
    if (targetIndex < l->size) {
        l->branches[targetIndex].created = true;
    }
    else {
        l->branches = realloc(l->branches, (targetIndex + 1) * sizeof(Branch));
        for (size_t i = l->size; i <= targetIndex; i++) {
            l->branches[i].created = false;
            l->branches[i].firstBook = NULL;
            l->branches[i].iterator = NULL;
            l->branches[i].bookCount = 0;
            l->branches[i].totalStock = 0;
        }
        l->branches[targetIndex].created = true;
        l->size = targetIndex + 1;
    }
}

static Book * insertBookToList(Book * l, const char * title, unsigned int stock, size_t * newStock, bool * isNewBook) {
    int c;

    /* Caso Base 1: Debo agregar el libro, ya sea en el medio o al final */
    if (l == NULL || (c = strcasecmp(l->data.title, title)) > 0) {
        Book * newBook = malloc(sizeof(Book));
        newBook->data.title = strdup(title);
        newBook->data.stock = stock;
        newBook->next = l;
        *newStock = stock;
        *isNewBook = true;
        return newBook;
    }

    /* Caso Base 2: El libro ya existe, le agrego al stock */
    if (c == 0) {
        l->data.stock += stock;
        *newStock = l->data.stock;
        *isNewBook = false;
        return l;
    }

    /* Caso General: Sigo buscando */
    l->next = insertBookToList(l->next, title, stock, newStock, isNewBook);
    return l;
}

size_t addBook(libraryADT lib, size_t branch, const char * title, unsigned int stock) {
    if (! isValidBranch(lib, branch, false)) {
        return 0;
    }
    size_t index = INDEX(branch), ret;
    bool isNewBook;

    ensureBranchExists(lib, index);
    lib->branches[index].firstBook = insertBookToList(lib->branches[index].firstBook, title, stock, &ret, &isNewBook);

    lib->branches[index].totalStock += stock;
    if (isNewBook) {
        lib->branches[index].bookCount += 1;
    }

    return ret;
}

size_t books(const libraryADT lib, size_t branch) {
    return isValidBranch(lib, branch, true) ? lib->branches[INDEX(branch)].bookCount : 0;
}
 
size_t stock(const libraryADT lib, size_t branch) {
    return isValidBranch(lib, branch, true) ? lib->branches[INDEX(branch)].totalStock : 0;
}
 
void toBeginByBranch(libraryADT lib, size_t branch) {
    if (isValidBranch(lib, branch, true)) {
        lib->branches[INDEX(branch)].iterator = lib->branches[INDEX(branch)].firstBook;
    }
}
 
int hasNext(const libraryADT lib, size_t branch) {
    if (isValidBranch(lib, branch, true)) {
        return lib->branches[INDEX(branch)].iterator != NULL;
    }
    return 0;
}
 
struct bookData next(libraryADT lib, size_t branch) {
    /* Aborta por branch no valida */
    if (! isValidBranch(lib, branch, true)) {
        exit(1);
    }
    
    /* Aborta si hasNext() devolvio 0 e igual se llamo a next */
    if (lib->branches[INDEX(branch)].iterator == NULL) {
        exit(1);
    }

    /* Genero una copia de la data de ese libro */
    struct bookData ret = {
        .stock = lib->branches[INDEX(branch)].iterator->data.stock,
        .title = strdup(lib->branches[INDEX(branch)].iterator->data.title)
    };

    /* Avanzo el iterador */
    lib->branches[INDEX(branch)].iterator = lib->branches[INDEX(branch)].iterator->next;

    return ret;
}
