#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "structures.h"
#include "init.h"
#include "plateau.h"

Fourmi *initialisation(Couleur couleur, Plateau *plateau) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = FOURMILIERE;
    fourmi->instruction = AUCUNE;
    fourmi->origine = fourmi;

    if (couleur == ROUGE) fourmi->position = 0;
    if (couleur == NOIR) fourmi->position = plateau->nombrecases - 1;

    plateau->cases[fourmi->position].fourmi = fourmi;
    fourmi->precedant = NULL;
    fourmi->suivant = NULL;
    fourmi->fourmilierePrec = NULL;
    fourmi->fourmiliereSuiv = NULL;
    fourmi->voisinPrec = NULL;
    fourmi->voisinSuiv = NULL;
    fourmi->tempsProd = 0;

    return fourmi;
}

void creationFourmi(Monde *monde, Fourmi *origine, Couleur couleur, TypeFourmi typefourmi, int indice, int instruction) {

    Fourmi *fourmi = calloc(1, sizeof(Fourmi));
    Fourmi *temp;

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = typefourmi;
    fourmi->instruction = (Instruction) instruction;
    fourmi->position = indice;
    fourmi->origine = origine;

    while (origine->suivant != NULL) {
        origine = origine->suivant;
    }

    origine->suivant = fourmi;
    fourmi->precedant = origine;
    fourmi->suivant = NULL;

    if (!estLibre(monde, indice)) {
        printf("case occupee -> voisin\n");

        temp = monde->plateau->cases[indice].fourmi;
        while (temp->voisinSuiv != NULL) {
            temp = temp->voisinSuiv;
        }
        temp->voisinSuiv = fourmi;
        fourmi->voisinPrec = temp;
        fourmi->voisinSuiv = NULL;
    } else {
        fourmi->voisinPrec = NULL;
        fourmi->voisinSuiv = NULL;
        monde->plateau->cases[indice].fourmi = fourmi;
    }

}

void creationFourmiliere(Monde *monde, Couleur couleur, int indice, int instruction) {

    Fourmi *fourmi = calloc(1, sizeof(Fourmi));
    Fourmi *temp;
    Fourmi *tempVoisin;

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->position = indice;
    fourmi->type = FOURMILIERE;
    fourmi->instruction = (Instruction) instruction;
    fourmi->origine = fourmi;

    switch (couleur) {
        case ROUGE:
            temp = monde->rouge;
            break;

        case NOIR:
            temp = monde->noire;
            break;

        default:
            temp = NULL;
            break;
    }

    if (temp == NULL) {

        if (couleur == NOIR) {
            monde->noire = fourmi;
        } else {
            monde->rouge = fourmi;
        }
        monde->plateau->cases[indice].fourmi = fourmi;
        fourmi->voisinSuiv = NULL;
        fourmi->voisinPrec = NULL;
        fourmi->fourmiliereSuiv = NULL;
        fourmi->fourmilierePrec = NULL;
    } else {


        while (temp->fourmiliereSuiv != NULL) {
            temp = temp->fourmiliereSuiv;
        }

        temp->fourmiliereSuiv = fourmi;
        fourmi->fourmilierePrec = temp;
        fourmi->fourmiliereSuiv = NULL;

        if (!estLibre(monde, indice)) {
            printf("case occupee -> voisin\n");

            tempVoisin = monde->plateau->cases[indice].fourmi;
            tempVoisin->voisinPrec = fourmi;
            fourmi->voisinSuiv = tempVoisin;
            fourmi->voisinPrec = NULL;
            monde->plateau->cases[indice].fourmi = fourmi;
        }
        else {
            fourmi->voisinPrec = NULL;
            fourmi->voisinSuiv = NULL;
            monde->plateau->cases[indice].fourmi = fourmi;
        }
    }

}

void transformeFourmi(Monde *monde, Fourmi *reine) {

    Couleur couleur;
    int indice;

    couleur = reine->couleur;
    indice = reine->position;

    supprimeAgent(monde, reine);
    creationFourmiliere(monde, couleur, indice, AUCUNE);
}

void supprimeAgent(Monde *monde, Fourmi *fourmi) {

    Fourmi *temp;
    temp = fourmi;

    int indice = fourmi->position;

    if (temp->suivant != NULL) {
        temp->suivant->precedant = temp->precedant;
    }
    temp->precedant->suivant = temp->suivant;


    if (temp->voisinSuiv != NULL) {
        temp->voisinSuiv->voisinPrec = temp->voisinPrec;
    }
    if (temp->voisinPrec != NULL) {
        temp->voisinPrec->voisinSuiv = temp->voisinSuiv;
    }

    if (monde->plateau->cases[indice].fourmi == temp) {
        if (temp->voisinSuiv != NULL) {
            monde->plateau->cases[indice].fourmi = temp->voisinSuiv;
        } else {
            monde->plateau->cases[indice].fourmi = NULL;
        }
    }
/*
    if (temp->voisinSuiv != NULL && temp->voisinPrec != NULL) {
        temp->voisinSuiv->voisinPrec = temp->voisinPrec;
        temp->voisinPrec->voisinSuiv = temp->voisinSuiv;
        monde->plateau->cases[indice].fourmi = temp->voisinSuiv;
    } else if (temp->voisinSuiv != NULL && temp->voisinPrec == NULL) {
        temp->voisinSuiv->voisinPrec = NULL;
        monde->plateau->cases[indice].fourmi = temp->voisinSuiv;
    } else if (temp->voisinSuiv == NULL && temp->voisinPrec != NULL) {
        temp->voisinPrec->voisinSuiv = NULL;
        monde->plateau->cases[indice].fourmi = temp->voisinPrec;
    } else {
        monde->plateau->cases[indice].fourmi = NULL;
    }
*/
    free(temp);
}

