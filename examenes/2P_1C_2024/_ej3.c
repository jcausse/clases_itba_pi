#include <stdlib.h>

#define BLOCK 5

typedef int elemType;

typedef struct Node {
    elemType elem;
    struct Node * next;
} Node;

struct dataCDT {
    Node * first;
    size_t size;
};

typedef struct dataCDT * dataADT;

int filterFn (elemType n) {
    return 1;
}

elemType * elems(const dataADT data, int (*filter) (elemType), size_t * dim) {
    if (filter == NULL || dim == NULL) {
        return NULL;
    }
    elemType * ret = NULL;
    size_t count = 0;
    Node * currentNode = data->first;
    while (currentNode != NULL) {
        if (filter(currentNode->elem)) {
            if (count % BLOCK == 0) {
                ret = realloc(ret, (count + BLOCK) * sizeof(elemType));
            }
            ret[count] = currentNode->elem;
            count++;
        }
        currentNode = currentNode->next;
    }

    *dim = count;
    return ret;
}
