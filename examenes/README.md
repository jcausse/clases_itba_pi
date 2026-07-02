# Examenes

Parciales y recuperatorios tomados en cuatrimestres anteriores, en su mayoría resueltos.

Muchos de los exámenes (especialmente los primeros parciales, que suelen no tener tests completos en los enunciados) tienen tests añadidos por mí. La mayoría tienen tests son extraidos de los enunciados (si los hay). La idea es que cada ejercicio tenga su test preparado para que los puedan copiar y usar para probar su propio código a la hora de resolverlos por su cuenta.

Ante cualquier duda, sugerencia o comentario, se agradecerá [enviar un mail](mailto:jcausse@itba.edu.ar).

## Organización

Los exámenes están divididos según su tipo:

* [Primeros Parciales](https://github.com/jcausse/clases_itba_pi/tree/main/examenes/primeros_parciales)
* [Primeros Recuperatorios](https://github.com/jcausse/clases_itba_pi/tree/main/examenes/primeros_recuperatorios)
* [Segundos Parciales](https://github.com/jcausse/clases_itba_pi/tree/main/examenes/segundos_parciales)
* [Segundos Recuperatorios](https://github.com/jcausse/clases_itba_pi/tree/main/examenes/segundos_recuperatorios)

La nomenclatura dentro de cada carpeta es `<año>_<cuatrimestre>`, donde `1C` es primer cuatrimestre y `2C` es segundo cuatrimestre.

Dentro de cada sub-carpeta encontrarán:

* Enunciado en un archivo `.pdf`.
* Archivos `.c` (en primeros exámenes) o carpetas (en segundos exámenes) con los ejercicios resueltos. La nomenclatura es `ejX` donde `X` es el número de ejercicio.
* Archivo `README.md`. Ver sección [READMEs](#readmes).
* Archivo(s) `Makefile` Ver sección [Uso de los Makefiles](#uso-de-los-makefiles).

## READMEs

Para cada examen subido, encontrarán un archivo `README.md` que contiene información y/o comentarios sobre cada examen, si fuera necesario. 

Además contiene un listado de los ejercicios con su estado, que puede ser:
    * `OK`: Ese ejercicio está resuelto y los test pasan.
    * `Falta`: Ejercicio aún no resuelto.
    * `TODO`: Ese ejercicio tiene algún faltante en la resolución, normalmente por falta de tiempo.

## Uso de los Makefiles

En la carpeta de cada examen se encuentra uno (en primeros exámenes) o varios (en segundos exámenes) archivos `Makefile` que automatizan la compilación de los ejercicios sin tener que escribir la línea de compilación con `gcc` de forma manual. 

Requiere el programa [`make`](https://man7.org/linux/man-pages/man1/make.1.html) instalado, que normalmente se incluye con varias distribuciones de Linux.

* Para primeros parciales y recuperatorios:
    * Para compilar un determinado ejercicio, usar `make ejX` donde `X` es el número de ejercicio.
    * Para eliminar archivos temporales resultantes de la compilación, usar `make clean`.
    
* Para segundos parciales y recuperatorios:
    * Posicionar la terminal en la carpeta correspondiente al ejercicio deseado.
    * Para compilar un determinado ejercicio, usar `make`.
    * Para eliminar archivos temporales resultantes de la compilación, usar `make clean`.
