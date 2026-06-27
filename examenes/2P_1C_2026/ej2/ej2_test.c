#include <stdio.h>
#include <assert.h>
#include "ej2.h"

unsigned char randIntTest(unsigned char min, unsigned char max) {
    static unsigned char SEQUENCE[] = {2, 5, 5, 3, 5, 2, 1, 10, 8, 2, 8, 8, 8, 8, 5};
    static size_t i = 0;
    unsigned char randNum = SEQUENCE[i];
    i++;
    return randNum;
}

int main(void) {
    randomADT adt = newRandomADT(10);
    assert(adt != NULL);
    assert(numbers(adt) == 0);
    assert(mostFrequent(adt) == -1);

    newRandom(adt);                             // 2
    assert(numbers(adt) == 1);
    assert(mostFrequent(adt) == 2);

    newRandoms(adt, 4);                         // 5, 5, 3, 5
    assert(numbers(adt) == 3);                  // 2, 5, 3
    assert(mostFrequent(adt) == 5);             // 5 is most frequent (3 times)

    newRandoms(adt, 10);                        // 2, 1, 10, 8, 2, 8, 8, 8, 8, 5
                                                // Now sequence is exhausted (15 elements total)
    assert(numbers(adt) == 6);                  // 5, 2, 3, 1, 10, 8
    assert(mostFrequent(adt) == 8);             // 8 appears 5 times

    freeRandomADT(adt);

    // Test with maxValue = 0
    assert(newRandomADT(0) == NULL);

    puts("OK!");
    return 0;
}
