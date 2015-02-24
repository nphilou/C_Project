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

void creationFourmi(Couleur couleur, TypeFourmi typefourmi, Fourmi *origine, Monde *myWorld, int indice) {

    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = typefourmi;

    while (origine->suivant != NULL) {
        origine = origine->suivant;
    }

    origine->suivant = fourmi;
    fourmi->precedant = origine;
    fourmi->suivant = NULL;

    if (!estLibre(myWorld, indice)) {
        printf("case occupée try again\n");
        return;
    }

    myWorld->plateau->cases[indice].fourmi = fourmi;
}

void supprimeAgent(Fourmi *fourmi, Monde *myWorld){
    
    Fourmi *temp;
    temp = fourmi;

    int indice= fourmi->position;
    myWorld->plateau->cases[indice].fourmi = NULL;
    
    if (temp->suivant != NULL) {
        temp->suivant->precedant = temp->precedant;
    }
    
    temp->precedant->suivant = temp->suivant;
    
    free(fourmi);
}

void priseFourmiliere (Fourmi *fourmi, Monde *myWorld, Fourmi * ennemie){
    
    Fourmi *temp;
    
    
    while (fourmi -> suivant != NULL){
        
        temp = fourmi;
        if (temp -> type != OUVRIERE){
            supprimeAgent(temp, myWorld);
        } else {
            changeCouleur(temp, temp-> couleur, myWorld, ennemie); 
        }
        fourmi= fourmi -> suivant; 
    }
}

void supprimeFourmiliere (Fourmi* fourmi, Monde * myWorld){
    
    Fourmi *temp;
    
    while (fourmi -> suivant != NULL){
        temp= fourmi;
        supprimeAgent(temp, myWorld); 
        fourmi = fourmi -> suivant; 
    }
}

void changeCouleur(Fourmi* fourmi, Couleur couleur, Monde *myWorld, Fourmi *ennemie){
    
    Fourmi * temp =calloc(1, sizeof(Fourmi));
    temp = fourmi;
    
    switch(fourmi-> couleur){
        case(ROUGE): 
            fourmi-> couleur = NOIR;
            break;
        case(NOIR):
            fourmi -> couleur = ROUGE; 
            break;
    }
    
    
    while (ennemie -> suivant != NULL){
        ennemie = ennemie -> suivant; 
    }
    
    temp -> instruction = AUCUNE;
    temp -> origine = ennemie -> origine; 
    temp -> precedant = ennemie; 
    ennemie -> suivant = temp; 
    temp -> suivant = NULL; 
    
}
    
void suicideFourmi (Fourmi * fourmi, Monde * myWorld){
    
    if (fourmi -> type == FOURMILIERE){
        supprimeFourmiliere(fourmi, myWorld); 
    } else {
        supprimeAgent(fourmi, myWorld); 
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
    creationFourmi(NOIR, REINE, myWorld->noire, myWorld, taille-2);
    creationFourmi(ROUGE, OUVRIERE, myWorld->rouge, myWorld, cote); 
    creationFourmi(NOIR, OUVRIERE, myWorld->noire, myWorld, taille - cote-1);
    
    /*myWorld->noire->suivant = initialReine(NOIR, plateau, myWorld->noire);
    myWorld->rouge->suivant = initialReine(ROUGE, plateau, myWorld->rouge);

    Creation ouvrieres
    myWorld->noire->suivant->suivant = initialOuvriere(NOIR, plateau, myWorld->noire->suivant);
    myWorld->rouge->suivant->suivant = initialOuvriere(ROUGE, plateau, myWorld->rouge->suivant);*/

    myWorld->tresorNoire = TRESOR;
    myWorld->tresorRouge = TRESOR;

    return myWorld;
}

//A CONTINUER TRANQUILLEMENT 
/*
void afficheMonde(Monde *myWorld, Fourmi *origine){
    Fourmi *listeFourmiliere = origine;
    
    while (listeFourmiliere != NULL) {
        listeFourmi = listeFourmiliere;
        while (listeFourmi != NULL) {
            switch(listeFourmi->type){
                case(FOURMILIERE):
                        printf("type = FOURMILIERE, ");
                        break;

                    case(REINE):
                        instruction = demandeInstructionReine(myWorld, listeFourmi);
                        break;

                    case(SOLDAT):
                        instruction = demandeInstructionSoldat(myWorld, listeFourmi);
                        break;

                    case(OUVRIERE):
                        instruction = demandeInstructionOuvriere(myWorld, listeFourmi);
                    
            }
        }
    }
}
*/