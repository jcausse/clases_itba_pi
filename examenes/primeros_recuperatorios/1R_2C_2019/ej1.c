#include <stdio.h>
#include <string.h>
#include <assert.h>

void contar_apariciones(unsigned char s[], unsigned char ap[256]) {
    unsigned int i = 0;
    while(s[i] != '\0') {
        ap[s[i]]++;
        i++;
    }
}

void elimina(unsigned char s[]) {
    unsigned char apariciones[256] = {0};
    contar_apariciones(s, apariciones);

    unsigned int read = 0, write = 0;
    while(s[read] != '\0') {
        if (apariciones[s[read]] == 1) {    // Ultima aparicion: Cuando el vector de apariciones tiene un 1 -> ahora lo copio
            s[write] = s[read];             // Lo copio (es seguro pq read siempre esta delante de write)
            write++;                        // Se incrementa write solo al copiar
        }
        apariciones[s[read]]--;             // Se decrementa una aparicion SIEMPRE (si habia mas de 1, eventualmente llega a 1)
        read++;
    }

    s[write] = '\0';
}

int main(void) {
    unsigned char s[] = "abcbc.cba"; 
    elimina(s);
    assert(strcmp((const char *) s, ".cba") == 0); 
    
    unsigned char t[] = "123456654321"; 
    elimina(t);
    assert(strcmp((const char *) t, "654321") == 0);
    elimina(t); // t no cambia
    assert(strcmp((const char *) t, "654321") == 0);
    
    unsigned char u[] = "Abc123aBC"; 
    elimina(u); // u no cambia
    assert(strcmp((const char *) u, "Abc123aBC") == 0);
 
    unsigned char w[] = "";
    elimina(w);
    assert(strcmp((const char *) w, "") == 0);

    puts("OK!");
    return 0;
}
