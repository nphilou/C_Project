#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "structures.h"
#include "affichage.h"
#include "init.h"
#include "instructions.h"
#include "jeu.h"


int main(int argc, char *argv[]) {

    //Initialisation SDL et SDL_ttf
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_WM_SetCaption("Fourmido", NULL);

    //Monde *monde = creationMonde();

    jeu();

    TTF_Quit();
    SDL_Quit();

    return 0;
}