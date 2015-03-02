#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "instructions.h"
#include "jeu.h"

#define TMAX 256

#include <math.h>
#include "config.h"
#include "init.h"
#include "plateau.h"
#include "affichage.h"

void sauvegarde(Monde *monde) {

    FILE *file = fopen("derniere_sauvegarde.txt", "w+");

    Fourmi *tempFourmiliere;
    Fourmi *tempFourmi;

    fprintf(file, "%d %d\n", monde->tresorRouge, monde->tresorNoire);

    tempFourmiliere = monde->rouge;
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


    tempFourmiliere = monde->noire;
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
    fclose(file);
}


Monde* chargement() {

    //myWorld -> tresorRouge, myWorld -> tresorNoire
    //tempAgent -> type,tempAgent -> origine -> position,  tempAgent -> couleur, tempAgent -> position, tempAgent-> instruction
    //joueur tour !


    FILE *file = fopen("derniere_sauvegarde.txt", "r");

    if (file == NULL) {
        printf("error");
        exit(EXIT_FAILURE);
    }


    int i = 0;
    int tresor[2];
    int type[TMAX];
    int origine[TMAX];
    int couleur[TMAX];
    int position[TMAX];
    int instruction[TMAX];
    char chaine[TMAX];
    int compt=0;

    fscanf(file, "%d %d", &tresor[0], &tresor[1]);
    printf("mon tresor est: %d, %d\n", tresor[0], tresor[1]);

    while ( fgets(chaine, TMAX, file)) {
        compt++;
        printf("%s", chaine);
        sscanf(chaine, "%d %d %d %d %d", &type[i], &origine[i], &couleur[i], &position[i], &instruction[i]);
        i++;
    }

    printf("mon fichier : %d %d %d %d %d\n", type[1], origine[1], couleur[1], position[1], instruction[1]);
    printf("mon fichier : %d %d %d %d %d\n", type[2], origine[2], couleur[2], position[2], instruction[2]);


    fclose(file);

    Monde * monde = chargementMonde(compt, tresor, type, origine, couleur, position, instruction);

    affichePlateauSDL(monde);
    return monde;

}


Monde * chargementMonde(int compt, int tresor[], int type[], int origine[], int couleur[], int position[], int instruction[]) {
    //Creation Monde
    Monde *monde = calloc(1, sizeof(Monde));

    //Creation plateau
    int cotePlateau = COTE;
    int i=2;    // commence le tableau à l'indice 1

    Plateau *plateau = calloc((size_t) pow(cotePlateau, 2), sizeof(Case));

    plateau->nombrecases = (int) pow(cotePlateau, 2); //A RENOMMER PAR TAILLE
    plateau->cote = cotePlateau;


    monde->plateau = plateau;


    //Creation fourmilieres rouge et noire
    monde->noire = NULL;
    monde->rouge = NULL;

    creationFourmiliere(monde, (Couleur) couleur[1], position[1], instruction[1]);

    printf("compt : %d\n", compt);
    while(i<=compt-1){
        if(type[i]==3) {
            creationFourmiliere(monde, (Couleur) couleur[i], position[i], instruction[i]);
        } else {
            printf("creation agent\n");
            creationFourmi(monde, monde->plateau->cases[origine[i]].fourmi , (Couleur) couleur[i], (TypeFourmi) type[i], position[i], instruction[i]);
            printf("boubou2\n");
        }
        i++;
    }
    monde->tresorRouge = tresor[0];
    monde->tresorNoire = tresor[1];

    affichePlateau(monde->plateau);
    affichePlateauSDL(monde);
    return monde;
}


void jeu() {
    int h, i = 1, l;

        printf("Voulez vous charger votre ancienne partie ? OUI(0) NON (1)");
        scanf("%d", &h);

    if (h == 0) {
        Monde *monde = chargement();
        while (i) {
            printf("((((((((((((((((((   TOUR  ROUGE   ))))))))))))))))))))\n");
            tour(monde, monde->rouge, monde->noire);
            afficherGagnant(monde);
            printf("(((((((((((((((((((   TOUR  NOIR   ))))))))))))))))))\n");
            tour(monde, monde->noire, monde->rouge);
            afficherGagnant(monde);
            printf("Quitter ? OUI(0), NON(1)");
            scanf("%d", &i);
        }
            printf("Voulez vous sauvegarder la partie ? OUI(0) NON(1)");
            scanf("%d", &l);
        if (l){
            sauvegarde(monde);
            videMemoire(monde);
        }else {
            videMemoire(monde);
        }
    }
    else {
        Monde *monde = creationMonde();
        while (i) {
            printf("((((((((((((((((((   TOUR  ROUGE   ))))))))))))))))))))\n");
            tour(monde, monde->rouge, monde->noire);
            //afficherGagnant(monde);
            if (monde->rouge == NULL && monde->noire != NULL) {
                printf("**********  JOUEUR NOIR A GAGNEEE  **********\n");
                break;
            } else if (monde->noire == NULL && monde->rouge != NULL) {
                printf("**********  JOUEUR ROUGE A GAGNEEE  ************\n");
                break;
            } else if (monde->rouge == NULL && monde->noire == NULL) {
                printf("*******MATCH NUL PAS DE GAGNANT ********\n");
                break;
            }
            printf("(((((((((((((((((((   TOUR  NOIR   ))))))))))))))))))\n");
            tour(monde, monde->noire, monde->rouge);
            if (monde->rouge == NULL && monde->noire != NULL) {
                printf("**********  JOUEUR NOIR A GAGNEEE  **********\n");
                break;
            } else if (monde->noire == NULL && monde->rouge != NULL) {
                printf("**********  JOUEUR ROUGE A GAGNEEE  ************\n");
                break;
            } else if (monde->rouge == NULL && monde->noire == NULL) {
                printf("*******MATCH NUL PAS DE GAGNANT ********\n");
                break;
            }
            //afficherGagnant(monde);
            printf("Quitter ? OUI(0), NON(1)");
            scanf("%d", &i);
        }
        do{
            printf("Voulez vous sauvegarder la partie ? OUI(0) NON(1)");
            scanf("%d", &l);
        }while (l != 0 || l != 1);
        if (l){
            sauvegarde(monde);
            videMemoire(monde);
        }else {
            videMemoire(monde);
        }
    }
}

/*
void afficherGagnant(Monde *monde) {
    if (monde->rouge == NULL && monde->noire != NULL) {
        printf("**********  JOUEUR NOIR A GAGNEEE  **********\n");
        break;
    } else if (monde->noire == NULL && monde->rouge != NULL) {
        printf("**********  JOUEUR ROUGE A GAGNEEE  ************\n");
        break;
    } else if (monde->rouge == NULL && monde->noire == NULL) {
        printf("*******MATCH NUL PAS DE GAGNANT ********\n");
        break;
    }
    return;
}
*/


void videMemoire(Monde *monde) {

    Fourmi *tmpFourmiliere;
    tmpFourmiliere = monde->rouge;

    if (tmpFourmiliere->fourmiliereSuiv != NULL) {
        while (tmpFourmiliere->fourmiliereSuiv != NULL) {
            supprimeFourmiliere(monde, tmpFourmiliere->fourmiliereSuiv);
        }
        supprimeFourmiliere(monde, tmpFourmiliere);
    } else {
        supprimeFourmiliere(monde, tmpFourmiliere);
    }

    free(monde->plateau);
    free(monde);
}

