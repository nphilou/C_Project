#!/bin/sh

echo "-> COMPILATION\n"
gcc -Wall app.c fourmido.c map.c -c -lm
gcc app.o fourmido.o map.o -o fourmidable -lm

echo "-> EXECUTION\n"
./fourmidable