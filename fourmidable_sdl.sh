#!/bin/sh

echo "-> COMPILATION\n"
gcc -Wall plateau.c init.c combat.c deplacement.c instructions.c app.c fourmido_sdl.c -c -lm -lSDL -lSDL_image
gcc plateau.o init.o combat.o deplacement.o instructions.o app.o fourmido_sdl.o -o fourmidable_sdl -lm -lSDL -lSDL_image
echo "-> EXECUTION\n"
./fourmidable_sdl