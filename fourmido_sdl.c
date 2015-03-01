#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "structures.h"
#include "affichage.h"
#include "init.h"
#include "instructions.h"
#include "jeu.h"


int main(int argc, char *argv[]) {

    //Creation monde
    Monde *myWorld = creationMonde();

    //Initialisation SDL et SDL_ttf
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //Creation fenetre
    SDL_WM_SetCaption("Fourmido", NULL);

    affichePlateauSDL(myWorld);


/*
    int continuer = 1;
    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

    }
*/

    int premierJoueur = (int) ROUGE;
    int i = 1;
    while (i) {
        printf("((((((((((((((((TOUR ROUGE))))))))))))))))\n\n");
        tour(myWorld, myWorld->rouge, myWorld->noire);
        affichePlateauSDL(myWorld);

        printf("((((((((((((((((TOUR NOIR))))))))))))))))\n\n");
        tour(myWorld, myWorld->noire, myWorld->rouge);
        affichePlateauSDL(myWorld);

        printf("Quitter ? OUI(0), NON(1)\n");
        lireEntier(&i);
    }
    sauvegarde(myWorld, premierJoueur);

    TTF_Quit();
    SDL_Quit();

    return 0;
}