# Examenes

Parciales y recuperatorios tomados en cuatrimestres anteriores, en su mayoría resueltos.

## Organización

La nomenclatura es `<1P | 1R | 2P | 2R>_<año>_<cuatrimestre>`, donde `1` es primer, `2` es segundo, `P` es parcial y `R` es recuperatorio.

Para cada examen resuelto, encontrarán:
- `README.md`: Contiene información y/o comentarios sobre cada examen, si fuera necesario. Además contiene un listado de los ejercicios con su estado, que puede ser:
    - `OK`: Ese ejercicio está resuelto y los test pasan.
    - `Revisar`: Ejercicio a medio resolver (normalmente, por falta de tiempo). Es posible que los test no pasen.
    - `Sin test`: Ejercicio resuelto, pero no tiene test.
    - `Falta`: Ejercicio aún no resuelto.
- `Makefile`: Un archivo pensado para utilizar `make` para automatizar la compilación de los ejercicios.
- Enunciado en un archivo `.pdf`.
- Archivos `.c` o carpetas con los ejercicios resueltos. La nomenclatura es `ejX` donde `X` es el número de ejercicio.

## Makefiles

En la carpeta de cada examen se encuentra un `Makefile` que automatiza la compilación de los ejercicios sin tener que escribir la línea de compilación con `GCC` de forma manual. Requiere el programa `make` instalado.

- Para compilar un determinado ejercicio, usar `make ejX` donde `X` es el número de ejercicio.
- Para eliminar archivos temporales resultantes de la compilación, usar `make clean`.
