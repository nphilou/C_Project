#include <stdio.h>
#include <stdlib.h>
//#include <SDL/SDL.h>
#include "app.h"
//#include "structures.h"

/*void pause() {
    int continuer = 1;
    SDL_Event event;

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}*/

int main(int argc, char *argv[]) {

    /*SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    SDL_WM_SetCaption("Hohoho", NULL);

    pause(); // Mise en pause du programme

    SDL_Quit(); // Arrêt de la SDL
    */
    
    Monde *myWorld = creationMonde();
    //printf("couleur rouge normalement : %d", myWorld->plateau->cases[0]->fourmi->couleur);
    //printf("test couleur : %d", myWorld->plateau->cases[0]->fourmi->couleur);
    
    
    /*int tresorRouge[1];
    tresorRouge [0] = 50;
    int tresorNoire[1];
    tresorRouge [0] = 50;*/
    
    int x,y;
    printf("x et y ?");
    scanf("%d", &x);
    scanf("%d", &y);
    
    creationFourmi (ROUGE, SOLDAT , myWorld, x, y); 
    
    printf("case x y : %d\n", estLibre(myWorld, x, y));
    
    affichePlateau(myWorld->plateau);

    return 0; // Fermeture du programme
}