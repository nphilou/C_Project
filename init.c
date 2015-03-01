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
    fourmi->tempsProd = 0;

    return fourmi;
}

void creationFourmi(Couleur couleur, TypeFourmi typefourmi, Fourmi *origine, Monde *myWorld, int indice) {

    Fourmi *fourmi = calloc(1, sizeof(Fourmi));
    Fourmi *temp;

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = typefourmi;
    fourmi->instruction = AUCUNE;
    fourmi->position = indice;
    fourmi->origine = origine;

    while (origine->suivant != NULL) {
        origine = origine->suivant;
    }

    origine->suivant = fourmi;
    fourmi->precedant = origine;
    fourmi->suivant = NULL;

    if (!estLibre(myWorld, indice)) {
        printf("case occupee -> voisin\n");

        temp = myWorld->plateau->cases[indice].fourmi;
        while (temp->voisinSuiv != NULL) {
            temp = temp->voisinSuiv;
        }
        temp->voisinSuiv = fourmi;
        fourmi->voisinPrec = temp;
        fourmi->voisinSuiv = NULL;
    } else {
        fourmi->voisinPrec = NULL;
        fourmi->voisinSuiv = NULL;
        myWorld->plateau->cases[indice].fourmi = fourmi;
    }

}


void creationFourmiliere(Couleur couleur, Monde *myWorld, int indice) {

    Fourmi *fourmi = calloc(1, sizeof(Fourmi));
    Fourmi *temp;

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->position = indice;
    fourmi->type = FOURMILIERE;
    fourmi->instruction = AUCUNE;
    fourmi->origine = fourmi;

    switch (couleur) {
        case ROUGE:
            temp = myWorld->rouge;
            break;

        case NOIR:
            temp = myWorld->noire;
            break;

        default:
            temp = NULL;
            break;
    }

    while (temp->fourmiliereSuiv != NULL) {
        temp = temp->fourmiliereSuiv;
    }

    temp->fourmiliereSuiv = fourmi;
    fourmi->fourmilierePrec = temp;
    fourmi->fourmiliereSuiv = NULL;

    myWorld->plateau->cases[indice].fourmi = fourmi;

}


void transformeFourmi(Fourmi *fourmi, Monde *myWorld) {

    Couleur couleur;
    int indice;

    couleur = fourmi->couleur;
    indice = fourmi->position;

    supprimeAgent(fourmi, myWorld);
    creationFourmiliere(couleur, myWorld, indice);
}


void supprimeAgent(Fourmi *fourmi, Monde *myWorld) {

    Fourmi *temp;
    temp = fourmi;

    int indice = fourmi->position;

    if (temp->suivant != NULL) {
        temp->suivant->precedant = temp->precedant;
    }
    temp->precedant->suivant = temp->suivant;


    if(temp -> voisinSuiv != NULL && temp -> voisinPrec != NULL) {
        temp -> voisinSuiv -> voisinPrec = temp -> voisinPrec;
        temp -> voisinPrec -> voisinSuiv = temp -> voisinSuiv;
        myWorld->plateau->cases[indice].fourmi = temp -> voisinSuiv;
    } else if (temp -> voisinSuiv !=NULL && temp -> voisinPrec == NULL){
        temp -> voisinSuiv ->voisinPrec = NULL;
        myWorld->plateau->cases[indice].fourmi = temp -> voisinSuiv;
    } else if (temp -> voisinSuiv ==NULL && temp -> voisinPrec != NULL){
        temp -> voisinPrec -> voisinSuiv = NULL;
        myWorld->plateau->cases[indice].fourmi = temp -> voisinPrec;
    } else {
        myWorld->plateau->cases[indice].fourmi = NULL;
    }

    free(temp);
}


void priseFourmiliere(Fourmi *fourmi, Monde *myWorld, Fourmi *ennemie) {

    Fourmi *temp;
    temp = fourmi;

    while (temp->suivant != NULL) {

        if (temp->suivant->type != OUVRIERE) {
            supprimeAgent(temp->suivant, myWorld);
        } else {
            changeCouleur(myWorld, temp->suivant, ennemie);
        }
        affichePlateau(myWorld->plateau);
    }

    supprimeFourmiliereFin(temp, myWorld);

}

void supprimeFourmiliere(Fourmi *fourmi, Monde *myWorld) {

    Fourmi *temp;
    temp = fourmi;


    while (temp->suivant != NULL) {
        supprimeAgent(temp->suivant, myWorld);
        affichePlateau(myWorld->plateau);
    }
    supprimeFourmiliereFin(temp, myWorld);

}

void supprimeFourmiliereFin(Fourmi *fourmi, Monde *myWorld) {

    Fourmi *temp;
    temp = fourmi;

    int indice = fourmi->position;
    if (temp->fourmiliereSuiv != NULL) {
        temp->fourmiliereSuiv->fourmilierePrec = temp->fourmilierePrec;
    }
    if (temp->fourmilierePrec != NULL) {
        temp->fourmilierePrec->fourmiliereSuiv = temp->fourmiliereSuiv;
    }

    myWorld->plateau->cases[indice].fourmi = NULL;
}

void changeCouleur(Monde *myWorld, Fourmi *fourmi, Fourmi *ennemie) {

    Couleur couleur;
    int indice = fourmi->position;

    if (fourmi->couleur == ROUGE) {
        couleur = NOIR;
    } else {
        couleur = ROUGE;
    }

    supprimeAgent(fourmi, myWorld);
    creationFourmi(couleur, OUVRIERE, ennemie->origine, myWorld, indice);

}

void suicideFourmi(Fourmi *fourmi, Monde *myWorld) {

    if (fourmi->type == FOURMILIERE) {
        supprimeFourmiliere(fourmi, myWorld);
    } else {
        supprimeAgent(fourmi, myWorld);
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
    creationFourmi(ROUGE, REINE, myWorld->rouge, myWorld, 1);
    creationFourmi(NOIR, REINE, myWorld->noire, myWorld, taille - 2);
    creationFourmi(ROUGE, OUVRIERE, myWorld->rouge, myWorld, cote);
    creationFourmi(NOIR, OUVRIERE, myWorld->noire, myWorld, taille - cote - 1);

    /*myWorld->noire->suivant = initialReine(NOIR, plateau, myWorld->noire);
    myWorld->rouge->suivant = initialReine(ROUGE, plateau, myWorld->rouge);
    
    Creation ouvrieres
    myWorld->noire->suivant->suivant = initialOuvriere(NOIR, plateau, myWorld->noire->suivant);
    myWorld->rouge->suivant->suivant = initialOuvriere(ROUGE, plateau, myWorld->rouge->suivant);*/

    myWorld->tresorNoire = TRESOR;
    myWorld->tresorRouge = TRESOR;

    return myWorld;
}