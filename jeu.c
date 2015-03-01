#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "structures.h"
#include "instructions.h"
#include "jeu.h"
#define TMAX 256
#include <math.h>
#include "config.h"
#include "init.h"
#include "plateau.h"

void sauvegarde (Monde* myWorld, int joueur){

    FILE *file = fopen ("derniere_sauvegarde.txt", "w+");

    Fourmi *tempFourmiliere;
    Fourmi * tempFourmi;

    fprintf (file, "%d %d\n",myWorld -> tresorRouge, myWorld -> tresorNoire);

    tempFourmiliere = myWorld -> rouge;
    if (tempFourmiliere -> fourmiliereSuiv != NULL){
        while (tempFourmiliere != NULL){
            tempFourmi = tempFourmiliere ;
            while ( tempFourmi != NULL){
                fprintf (file, "%d %d %d %d %d\n", tempFourmi -> type, tempFourmi -> origine->position, tempFourmi -> couleur, tempFourmi -> position, tempFourmi-> instruction);
                tempFourmi = tempFourmi -> suivant;
            }
            tempFourmiliere = tempFourmiliere -> fourmiliereSuiv;
        }
    } else {
        tempFourmi = tempFourmiliere;
        while ( tempFourmi != NULL){
            fprintf (file, "%d %d %d %d %d\n", tempFourmi -> type,tempFourmi -> origine->position,  tempFourmi -> couleur, tempFourmi -> position, tempFourmi-> instruction);
            tempFourmi = tempFourmi-> suivant;
        }
    }


    tempFourmiliere = myWorld -> noire;
    if (tempFourmiliere -> fourmiliereSuiv != NULL){
        while (tempFourmiliere != NULL){
            tempFourmi = tempFourmiliere;
            while ( tempFourmi != NULL){
                fprintf (file, "%d %d %d %d %d\n", tempFourmi -> type,tempFourmi -> origine->position,  tempFourmi -> couleur, tempFourmi -> position, tempFourmi-> instruction);
                tempFourmi = tempFourmi -> suivant;
            }
            tempFourmiliere = tempFourmiliere -> fourmiliereSuiv;
        }
    } else {
        tempFourmi = tempFourmiliere;
        while ( tempFourmi != NULL){
            fprintf (file, "%d %d %d %d %d\n", tempFourmi -> type,tempFourmi -> origine->position,  tempFourmi -> couleur, tempFourmi -> position, tempFourmi-> instruction);
            tempFourmi = tempFourmi-> suivant;
        }
    }
    // a qui le tour ...
    fprintf (file, "%d\n", joueur);
}



void chargement (){

    //myWorld -> tresorRouge, myWorld -> tresorNoire
    //ROUGE
    //tempAgent -> type,tempAgent -> origine -> position,  tempAgent -> couleur, tempAgent -> position, tempAgent-> instruction
    //joueur tour !


    FILE * file = fopen("derniere_sauvegarde.txt", "r");

    if(file==NULL){
        printf("error");
        exit(EXIT_FAILURE);
    }

    int tab[15] = {0};
    char ligne[TMAX] = "";

    while(fgets(ligne, TMAX, file)!= NULL){
        fscanf(ligne, "%d %d %d %d %d", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4]);
    }


    printf("mon fichier : %d %d %d %d %d", tab[0], tab[1], tab[2], tab[3], tab[4]);

    fclose (file);
/*
    Monde *myWorld = chargementMonde(tab, compt);
    affichePlateau(myWorld->plateau);
*/
}
/*
int * recupereEntier (FILE*file, int *compt){
    char temp[15];
    char * p;
    int tempTab [TMAX];
    int * tabEntier;
    int i;
    *compt=0;

    while (fgets(temp, 15, file)){

        p= temp;
        while (*p) {
            if (isdigit(*p)) {
                tempTab[(*compt)++] = atoi(p);
                while (isdigit(*p)) p++;
            } else {
                p++;
            }
        }
    }

    tabEntier = malloc(*compt * sizeof(int));
    for (i = 0; i < *compt; i++) {
        tabEntier[i] = tempTab[i];
    }

    return tabEntier;
}


Monde * chargementMonde( char * tab, int compt) {
    //Creation Monde
    Monde *myWorld = calloc(1, sizeof(Monde));

    //Creation plateau
    int cotePlateau = COTE;

    Plateau *plateau = calloc((size_t) pow(cotePlateau, 2), sizeof(Case));


    plateau->nombrecases = (int) pow(cotePlateau, 2); //A RENOMMER PAR TAILLE
    plateau->cote = cotePlateau;
    printf("plateau->nombrecases = %d \n", plateau->nombrecases);

    //raccourcis
    int cote = plateau->cote;
    int taille = plateau->nombrecases;

    myWorld->plateau = plateau;


    */
/*
    //Creation fourmilieres rouge et noire
    myWorld->noire = initialisation(NOIR, plateau);
    myWorld->rouge = initialisation(ROUGE, plateau);

    //Creation all
    creationFourmi(ROUGE, REINE, myWorld->rouge, myWorld, 1);
    creationFourmi(NOIR, REINE, myWorld->noire, myWorld, taille - 2);
    creationFourmi(ROUGE, OUVRIERE, myWorld->rouge, myWorld, cote);
    creationFourmi(NOIR, OUVRIERE, myWorld->noire, myWorld, taille - cote - 1);
*/
/*
            myWorld->tresorRouge = tab[0];
            myWorld->tresorNoire = tab[1];





    return myWorld;
}*/

/*
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