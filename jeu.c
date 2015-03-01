#include "jeu.h"
#include "instructions.h"
//#include <stdio.h>
//#include <stdlib.h>
#include "structures.h"

void sauvegarde (Monde* myWorld, int joueur){

    FILE *file = fopen ("derniere_sauvegarde.txt", "w+");

    Fourmi *temp;

    temp = myWorld -> rouge;
    fprintf (file, "%d %d\n", temp-> couleur, myWorld -> tresorRouge);
    while (temp -> fourmiliereSuiv!= NULL){
            while ( temp -> suivant != NULL){
                fprintf (file, "%d %d %d %d %d\n", temp -> origine, temp -> type, temp -> couleur, temp -> position, temp-> instruction);
                temp = temp -> suivant;
            }
        temp = temp -> fourmiliereSuiv;
    }

    temp = myWorld -> noire;
    fprintf (file, "%d %d\n", temp-> couleur, myWorld -> tresorNoire);
     while (temp -> fourmiliereSuiv!= NULL){
            while ( temp -> suivant != NULL){
                fprintf (file, "%d %d %d %d %d\n", temp -> origine, temp -> type, temp -> couleur, temp -> position, temp-> instruction);
                temp = temp -> suivant;
            }
        temp = temp -> fourmiliereSuiv;
    }
    // a qui le tour ...
    fprintf (file, "%d\n", joueur);
}

/*
void chargement (Monde*myWorld){

    //couleur equipe/tresor
    //origine/type/couleur/position/instruction
    //joueur tour !

    FILE * file = fopen("derniere_sauvegarde.txt", "r");

    if(file==NULL){
        printf("error");
        exit(EXIT_FAILURE);
    }

    int element;
    do {
        element = fgetc (file);



    } while ( element != EOF);

    fclose (file);

}


void jeu (Monde * myWorld){

    //

    int i = 1;
    int joueur; //0 =rouge , 1=noir
    while (i) {
        printf("((((((((((((((((TOUR ROUGE))))))))))))))))\n");
        joueur=0;
        tour(myWorld, myWorld->rouge, myWorld->noire);
        printf("((((((((((((((((TOUR NOIR))))))))))))))))\n");
        joueur=1;
        tour(myWorld, myWorld->noire, myWorld->rouge);
        printf("Quitter ? OUI(0), NON(1)");
        scanf("%d", &i);
    }
    sauvegarde(myWorld, joueur);

}

void afficherGagnant () {} // SCORE

void videMemoire (){}
*/