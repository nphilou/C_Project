#!/bin/sh

echo "-> COMPILATION\n"
gcc -Wall affichage.c plateau.c init.c combat.c deplacement.c instructions.c app.c fourmido.c -c -lm 2> logs/compile.log 
gcc affichage.c plateau.o init.o combat.o deplacement.o instructions.o app.o fourmido.o -o fourmidable -lm 2> logs/link.log
echo "-> EXECUTION\n"
./fourmidable