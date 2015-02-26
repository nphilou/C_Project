#include <stdio.h>
//#include <SDL/SDL.h>
#include "app.h"

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

    /* SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    SDL_WM_SetCaption("Hohoho", NULL);

    pause(); // Mise en pause du programme

    SDL_Quit(); // Arrêt de la SDL
    */

    Monde *myWorld = creationMonde();

    int indice = map(2, 2, myWorld->plateau->cote);
    creationFourmi(ROUGE, SOLDAT, myWorld->noire, myWorld, indice);
   // indice = map(3, 2, myWorld->plateau->cote);
    
     
    affichePlateau(myWorld->plateau);
    
    //creationFourmiliere(ROUGE, myWorld , indice);
 
    
    
    //printf("supprime fourmiliere, indice = %d\n", myWorld -> plateau -> cases[24].fourmi->position);
    //supprimeFourmiliere (myWorld -> plateau -> cases[0].fourmi, myWorld);
    //suicideFourmi(myWorld-> plateau -> cases[5].fourmi, myWorld);

    priseFourmiliere( myWorld -> plateau -> cases[0].fourmi , myWorld,myWorld -> plateau -> cases[23].fourmi);
    /*if ( myWorld -> plateau -> cases[0].fourmi == NULL ||  myWorld -> plateau -> cases[23].fourmi == NULL){
      printf(" ca marche"); 
    }*/

    affichePlateau(myWorld->plateau);

    /*int premierJoueur = (int) ROUGE;
    int i = 1;
    while(i){
        printf("((((((((((((((((TOUR ROUGE))))))))))))))))\n");
        tour(myWorld, myWorld->rouge, myWorld->noire);
        printf("((((((((((((((((TOUR NOIR))))))))))))))))\n");
        tour(myWorld, myWorld->noire, myWorld->rouge);
        printf("Quitter ? OUI(0), NON(1)");
        scanf("%d", &i);
    }*/
    
    return 0;
}