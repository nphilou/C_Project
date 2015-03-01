

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "instructions.h"
#include "jeu.h"

void sauvegarde (Monde* myWorld, int joueur){

    FILE *file = fopen ("derniere_sauvegarde.txt", "w+");

    Fourmi *tempFourmiliere;
    Fourmi * tempAgent;

    fprintf (file, "%d %d\n",myWorld -> tresorRouge, myWorld -> tresorNoire);
    tempFourmiliere = myWorld -> rouge;
    printf("type fourmi:%d", myWorld -> rouge -> type);
    if (tempFourmiliere -> fourmiliereSuiv != NULL){
        while (tempFourmiliere != NULL){
            fprintf (file, "%d %d %d\n", tempFourmiliere-> position, tempFourmiliere->instruction, tempFourmiliere-> couleur);
            tempAgent = tempFourmiliere -> suivant;
            while ( tempAgent != NULL){
                fprintf (file, "%d %d %d %d %d\n", tempAgent -> origine->position, tempAgent -> type, tempAgent -> couleur, tempAgent -> position, tempAgent-> instruction);
                tempAgent = tempAgent -> suivant;
            }
            tempFourmiliere = tempFourmiliere -> fourmiliereSuiv;
        }
    } else {
        tempAgent = tempFourmiliere -> suivant;
        while ( tempAgent != NULL){
            fprintf (file, "%d %d %d %d %d\n", tempAgent -> origine->position, tempAgent -> type, tempAgent -> couleur, tempAgent -> position, tempAgent-> instruction);
            tempAgent = tempAgent -> suivant;
        }
    }


    tempFourmiliere = myWorld -> noire;
    if (tempFourmiliere -> fourmiliereSuiv != NULL){
        while (tempFourmiliere != NULL){
            fprintf (file, "%d %d %d\n", tempFourmiliere-> position, tempFourmiliere->instruction, tempFourmiliere-> couleur);
            tempAgent = tempFourmiliere -> suivant;
            while ( tempAgent -> suivant != NULL){
                fprintf (file, "%d %d %d %d %d\n", tempAgent -> origine->position, tempAgent -> type, tempAgent -> couleur, tempAgent -> position, tempAgent-> instruction);
                //tempAgent = tempAgent -> suivant;
            }
            tempFourmiliere = tempFourmiliere -> fourmiliereSuiv;
        }
    } else {
        tempAgent = tempFourmiliere->suivant;
        while (tempAgent->suivant != NULL) {
            fprintf(file, "%d %d %d %d %d\n", tempAgent->origine->position, tempAgent->type, tempAgent->couleur, tempAgent->position, tempAgent->instruction);
            //tempAgent = tempAgent -> suivant;
        }
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