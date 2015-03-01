#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "app.h"


/*
void sauvegarde (Monde* myWorld){
    // ttes fourmi: fourmiliere/ouviere/soldat/reine par equipe
    // leur position
    // derniere instruction pour chaque fourmi
    // tresor
    // a qui le tour de jouer !!


    FILE *file = fopen (" derniere sauvegarde.txt", "w+");

    Fourmi *temp;

    temp = myWorld -> rouge;
    fprintf (file, "%d %d\n", temp-> couleur, myWorld -> tresorRouge);
    while (temp -> fourmiliereSuiv!= NULL){
            while ( temp -> suivant != NULL){
                fprintf (file, "%d %d %d %d %d\n", temp -> origine, temp -> type, temp -> couleur, temp > indice, temp-> instruction);
                temp = temp -> suivant;
            }
        temp = temp -> fourmiliereSuiv;
    }

    temp = myWorld -> noire;
    fprintf (file, "%d %d\n", temp-> couleur, myWorld -> tresorNoire);
     while (temp -> fourmiliereSuiv!= NULL){
            while ( temp -> suivant != NULL){
                fprintf (file, "%d %d %d %d %d\n", temp -> origine, temp -> type, temp -> couleur, temp > indice, temp-> instruction);
                temp = temp -> suivant;
            }
        temp = temp -> fourmiliereSuiv;
    }

    // a qui le tour ...
    fprintf (file, "")
}

void chargement (Monde*myWorld){

    //couleur equipe/tresor
    //origine/type/couleur/indice/instruction

    FILE * file = fopen("derniere sauvegarde.txt", "r");

    if(f==NULL){
        printf("error");
        exit(EXIT_FAILURE);
    }

    int element;
    do {
        element = fgetc (file);



    } while ( element != EOF);

    fclose (file);

}
*/