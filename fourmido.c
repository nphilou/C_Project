#include <stdio.h>

#include "structures.h"
#include "plateau.h"
#include "app.h"
#include "init.h"
#include "jeu.h"
#include "deplacement.h"


int main(int argc, char *argv[]) {


    Monde *myWorld = creationMonde();
 /*
    int indice1 = map(2, 2, myWorld->plateau->cote);
    int indice2 = map(2, 2, myWorld->plateau->cote);
    int indice3 = map(2, 2, myWorld->plateau->cote);
    int indice4 = map(3, 2, myWorld->plateau->cote);
    creationFourmi(ROUGE, OUVRIERE, myWorld->rouge, myWorld, indice1);
    creationFourmi(ROUGE, SOLDAT, myWorld->rouge, myWorld, indice2);
    creationFourmi(ROUGE, OUVRIERE, myWorld->rouge, myWorld, indice3);
    creationFourmi(NOIR, SOLDAT, myWorld->noire, myWorld, indice4);
*/

   //affichePlateau(myWorld->plateau);

    //creationFourmiliere(ROUGE, myWorld , indice);

    //printf("le type de ma fourmi:%d\n", myWorld -> plateau -> cases[12].fourmi-> type);
    //printf("le type de ma fourmi suivante :%d\n", myWorld -> plateau -> cases[12].fourmi-> voisinSuiv-> type);

    //printf("supprime fourmiliere, indice = %d\n", myWorld -> plateau -> cases[24].fourmi->position);
    //supprimeFourmiliere (myWorld -> plateau -> cases[0].fourmi, myWorld);
    //suicideFourmi(myWorld-> plateau -> cases[5].fourmi, myWorld);
    //transformeFourmi (myWorld -> plateau -> cases[1].fourmi,myWorld); 

    //printf("la fourmiliere precedente position:%d\n", myWorld-> plateau -> cases[1].fourmi -> fourmilierePrec -> position);
    //affichePlateau(myWorld->plateau);

    //combatCase(myWorld, myWorld -> plateau -> cases[13].fourmi, 12);
    //affichePlateau(myWorld->plateau);

    /*deplacementFourmi(myWorld, myWorld -> plateau -> cases[12].fourmi, 3,3);
    deplacementFourmi(myWorld, myWorld -> plateau -> cases[12].fourmi, 2,3);
    printf("fourmi de la case: %d\n", myWorld -> plateau -> cases[12].fourmi-> type);
    printf("fourmi -> suivante: %d\n", myWorld -> plateau -> cases[12].fourmi->voisinPrec-> type);
    */
    //affichePlateau(myWorld->plateau);

    //printf("type fourmi:%d\n", myWorld -> plateau -> cases[24].fourmi -> type);


    //int premierJoueur = (int) ROUGE;
    /*int i = 1;
    while(i){
        printf("((((((((((((((((TOUR ROUGE))))))))))))))))\n");
        tour(myWorld, myWorld->rouge, myWorld->noire);
        printf("((((((((((((((((TOUR NOIR))))))))))))))))\n");
        premierJoueur = (int) NOIR;
        tour(myWorld, myWorld->noire, myWorld->rouge);
        printf("Quitter ? OUI(0), NON(1)");
        scanf("%d", &i);
    }*/

   // sauvegarde(myWorld, premierJoueur);
    //chargement ();
    //affichePlateau(myWorld->plateau);

    return 0;
}