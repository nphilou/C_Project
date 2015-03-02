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


Monde *chargement() {

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
    int compt = 0;

    fscanf(file, "%d %d", &tresor[0], &tresor[1]);
    printf("mon tresor est: %d, %d\n", tresor[0], tresor[1]);

    while (fgets(chaine, TMAX, file)) {
        compt++;
        printf("%s", chaine);
        sscanf(chaine, "%d %d %d %d %d", &type[i], &origine[i], &couleur[i], &position[i], &instruction[i]);
        i++;
    }

    printf("mon fichier : %d %d %d %d %d\n", type[1], origine[1], couleur[1], position[1], instruction[1]);
    printf("mon fichier : %d %d %d %d %d\n", type[2], origine[2], couleur[2], position[2], instruction[2]);


    fclose(file);

    Monde *monde = chargementMonde(compt, tresor, type, origine, couleur, position, instruction);

    affichePlateauSDL(monde);
    return monde;

}


Monde *chargementMonde(int compt, int tresor[], int type[], int origine[], int couleur[], int position[], int instruction[]) {
    //Creation Monde
    Monde *monde = calloc(1, sizeof(Monde));


    int cotePlateau = COTE;
    int i = 2;

    //Creation plateau
    Plateau *plateau = calloc((size_t) pow(cotePlateau, 2), sizeof(Case));

    plateau->nombrecases = (int) pow(cotePlateau, 2);
    plateau->cote = cotePlateau;


    monde->plateau = plateau;


    monde->noire = NULL;
    monde->rouge = NULL;

    creationFourmiliere(monde, (Couleur) couleur[1], position[1], instruction[1]);

    while (i <= compt - 1) {
        if (type[i] == 3) {
            creationFourmiliere(monde, (Couleur) couleur[i], position[i], instruction[i]);
        } else {
            creationFourmi(monde, monde->plateau->cases[origine[i]].fourmi, (Couleur) couleur[i], (TypeFourmi) type[i], position[i], instruction[i]);
        }
        i++;
    }
    monde->tresorRouge = tresor[0];
    monde->tresorNoire = tresor[1];

    affichePlateauSDL(monde);
    return monde;
}


void jeu() {
    int h, i = 1, l;
    int gagnant;

    printf("Voulez vous charger votre ancienne partie ? OUI(0) NON (1)");
    scanf("%d", &h);

    if (h == 0) {
        Monde *monde = chargement();

        while (i) {

            printf("((((((((((((((((((   TOUR  ROUGE   ))))))))))))))))))))\n");
            tour(monde, monde->rouge, monde->noire);
            gagnant= afficherGagnant(monde);
            if(gagnant==1) break;


            printf("(((((((((((((((((((   TOUR  NOIR   ))))))))))))))))))\n");
            tour(monde, monde->noire, monde->rouge);
            gagnant= afficherGagnant(monde);
            if(gagnant==1) break;

            printf("Quitter ? OUI(0), NON(1)");
            scanf("%d", &i);
        }
        if (monde->rouge != NULL && monde->noire != NULL) {
            printf("Voulez vous sauvegarder la partie ? OUI(0) NON(1)");
            scanf("%d", &l);
            if (l) {
                sauvegarde(monde);
                videMemoire(monde);
            } else {
                videMemoire(monde);
            }
        } else {
            videMemoire(monde);
        }
    }

    else {
        Monde *monde = creationMonde();

        while (i) {
            printf("((((((((((((((((((   TOUR  ROUGE   ))))))))))))))))))))\n");
            tour(monde, monde->rouge, monde->noire);
            gagnant= afficherGagnant(monde);
            if(gagnant==1) break;


            printf("(((((((((((((((((((   TOUR  NOIR   ))))))))))))))))))\n");
            tour(monde, monde->noire, monde->rouge);
            gagnant= afficherGagnant(monde);
            if(gagnant==1) break;

            printf("Quitter ? OUI(0), NON(1)");
            scanf("%d", &i);
        }


        if (monde->rouge != NULL && monde->noire != NULL) {
            printf("Voulez vous sauvegarder la partie ? OUI(0) NON(1)");
            scanf("%d", &l);
            if (l==0) {
                sauvegarde(monde);
                videMemoire(monde);
            } else {
                videMemoire(monde);
            }
        } else {
            printf("vide memoire\n");
            videMemoire(monde);
        }
    }
}


int afficherGagnant(Monde *monde) {
    if (monde->rouge == NULL && monde->noire != NULL) {
        printf("**********  JOUEUR NOIR A GAGNEEE  **********\n\n");
        return 1;
    } else if (monde->noire == NULL && monde->rouge != NULL) {
        printf("**********  JOUEUR ROUGE A GAGNEEE  ************\n\n");
        return 1;
    } else if (monde->rouge == NULL && monde->noire == NULL) {
        printf("*******MATCH NUL PAS DE GAGNANT ********\n\n");
        return 1;
    }
    return 0;
}



void videMemoire(Monde *monde) {

    Fourmi *tmpFourmiRouge = NULL;
    Fourmi *tmpFourmiNoire= NULL;


    if (monde ->rouge !=NULL) {
        printf("sup equipe rouge\n");
        tmpFourmiRouge = monde->rouge;
        if (tmpFourmiRouge->fourmiliereSuiv != NULL) {
            while (tmpFourmiRouge->fourmiliereSuiv != NULL) {
                supprimeFourmiliere(monde, tmpFourmiRouge->fourmiliereSuiv);
            }
            supprimeFourmiliere(monde, tmpFourmiRouge);
        } else {
            supprimeFourmiliere(monde, tmpFourmiRouge);
        }
    }

    if (monde -> noire !=NULL) {
        tmpFourmiNoire= monde->noire;
        if (tmpFourmiNoire->fourmiliereSuiv != NULL) {
            while (tmpFourmiNoire->fourmiliereSuiv != NULL) {
                supprimeFourmiliere(monde, tmpFourmiNoire->fourmiliereSuiv);
            }
            supprimeFourmiliere(monde, tmpFourmiNoire);
        } else {
            supprimeFourmiliere(monde, tmpFourmiNoire);
        }
    }

    free(monde->plateau);
    free(monde);
}
