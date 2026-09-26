#include <stdio.h>
#include <assert.h>
#include <ctype.h>            // tolower(), isalpha()
#include <string.h>           // strcmp()

void eliminaConsecutivosAlfabeticos(char * s) {
   // Validaciones:
   // - s no debe ser invalido (NULL)
   // - s no debe ser vacio
   // - s no debe contener 1 solo caracter
   if (s == NULL || s[0] == '\0' || s[1] == '\0') {
      return;
   }

   unsigned int read = 1, write = 1;

   while (s[read] != '\0') {
      // Copiar si:
      // - No es una letra
      // - El anterior no es una leta
      // - Siendo las dos una letra, la actual no es consecutiva de la anterior
      if(
         !isalpha(s[read])                            ||       // No es letra, o bien
         !isalpha(s[read - 1])                        ||       // La anterior no es letra, o bien
         tolower(s[read]) != tolower(s[read - 1] + 1)          // Ambas son letras (no cumplio las ORs), pero no son consecutivas
      ) {
         s[write] = s[read];
         write++;
      }

      read++;
   }

   s[write] = '\0';
}

int main(void) { 
   char s1[] = "BcDeC PQEzA"; 
   eliminaConsecutivosAlfabeticos(s1);
   assert(!strcmp(s1, "BC PEzA"));

   char s2[] = "xyzxyzXyz"; 
   eliminaConsecutivosAlfabeticos(s2); 
   assert(!strcmp(s2, "xxX")); 
   
   char s3[] = "Hola Mundo!"; 
   eliminaConsecutivosAlfabeticos(s3); 
   assert(!strcmp(s3, "Hola Mundo!")); 
   
   char s4[] = "A"; 
   eliminaConsecutivosAlfabeticos(s4); 
   assert(!strcmp(s4, "A")); 

   char s5[] = "YZ["; 
   eliminaConsecutivosAlfabeticos(s5); 
   assert(!strcmp(s5, "Y[")); 

   char s6[] = "@ABD"; 
   eliminaConsecutivosAlfabeticos(s6); 
   assert(!strcmp(s6, "@AD")); 
   
   puts("OK!"); 
   return 0; 
}
