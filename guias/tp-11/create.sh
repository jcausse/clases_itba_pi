if [ $# -ne 1 ]; then
    echo "Usage: ./create <number>"
    exit 1
fi

if [ -d "ej$1" ]; then
    echo "Directory exists."
    exit 1
fi

# Directory
mkdir -p ej$1
cd ej$1

# .c
echo "#include \"ej$1.h\"" > ej$1.c
echo "#include <stdlib.h>" >> ej$1.c
echo "" >> ej$1.c

# .h
echo "#ifndef EJ_$1_H" > ej$1.h
echo "#define EJ_$1_H" >> ej$1.h
printf "\n\n\n" >> ej$1.h
echo "#endif // EJ_$1_H" >> ej$1.h

# test
echo "#include \"ej$1.h\"" > ej$1_test.c
echo "#include <stdio.h>" >> ej$1_test.c
echo "#include <stdlib.h>" >> ej$1_test.c
echo "#include <assert.h>" >> ej$1_test.c
echo "" >> ej$1_test.c

# Makefile
echo "CC := gcc" > Makefile
echo "CFLAGS := -Wall -Wextra -pedantic -std=c23 -g -fsanitize=address" >> Makefile
echo "" >> Makefile
echo "ej$1: ej$1.c ej$1.h ej$1_test.c" >> Makefile
echo "	\$(CC) \$(CFLAGS) -o ej$1 ej$1.c ej$1_test.c" >> Makefile
echo "" >> Makefile
echo "clean:" >> Makefile
echo "	rm ej$1" >> Makefile
