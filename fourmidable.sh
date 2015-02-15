#!/bin/sh

echo "-> COMPILATION\n"
gcc -Wall app.c fourmido.c -c -lm
gcc app.o fourmido.o -o fourmidable -lm

echo "-> EXECUTION\n"
./fourmidable