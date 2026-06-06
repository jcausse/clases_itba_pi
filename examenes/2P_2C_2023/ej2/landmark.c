#include "landmark.h"

#define BLOCK 5

typedef struct {
    landmarkType landmark;
    bool occupied;
} LandmarkContainer;

struct landmarkCDT {
    LandmarkContainer * array;
    size_t arraySize;
    size_t addedLandmarks;
    landmarkTypeComparator cmp;
};

landmarkADT newLandmark(landmarkTypeComparator cmp) {
    landmarkADT ret = malloc(sizeof(struct landmarkCDT));
    ret->array = NULL;
    ret->arraySize = ret->addedLandmarks = 0;
    ret->cmp = cmp;
    return ret;
}

static void extendArrayToSize(landmarkADT landmark, size_t size) {
    // No hacer nada si el array ya tiene el espacio necesario
    if (landmark->arraySize >= size) {
        return;
    }

    // Agrandar el array
    landmark->array = realloc(landmark->array, size * sizeof(LandmarkContainer));

    // Inicializar las nuevas posiciones
    for (size_t i = landmark->arraySize; i < size; i++) {
        landmark->array[i].occupied = false;
    }
    
    // Anotar el nuevo size
    landmark->arraySize = size;
}

void addLandmark(landmarkADT landmark, size_t meters, landmarkType site) {
    size_t ix = meters / CHUNK_SIZE;
    extendArrayToSize(landmark, ix + 1);    // Extiende solo si se necesita
    landmark->array[ix].landmark = site;    // No va dentro del if porque si ya habia un landmark en ese lugar debe pisarlo
    if (!landmark->array[ix].occupied) {
        landmark->array[ix].occupied = true;
        (landmark->addedLandmarks)++;
    }
}

int hasLandmark(const landmarkADT landmark, size_t meters) {
    size_t ix = meters / CHUNK_SIZE;
    if (ix >= landmark->arraySize) {
        return 0;
    }
    return landmark->array[ix].occupied;
}

int distance(const landmarkADT landmark, landmarkType site) {
    unsigned int i = 0;
    while (i < landmark->arraySize &&
        (!landmark->array[i].occupied || landmark->cmp(landmark->array[i].landmark, site) != 0)
    ) {
        i++;
    }
    return i == landmark->arraySize ? NO_SUCH_LANDMARK : i * CHUNK_SIZE;
}

size_t landmarkCount(const landmarkADT landmark) {
    return landmark->addedLandmarks;
}

landmarkType * landmarks(const landmarkADT landmark) {
    if (landmark->addedLandmarks == 0) {
        return NULL;
    }
    landmarkType * ret = malloc(landmark->addedLandmarks * sizeof(landmarkType));
    size_t j = 0;
    for (size_t i = 0; i < landmark->arraySize; i++) {
        if (landmark->array[i].occupied) {
            ret[j] = landmark->array[i].landmark;
            j++;
        }
    }
    return ret;
}

landmarkType * landmarksBetween(const landmarkADT landmark, size_t from, size_t to, size_t *dim) {
    if (from > to || to / CHUNK_SIZE >= landmark->arraySize) {
        *dim = 0;
        return NULL;
    }

    size_t from_ix = from / CHUNK_SIZE, to_ix = to / CHUNK_SIZE;
    landmarkType * ret = NULL;
    size_t j = 0;
    for (size_t i = from_ix; i <= to_ix; i++) {
        if (landmark->array[i].occupied) {
            if (j % BLOCK == 0) {
                ret = realloc(ret, (j + BLOCK) * sizeof(landmarkType));
            }
            ret[j] = landmark->array[i].landmark;
            j++;
        }
    }

    if (ret != NULL) {
        ret = realloc(ret, j * sizeof(landmarkType));
    }
    *dim = j;
    return ret;
}

void freeLandmark(landmarkADT landmark) {
    free(landmark->array);
    free(landmark);
}
