#include <stdio.h>
#include <SDL/SDL.h>
#include "app.h"

void pause() {
    int continuer = 1;
    SDL_Event event;

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

int main(int argc, char *argv[]) {

    SDL_Surface *ecran = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Hohoho", NULL);

    if (ecran == NULL){
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    pause();

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