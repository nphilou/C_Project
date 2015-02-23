#!/bin/sh

echo "-> COMPILATION\n"
gcc -Wall plateau.c init.c combat.c deplacement.c instructions.c app.c fourmido.c -c -lm
gcc plateau.o init.o combat.o deplacement.o instructions.o app.o fourmido.o -o fourmidable -lm
echo "-> EXECUTION\n"
./fourmidable