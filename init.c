#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "init.h"

#define TRESOR 50

Fourmi *initialisation(Couleur couleur, Plateau *plateau) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = FOURMILIERE;

    if (couleur == ROUGE) plateau->cases[0].fourmi = fourmi;
    if (couleur == NOIR) plateau->cases[plateau->nombrecases - 1].fourmi = fourmi;

    fourmi->suivant = NULL;
    fourmi->precedant = NULL;
    fourmi->tempsProd = 0;

    return fourmi;
}

Fourmi *initialReine(Couleur couleur, Plateau *plateau, Fourmi *fourmiOrigine) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = REINE;
    fourmi->origine = fourmiOrigine;
    fourmi->precedant = fourmiOrigine;
    fourmi->suivant = NULL;
    fourmiOrigine->suivant = fourmi;

    if (couleur == ROUGE) {
        plateau->cases[1].fourmi = fourmi;
        fourmi->position = 1;
    }
    if (couleur == NOIR) {
        plateau->cases[map(plateau->cote - 2, plateau->cote - 1, plateau->cote)].fourmi = fourmi;
        fourmi->position = map(plateau->cote - 2, plateau->cote - 1, plateau->cote);
    }
    return fourmi;
}

Fourmi *initialOuvriere(Couleur couleur, Plateau *plateau, Fourmi *reine) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = OUVRIERE;

    reine->suivant = fourmi;
    fourmi->precedant = reine;
    fourmi->suivant = NULL;

    if (couleur == ROUGE) {
        plateau->cases[map(0, 1, plateau->cote)].fourmi = fourmi;
        fourmi->position = map(0, 1, plateau->cote);
    }
    if (couleur == NOIR) {
        plateau->cases[map(plateau->cote - 1, plateau->cote - 2, plateau->cote)].fourmi = fourmi;
        fourmi->position = map(plateau->cote - 1, plateau->cote - 2, plateau->cote);
    }
    return fourmi;
}

void creationFourmi(Couleur couleur, TypeFourmi typefourmi, Monde *myWorld, int indice) {

    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = typefourmi;

    Fourmi *listeFourmi;
    if (couleur == ROUGE) {
        listeFourmi = myWorld->rouge->suivant;
    } else {
        listeFourmi = myWorld->noire->suivant;
    }

    while (listeFourmi->suivant != NULL) {
        listeFourmi = listeFourmi->suivant;
    }

    listeFourmi->suivant = fourmi;
    fourmi->precedant = listeFourmi;
    fourmi->suivant = NULL;

    if (!estLibre(myWorld, indice)) {
        printf("case occupée try again\n");
        return;
    }

    myWorld->plateau->cases[indice].fourmi = fourmi;
}

void supprimeFourmi(Fourmi *fourmi, Monde *myWorld, Fourmi *fourmiAttaquante) {

    Fourmi *tmp1 = calloc(1, sizeof(Fourmi));
    Fourmi *autreEquipe = calloc(1, sizeof(Fourmi));
    int indice;


    if (fourmi->type != FOURMILIERE) {

        printf("je supprime l'ouvriere noire\n");
        indice = fourmi->position;
        tmp1 = fourmi;

        if (tmp1->suivant != NULL) {
            tmp1->precedant->suivant = tmp1->suivant;
            tmp1->suivant->precedant = tmp1->precedant;
        }
        else {
            tmp1->precedant->suivant = NULL;
        }
        free(fourmi);
        myWorld->plateau->cases[indice].fourmi = NULL;
    }

    else {  // FOURMILIERE


        while (fourmi->suivant != NULL) {

            //tmp1 = calloc(1, sizeof(Fourmi));
            affichePlateau(myWorld->plateau);
            indice = fourmi->position;

            if (fourmi->type != OUVRIERE) {

                indice = fourmi->position;
                tmp1 = fourmi;
                fourmi = fourmi->suivant;
                fourmi->precedant = NULL;
                free(tmp1);
                myWorld->plateau->cases[indice].fourmi = NULL;

            }


            else { // si c'est une ouvriere
                tmp1 = fourmi;
                if (fourmi->suivant != NULL) {
                    fourmi->precedant->suivant = fourmi->suivant;
                    fourmi->suivant->precedant = fourmi->precedant;
                }
                else {
                    fourmi->precedant->suivant = NULL;
                }

                if (tmp1->couleur == ROUGE) {
                    tmp1->couleur = NOIR;
                    tmp1->suivant = NULL;
                    //tmp1 -> origine = fourmiAttaquante;

                    autreEquipe = myWorld->noire;
                    while (autreEquipe->suivant != NULL) {
                        autreEquipe = autreEquipe->suivant;
                    }
                    tmp1->precedant = autreEquipe;
                    autreEquipe->suivant = tmp1;

                }
                else {
                    tmp1->couleur = ROUGE;
                    tmp1->suivant = NULL;
                    //tmp1 -> origine = fourmiAttaquante;

                    autreEquipe = myWorld->rouge;
                    while (autreEquipe->suivant != NULL) {
                        autreEquipe = autreEquipe->suivant;
                    }
                    tmp1->precedant = autreEquipe;
                    autreEquipe->suivant = tmp1;

                }

                fourmi = fourmi->suivant;
            }

        }

    }

}

Monde *creationMonde() {
    //Creation Monde
    Monde *myWorld = calloc(1, sizeof(Monde));

    //Creation plateau
    int cotePlateau = 5;
    printf("Taille du plateau ? ");
    //scanf("%d", &cotePlateau);

    //Test valeur saisie >1
    if (cotePlateau <= 1) {
        printf("Bah bravo MORRAY !\n");
        exit(1);
    }

    Plateau *plateau = calloc((size_t) pow(cotePlateau, 2), sizeof(Case));
    plateau->nombrecases = (int) pow(cotePlateau, 2);
    plateau->cote = cotePlateau;
    printf("plateau->nombrecases = %d \n", plateau->nombrecases);


    myWorld->plateau = plateau;

    //Creation fourmilieres rouge et noire
    myWorld->noire = initialisation(NOIR, plateau);
    myWorld->rouge = initialisation(ROUGE, plateau);


    //Creation reines
    myWorld->noire->suivant = initialReine(NOIR, plateau, myWorld->noire);
    myWorld->rouge->suivant = initialReine(ROUGE, plateau, myWorld->rouge);

    //Creation ouvrieres
    myWorld->noire->suivant->suivant = initialOuvriere(NOIR, plateau, myWorld->noire->suivant);
    myWorld->rouge->suivant->suivant = initialOuvriere(ROUGE, plateau, myWorld->rouge->suivant);

    myWorld->tresorNoire = TRESOR;
    myWorld->tresorRouge = TRESOR;

    return myWorld;
}