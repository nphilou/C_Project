#!/bin/sh

echo "-> COMPILATION\n"
gcc -Wall affichage.c plateau.c init.c combat.c deplacement.c instructions.c app.c fourmido_sdl.c -c -lm -lSDL -lSDL_image -lSDL_ttf
gcc affichage.c plateau.o init.o combat.o deplacement.o instructions.o app.o fourmido_sdl.o -o fourmidable_sdl -lm -lSDL -lSDL_image -lSDL_ttf
echo "-> EXECUTION\n"
./fourmidable_sdl