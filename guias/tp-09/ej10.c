#include <stdio.h>
#include <assert.h>
#include <string.h>

/*

************
*** IDEA ***
************

IDA - 1.
invierte( H O L A \0, _ _ _ _ _)
          ^          ^

IDA - 2.
invierte( H O L A \0, _ _ _ _ _)
            ^        ^

IDA - 3.
invierte( H O L A \0, _ _ _ _ _)
              ^       ^

IDA - 4.
invierte( H O L A \0, _ _ _ _ _)
                ^     ^

IDA - 5 (CASO BASE).
invierte( H O L A \0, _ _ _ _ _) devuelve 0
                  ^   ^

VUELTA - 4.
invierte( H O L A \0, A _ _ _ _) devuelve 1
                ^     ^
                      0

VUELTA - 3.
invierte( H O L A \0, A L _ _ _) devuelve 2
              ^         ^
                        1

VUELTA - 2.
invierte( H O L A \0, A L O _ _) devuelve 3
            ^             ^
                          2

VUELTA - 1.
invierte( H O L A \0, A L O H _) devuelve 4
          ^                 ^
                            3

Obs: La ultima de las vueltas devuelve el equivalente a strlen(src) = strlen(dst)

*/

size_t invierte(const char * src, char * dst) {
    if (*src == '\0') {
        return 0;
    }

    size_t ret = invierte(src + 1, dst);
    *(dst + ret) = *src;
    return ret + 1;
}

/*
// Una segunda opcion, con punteros:

char * invierte(const char * src, char * dst) {
    if (*src == '\0') {
        return dst;
    }

    dst = invierte(src + 1, dst);
    *dst = *src;
    return dst + 1;
}
*/

int main(void) {
    char s[20] = {0};
    size_t ret;
    const char * src;

    src = "1234567890";
    ret = invierte(src, s);
    assert(strcmp(s, "0987654321")==0);
    assert(strlen(src) == strlen(s) && strlen(src) == ret);
    
    memset(s, 0, 20);
    src = "";
    ret = invierte(src, s);
    assert(strcmp(s, "")==0);
    assert(strlen(src) == strlen(s) && strlen(src) == ret);
    
    memset(s, 0, 20);
    src = "a";
    ret = invierte(src, s);
    assert(strcmp(s, "a")==0);
    assert(strlen(src) == strlen(s) && strlen(src) == ret);
    
    memset(s, 0, 20);
    src = "ab";
    ret = invierte(src, s);
    assert(strcmp(s, "ba")==0);
    assert(strlen(src) == strlen(s) && strlen(src) == ret);
      
    memset(s, 0, 20);
    src = "abc";
    ret = invierte(src, s);
    assert(strcmp(s, "cba")==0);
    assert(strlen(src) == strlen(s) && strlen(src) == ret);
    
    printf ("OK!\n");
    return 0;
}
