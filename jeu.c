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

void sauvegarde(Monde *myWorld, int joueur) {

    FILE *file = fopen("derniere_sauvegarde.txt", "w+");

    Fourmi *tempFourmiliere;
    Fourmi *tempFourmi;

    fprintf(file, "%d %d\n", myWorld->tresorRouge, myWorld->tresorNoire);

    tempFourmiliere = myWorld->rouge;
    if (tempFourmiliere->fourmiliereSuiv != NULL) {
        while (tempFourmiliere != NULL) {
            tempFourmi = tempFourmiliere;
            while (tempFourmi != NULL) {
                fprintf(file, "%d %d %d %d %d\n", tempFourmi->type, tempFourmi->origine->position, tempFourmi->couleur, tempFourmi->position, tempFourmi->instruction);
                tempFourmi = tempFourmi->suivant;
            }
            tempFourmiliere = tempFourmiliere->fourmiliereSuiv;
        }
    } else {
        tempFourmi = tempFourmiliere;
        while (tempFourmi != NULL) {
            fprintf(file, "%d %d %d %d %d\n", tempFourmi->type, tempFourmi->origine->position, tempFourmi->couleur, tempFourmi->position, tempFourmi->instruction);
            tempFourmi = tempFourmi->suivant;
        }
    }


    tempFourmiliere = myWorld->noire;
    if (tempFourmiliere->fourmiliereSuiv != NULL) {
        while (tempFourmiliere != NULL) {
            tempFourmi = tempFourmiliere;
            while (tempFourmi != NULL) {
                fprintf(file, "%d %d %d %d %d\n", tempFourmi->type, tempFourmi->origine->position, tempFourmi->couleur, tempFourmi->position, tempFourmi->instruction);
                tempFourmi = tempFourmi->suivant;
            }
            tempFourmiliere = tempFourmiliere->fourmiliereSuiv;
        }
    } else {
        tempFourmi = tempFourmiliere;
        while (tempFourmi != NULL) {
            fprintf(file, "%d %d %d %d %d\n", tempFourmi->type, tempFourmi->origine->position, tempFourmi->couleur, tempFourmi->position, tempFourmi->instruction);
            tempFourmi = tempFourmi->suivant;
        }
    }
    // a qui le tour ...
    fprintf(file, "%d\n", joueur);
}


Monde *chargement() {

    //myWorld -> tresorRouge, myWorld -> tresorNoire
    //ROUGE
    //tempAgent -> type,tempAgent -> origine -> position,  tempAgent -> couleur, tempAgent -> position, tempAgent-> instruction
    //joueur tour !


    FILE *file = fopen("derniere_sauvegarde.txt", "r");

    if (file == NULL) {
        printf("error");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    int tresor[2] = {0};
    int type[TMAX] = {0};
    int origine[TMAX] = {0};
    int couleur[TMAX] = {0};
    int position[TMAX] = {0};
    int instruction[TMAX] = {0};
    char chaine[TMAX] = {0};

    fscanf(file, "%d %d", &tresor[0], &tresor[1]);

    while (fgets(chaine, TMAX, file))!= NULL){
        fscanf(file, "%d %d %d %d %d", &type[i], &origine[i], &couleur[i], &position[i], &instruction[i]);
        i++;
    }
    printf("mon tresor est: %d, %d\n", tresor[0], tresor[1]);
    printf("mon fichier : %d %d %d %d %d\n", type[0], origine[0], couleur[0], position[0], instruction[0]);

    fclose(file);

    Monde *myWorld = chargementMonde(tresor, type, origine, couleur, position, instruction);
    affichePlateau(myWorld->plateau);

    return myWorld;
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
            myWorld->tresorRouge = tresor[0];
            myWorld->tresorNoire = tab[1];


    return myWorld;
}*/


void jeu() {
    int h = 1, i = 1;
    int premierJoueur = 0;  // 0 =rouge , 1=noir

    do {
        printf("Voulez vous charger votre ancienne partie ? OUI(0) NON (1)");
        scanf("%d", &h);
    } while (h != 0 || h != 1);

    if (h == 0) {
        Monde *myWorld = chargement();
        while (i) {
            printf("((((((((((((((((((   TOUR  ROUGE   ))))))))))))))))))))\n");
            tour(myWorld, myWorld->rouge, myWorld->noire);
            afficherGagnant(myWorld);
            printf("(((((((((((((((((((   TOUR  NOIR   ))))))))))))))))))\n");
            tour(myWorld, myWorld->noire, myWorld->rouge);
            afficherGagnant(myWorld);
            printf("Quitter ? OUI(0), NON(1)");
            scanf("%d", &i);
        }
        sauvegarde(myWorld, premierJoueur);
        videMemoire(myWorld);
    }
    else {
        Monde *myWorld = creationMonde();
        while (i) {
            printf("((((((((((((((((((   TOUR  ROUGE   ))))))))))))))))))))\n");
            tour(myWorld, myWorld->rouge, myWorld->noire);
            afficherGagnant(myWorld);
            printf("(((((((((((((((((((   TOUR  NOIR   ))))))))))))))))))\n");
            tour(myWorld, myWorld->noire, myWorld->rouge);
            afficherGagnant(myWorld);
            printf("Quitter ? OUI(0), NON(1)");
            scanf("%d", &i);
        }
        sauvegarde(myWorld, premierJoueur);
        videMemoire(myWorld);
    }

}

void afficherGagnant(Monde *myWorld) {
    if (myWorld->rouge == NULL && myWorld->noire != NULL) {
        printf("**********  JOUEUR NOIR A GAGNEEE  **********\n");
    } else if (myWorld->noire == NULL && myWorld->rouge != NULL) {
        printf("**********  JOUEUR ROUGE A GAGNEEE  ************\n");
    } else if (myWorld->rouge == NULL && myWorld->noire == NULL) {
        printf("*******MATCH NUL PAS DE GAGNANT ********\n");
    }
}

// SCORE

void videMemoire(Monde *myWorld) {

    Fourmi *tmpFourmiliere;
    tmpFourmiliere = myWorld->rouge;

    if (tmpFourmiliere->fourmiliereSuiv != NULL) {
        while (tmpFourmiliere->fourmiliereSuiv != NULL) {
            supprimeFourmiliere(tmpFourmiliere->fourmiliereSuiv, myWorld);
        }
        supprimeFourmiliere(tmpFourmiliere, myWorld);
    } else {
        supprimeFourmiliere(tmpFourmiliere, myWorld);
    }

    free(myWorld->plateau);
    free(myWorld);
}

