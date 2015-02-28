#include <stdio.h>

#include "structures.h"
#include "plateau.h"
#include "app.h"
#include "init.h"

int main(int argc, char *argv[]) {


    Monde *myWorld = creationMonde();

    int indice1 = map(2, 2, myWorld->plateau->cote);
    int indice2 = map(2, 2, myWorld->plateau->cote);
    creationFourmi(NOIR, SOLDAT, myWorld->noire, myWorld, indice1);
    creationFourmi(ROUGE, SOLDAT, myWorld->rouge, myWorld, indice2);
    // indice = map(3, 2, myWorld->plateau->cote);

    affichePlateau(myWorld->plateau);

    //creationFourmiliere(ROUGE, myWorld , indice);

    printf("le type de ma fourmi:%d", myWorld -> plateau -> cases[12].fourmi-> type); 
    printf("le type de ma fourmi suivante :%d", myWorld -> plateau -> cases[12].fourmi-> voisinSuiv-> type); 

    //printf("supprime fourmiliere, indice = %d\n", myWorld -> plateau -> cases[24].fourmi->position);
    //supprimeFourmiliere (myWorld -> plateau -> cases[0].fourmi, myWorld);
    //suicideFourmi(myWorld-> plateau -> cases[5].fourmi, myWorld);
    //transformeFourmi (myWorld -> plateau -> cases[1].fourmi,myWorld); 

    //printf("la fourmiliere precedente position:%d\n", myWorld-> plateau -> cases[1].fourmi -> fourmilierePrec -> position);
    //affichePlateau(myWorld->plateau);

    //priseFourmiliere( myWorld -> plateau -> cases[0].fourmi , myWorld, myWorld -> plateau -> cases[24].fourmi);

    //combatFourmi(myWorld -> plateau -> cases[18].fourmi, myWorld -> plateau -> cases[0].fourmi, myWorld); 



    //deplacementFourmi(myWorld, myWorld -> plateau -> cases[6].fourmi, 2,2);

    //affichePlateau(myWorld->plateau);

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