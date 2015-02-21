#!/bin/sh

echo "-> COMPILATION\n"
gcc -Wall plateau.c init.c app.c fourmido.c -c -lm
gcc plateau.o init.o app.o fourmido.o -o fourmidable -lm

echo "-> EXECUTION\n"
./fourmidable