void priseFourmiliere(Monde *monde, Fourmi *fourmiliere, Fourmi *ennemie) {

    Fourmi *temp;
    temp = fourmiliere;

    while (temp->suivant != NULL) {

        if (temp->suivant->type != OUVRIERE) {
            supprimeAgent(monde, temp->suivant);
        } else {
            changeCouleur(monde, temp->suivant, ennemie);
        }
    }
    supprimeFourmiliereFin(monde, temp);
    affichePlateau(monde->plateau);

}

void supprimeFourmiliere(Monde *monde, Fourmi *fourmiliere) {

    Fourmi *temp;
    temp = fourmiliere;


    while (temp->suivant != NULL) {
        supprimeAgent(monde, temp->suivant);
    }
    supprimeFourmiliereFin(monde, temp);
    affichePlateau(monde->plateau);
}

void supprimeFourmiliereFin(Monde *monde, Fourmi *fourmiliere) {

    Fourmi *temp;
    temp = fourmiliere;

    int indice = fourmiliere->position;

    if (temp->fourmiliereSuiv != NULL) {
        temp->fourmiliereSuiv->fourmilierePrec = temp->fourmilierePrec;
    }
    if (temp->fourmilierePrec != NULL) {
        temp->fourmilierePrec->fourmiliereSuiv = temp->fourmiliereSuiv;
    }

    if ((temp == monde->rouge || temp == monde->noire) && temp->fourmiliereSuiv != NULL) {
        if (temp == monde->rouge) {
            monde->rouge = temp->fourmiliereSuiv;
        } else {
            monde->noire = temp->fourmiliereSuiv;
        }
    } else if ((temp == monde->rouge || temp == monde->noire) && temp->fourmiliereSuiv == NULL) {
        if (temp == monde->rouge) {
            monde->rouge = NULL;
        } else {
            monde->noire = NULL;
        }
    }

    free(temp);
    monde->plateau->cases[indice].fourmi = NULL;

}

void changeCouleur(Monde *monde, Fourmi *fourmi, Fourmi *ennemie) {

    Couleur couleur;
    int indice = fourmi->position;

    if (fourmi->couleur == ROUGE) {
        couleur = NOIR;
    } else {
        couleur = ROUGE;
    }

    supprimeAgent(monde, fourmi);
    creationFourmi(monde, ennemie->origine, couleur, OUVRIERE, indice, AUCUNE);

}

void suicideFourmi(Monde *monde, Fourmi *fourmi) {

    if (fourmi->type == FOURMILIERE) {
        supprimeFourmiliere(monde, fourmi);
    } else {
        supprimeAgent(monde, fourmi);
    }

}

int chercheFourmiliere(Fourmi *fourmi) {

    int test = 0;
    Fourmi *temp;

    temp = fourmi;
    while (temp->voisinSuiv != NULL) {
        if (temp->type == FOURMILIERE) test = 1;
        temp = temp->voisinSuiv;
    }

    while (temp->voisinPrec != NULL) {
        if (temp->type == FOURMILIERE) test = 1;
        temp = temp->voisinPrec;
    }

    return test;
}

Monde *creationMonde() {
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

    //Creation fourmilieres rouge et noire
    myWorld->noire = initialisation(NOIR, plateau);
    myWorld->rouge = initialisation(ROUGE, plateau);

    //Creation all
    creationFourmi(myWorld, myWorld->rouge, ROUGE, REINE, 1, AUCUNE);
    creationFourmi(myWorld, myWorld->noire, NOIR, REINE, taille - 2, AUCUNE);
    creationFourmi(myWorld, myWorld->rouge, ROUGE, OUVRIERE, cote, AUCUNE);
    creationFourmi(myWorld, myWorld->noire, NOIR, OUVRIERE, taille - cote - 1, AUCUNE);

    /*myWorld->noire->suivant = initialReine(NOIR, plateau, myWorld->noire);
    myWorld->rouge->suivant = initialReine(ROUGE, plateau, myWorld->rouge);
    
    Creation ouvrieres
    myWorld->noire->suivant->suivant = initialOuvriere(NOIR, plateau, myWorld->noire->suivant);
    myWorld->rouge->suivant->suivant = initialOuvriere(ROUGE, plateau, myWorld->rouge->suivant);*/

    myWorld->tresorNoire = TRESOR;
    myWorld->tresorRouge = TRESOR;

    return myWorld;
}