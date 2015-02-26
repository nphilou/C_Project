#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "app.h"


int main(int argc, char *argv[]) {

    SDL_Surface *ecran = NULL, *rectangle = NULL;
    SDL_Rect position;
    SDL_Event event;
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    //chargement images
    SDL_Surface *fourmiliere = NULL, *ouvriere = NULL, *reine = NULL, *soldat = NULL;
    fourmiliere = IMG_LOAD

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_WM_SetCaption("Hohoho", NULL);

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
    position.x = 10;
    position.y = 20;
    SDL_EnableKeyRepeat(10, 10);

    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
    SDL_BlitSurface(rectangle, NULL, ecran, &position);

    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        position.y -= 5;
                        break;
                    case SDLK_DOWN:
                        position.y += 5;
                        break;
                    case SDLK_RIGHT:
                        position.x += 5;
                        break;
                    case SDLK_LEFT:
                        position.x -= 5;
                        break;
                }
                break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(rectangle, NULL, ecran, &position);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(rectangle);
    SDL_Quit();

    Monde *myWorld = creationMonde();

    int indice = map(2, 2, myWorld->plateau->cote);
    creationFourmi(ROUGE, SOLDAT, myWorld->noire, myWorld, indice);
    indice = map(3, 2, myWorld->plateau->cote);
    
    affichePlateau(myWorld->plateau);
/*
    int premierJoueur = (int) ROUGE;
    int i = 1;
    while(i){
        printf("((((((((((((((((TOUR ROUGE))))))))))))))))\n");
        tour(myWorld, myWorld->rouge, myWorld->noire);
        printf("((((((((((((((((TOUR NOIR))))))))))))))))\n");
        tour(myWorld, myWorld->noire, myWorld->rouge);
        printf("Quitter ? OUI(0), NON(1)");
        scanf("%d", &i);
    }
    */
    return 0;
}