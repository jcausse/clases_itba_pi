#include <stdio.h>
#include <assert.h>
#include <string.h>

#define TO_UPPERCASE(c) ((c) - 'a' + 'A')
#define WORD_SEPARATOR '_'

void snakeToCamel(char * s) {
    unsigned int read = 1;
    unsigned int write = 1;
    bool nextIsUppercase = false;

    while(s[read] != '\0') {

        // Caso 1: Separador de palabras
        if (s[read] == WORD_SEPARATOR) {
            nextIsUppercase = true;
        }

        // Caso 2: Letra y el anterior fue separador
        else if (nextIsUppercase) {
            s[write] = TO_UPPERCASE(s[read]);
            write++;
            nextIsUppercase = false;
        }

        // Caso 3: Letra y el anterior fue letra
        else {
            s[write] = s[read];
            write++;
        }

        read++;
    }

    s[write] = '\0';
}

int main(void) {
    char str1[] = "edad";
    char * result1 = "edad";
    snakeToCamel(str1);
    assert(strcmp(str1, result1) == 0);

    char str2[] = "edad_de_tu_perro_lanudo";
    char * result2 = "edadDeTuPerroLanudo";
    snakeToCamel(str2);
    assert(strcmp(str2, result2) == 0);

    char str3[] = "a_b_c_d_e";
    char * result3 = "aBCDE";
    snakeToCamel(str3);
    assert(strcmp(str3, result3) == 0);

    char str4[] = "a";
    char * result4 = "a";
    snakeToCamel(str4);
    assert(strcmp(str4, result4) == 0);
    
    char str5[] = "you_play_me_like_dun_dun_dun";
    char * result5 = "youPlayMeLikeDunDunDun";
    snakeToCamel(str5);
    assert(strcmp(str5, result5) == 0);

    char str6[] = "aqui_me_pongo_a_cantar_al_compas_de";
    char * result6 = "aquiMePongoACantarAlCompasDe";
    snakeToCamel(str6);
    assert(strcmp(str6, result6) == 0);

    puts("OK!");
    return 0;
}
