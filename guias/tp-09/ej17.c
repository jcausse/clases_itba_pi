#include <stdio.h>
#include <assert.h>
#include <ctype.h>

int bienFormado(const char * s) {
    // Caso base: cadena vacía. Se considera bien formada, por lo que se devuelve 0.
    if (*s == '\0') {
        return 0;
    }

    // Llamada recursiva para procesar el resto de la cadena.
    int ret = bienFormado(s + 1);

    // Si la llamada recursiva devuelve un valor negativo, significa que ya se ha encontrado un error en el formato.
    if (ret < 0) {
        return ret;
    }

    // Si el carácter actual es un dígito, se espera que el valor devuelto por la llamada recursiva sea 0 (bien formado hasta ahora).
    // Si es así, se devuelve el valor numérico del dígito actual. Si no, se devuelve -1 para indicar un error en el formato.
    if (isdigit(*s)) {
        return ret == 0 ? *s - '0' : -1;
    }

    // Si el carácter actual es una letra, se espera que el valor devuelto por la llamada recursiva sea un valor positivo.
    // Si es así, se descuenta la letra actual.
    // Si ret fuese cero, se devolvería -1, y la anterior llamada recibirá que hubo un error de formato.
    if (isalpha(*s)) {
        return ret - 1;
    }

    // Si el carácter actual no es ni un dígito ni una letra, se devuelve -1 para indicar un error en el formato.
    return -1;
}

void run_tests(size_t dim, const char * arr[dim], bool returns_zero) {
    for(size_t i = 0; i < dim; i++) {
        printf("Testing: %s\n", arr[i]);
        if (returns_zero) {
            assert(bienFormado(arr[i]) == 0);
        } else {
            assert(bienFormado(arr[i]) != 0);
        }
    }
}

int main(void) {
    const char * zero[] = {"abcd4a10bb2", "", "0000", "a1", "abc3", "0a1"};
    const char * not_zero[] = { "a", "1", "a2", "abc2", "abc4", "abc33", "0123", "2aa", "$1", "@@2", "abcd22", "@@"};

    run_tests(sizeof(zero) / sizeof(zero[0]), zero, true);
    run_tests(sizeof(not_zero) / sizeof(not_zero[0]), not_zero, false);

    puts("OK!");
    return 0;
}
