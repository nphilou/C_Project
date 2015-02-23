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
    //printf("couleur rouge normalement : %d", myWorld->plateau->cases[0]->fourmi->couleur);
    //printf("test couleur : %d", myWorld->plateau->cases[0]->fourmi->couleur);


    /*int x,y;
    printf("x et y ?");
    scanf("%d", &x);
    scanf("%d", &y);*/

    
    int indice = map(2, 2, myWorld->plateau->cote);
    creationFourmi(ROUGE, SOLDAT, myWorld, indice);

    affichePlateau(myWorld->plateau);
   
    /*int a, b;
    demandeDestination(&a, &b, myWorld);
    printf("a = %d et b = %d \n", a, b);
    
    //int test = deplacementFourmi(myWorld, myWorld-> plateau -> cases[1].fourmi, &a, &b);
    //printf("test= %d\n", test);
    */

   
    supprimeFourmi(myWorld -> plateau -> cases[0].fourmi, myWorld, myWorld -> plateau -> cases[].fourmi); 
    printf("couleur de l'ouvriere\n", myWorld -> plateau -> cases[5].fourmi-> couleur);
   //supprimeFourmi(myWorld-> plateau -> cases[5].fourmi, myWorld);
   
    //combatFourmi ( myWorld -> plateau -> cases[0].fourmi , myWorld -> plateau -> cases[24].fourmi,myWorld);
   
   
   affichePlateau(myWorld->plateau);



    /*printf("case libre = %d\n", chercheLibre(indice, myWorld));
    creationFourmi(ROUGE, REINE, myWorld, chercheLibre(indice, myWorld));
    affichePlateau(myWorld->plateau);*/


    /*
    //creation de fourmis en masse :D
    int test=0;
    //while (!test){
        printf("x et y ?");
        scanf("%d", &x);
        scanf("%d", &y);
        
        if(x<0){
            printf("Deja fini ?");
            test++;
        }
        
        //int indice= map(x, y, myWorld->plateau->cote);
        creationFourmi (ROUGE, SOLDAT , myWorld, indice); 
        
        //printf("La case libre la plus proche a pour indice %d soit %d en abs et %d en ord\n", chercheLibre(indice, myWorld), chercheAbscisse(myWorld, chercheLibre(indice, myWorld)), chercheOrdonnee(myWorld, chercheLibre(indice, myWorld)));
        creationFourmi (ROUGE, REINE , myWorld, chercheLibre(indice, myWorld));
        creationFourmi (ROUGE, REINE , myWorld, chercheLibre(indice, myWorld));
        creationFourmi (ROUGE, REINE , myWorld, chercheLibre(indice, myWorld));
        creationFourmi (ROUGE, REINE , myWorld, chercheLibre(indice, myWorld));
        creationFourmi (ROUGE, REINE , myWorld, chercheLibre(indice, myWorld));
        creationFourmi (ROUGE, REINE , myWorld, chercheLibre(indice, myWorld));
        creationFourmi (ROUGE, REINE , myWorld, chercheLibre(indice, myWorld));
        
        affichePlateau(myWorld->plateau);
    //}
*/
    return 0;
}