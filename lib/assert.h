#include <stdio.h>

#undef assert
/*
#define assert(expr) \
  if (!(expr)) { \
          fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d\n", #expr, __func__, __FILE__, __LINE__); \
      exit(EXIT_FAILURE); \
    }
*/

// La version anterior puede fallar si el assert se usa dentro de un if-else y en el if hay una proposición simple, por ejemplo
// if ()
//  assert()
// else
//
// ya que el else quedaría asociado al if del assert, y no es la intención del programador.
// Si bien no queda muy elegante, una forma segura de hacerlo es la siguiente
// (en esta version sacamos el exit)


#define assert(expr) \
  if (expr) { \
  }     \
  else { \
      fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d\n", #expr, __func__, __FILE__, __LINE__); \
   }
