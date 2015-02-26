#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "init.h"

Fourmi *initialisation(Couleur couleur, Plateau *plateau) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = FOURMILIERE;
    fourmi->instruction = AUCUNE;

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
    Fourmi * temp; 

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = typefourmi;
    fourmi -> instruction = AUCUNE; 
    fourmi -> position = indice; 

    while (origine->suivant != NULL) {
        origine = origine->suivant;
    }

    origine->suivant = fourmi;
    fourmi->precedant = origine;
    fourmi->suivant = NULL;

    if (!estLibre(myWorld, indice)) {
        printf("case occupee dsl");

        temp = myWorld -> plateau -> cases[indice].fourmi;
        while (temp -> voisinSuiv != NULL){
            temp = temp -> voisinSuiv; 
        }
        temp -> voisinSuiv = fourmi; 
        fourmi -> voisinPrec = temp; 
        fourmi -> voisinSuiv = NULL; 
    } else {
        fourmi -> voisinPrec = NULL; 
        fourmi -> voisinSuiv = NULL; 
        myWorld->plateau->cases[indice].fourmi = fourmi;
    }

    
}


void creationFourmiliere(Couleur couleur, Monde * myWorld , int indice){
    
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));
    Fourmi * temp; 
    
    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }
    
    fourmi -> couleur = couleur; 
    fourmi -> position = indice; 
    fourmi -> type = FOURMILIERE; 
    fourmi -> instruction = AUCUNE; 

    switch (couleur){
        case ROUGE: 
            temp = myWorld -> rouge; 
            break;
            
        case NOIR: 
            temp = myWorld -> noire; 
            break;
    }
    
    while (temp -> fourmiliereSuiv !=NULL){
        temp = temp -> fourmiliereSuiv; 
    }
    
    temp -> fourmiliereSuiv = fourmi; 
    fourmi -> fourmilierePrec = temp; 
    fourmi -> fourmiliereSuiv = NULL;
    
    myWorld->plateau->cases[indice].fourmi = fourmi;
    
}


void transformeFourmi (Fourmi* fourmi, Monde*myWorld){
    
    creationFourmiliere(fourmi -> couleur, myWorld, fourmi -> position); 
    supprimeAgent(fourmi, myWorld); 
    
}


void supprimeAgent(Fourmi *fourmi, Monde *myWorld){
    
    Fourmi *temp;
    temp = fourmi;
    
    int indice= fourmi->position;
    
    printf("indice de la fourmi a supprimer = %d\n", fourmi->position);
    if (temp->suivant != NULL) {
        temp->suivant->precedant = temp->precedant;
    }
    temp->precedant->suivant = temp->suivant;
    
    myWorld->plateau->cases[indice].fourmi = NULL;
    free(temp);
    
    printf("fin suicide\n");
}


void priseFourmiliere (Fourmi *fourmi, Monde *myWorld, Fourmi * ennemie){
    printf("priseFourmiliere");
    
    Fourmi *temp;
    temp = fourmi;
    int indice = fourmi -> position; 
    
    while (temp -> suivant != NULL){

        if (temp -> suivant -> type != OUVRIERE){
            supprimeAgent(temp->suivant, myWorld);
        } else {
            printf("je change de couleur mon ouvriere\n"); 
            changeCouleur(myWorld, temp -> suivant , ennemie); 
        }
        
        printf ("indice de la fourmi %d\n", temp -> suivant-> position); 
        printf("type de la fourmi: %d\n", temp -> suivant -> type); 
        temp = temp -> suivant;
        affichePlateau(myWorld->plateau);
    }
    
    supprimeFourmiliereFin(myWorld -> plateau -> cases[indice].fourmi, myWorld);
    affichePlateau(myWorld->plateau);
    
}

void supprimeFourmiliere (Fourmi* fourmi, Monde * myWorld){
    
    Fourmi *temp;
    temp = fourmi; 
    
    
    while (temp->suivant != NULL){
        supprimeAgent(temp->suivant, myWorld); 
        affichePlateau(myWorld->plateau);
    }
    printf("indice fourmiliere fin = %d\n", temp->position);
    printf("fourmi case 24 = %d\n", (int) myWorld -> plateau -> cases[24].fourmi -> type);
    supprimeFourmiliereFin(temp, myWorld); 
    
}

void supprimeFourmiliereFin(Fourmi* fourmi, Monde * myWorld){
    
    Fourmi *temp;
    temp = fourmi;
    
    int indice= fourmi->position;
    printf("indice ? = %d\n", indice);
    if (temp->fourmiliereSuiv != NULL) {
        temp->fourmiliereSuiv->fourmilierePrec = temp->fourmilierePrec;
    }
    if (temp->fourmilierePrec != NULL) {
        temp->fourmilierePrec->fourmiliereSuiv = temp->fourmiliereSuiv;
    }
    
    myWorld->plateau->cases[indice].fourmi = NULL;
}

void changeCouleur(Monde *myWorld, Fourmi* fourmi, Fourmi *ennemie){
    
    enum Couleur couleur;
    int indice = fourmi -> position; 
    
    if (fourmi-> couleur == ROUGE){
        couleur = NOIR;
    } else {
        couleur = ROUGE; 
    }
    
    supprimeAgent(fourmi, myWorld); 
    creationFourmi(couleur, OUVRIERE, ennemie-> origine, myWorld, indice);
    
    /*
    while (ennemie -> suivant != NULL){
        ennemie = ennemie -> suivant; 
    }
    
    temp -> instruction = AUCUNE;
    temp -> origine = ennemie -> origine; 
    temp -> precedant = ennemie; 
    ennemie -> suivant = temp; 
    temp -> suivant = NULL; 
    */
}
    
void suicideFourmi (Fourmi * fourmi, Monde * myWorld){
    
    if (fourmi -> type == FOURMILIERE){
        supprimeFourmiliere (fourmi, myWorld); 
    } else {
        supprimeAgent(fourmi, myWorld); 
    }
    
}


int chercheFourmiliere (Fourmi * fourmi, Monde * myWorld) {
    
    int test = 0; 
    Fourmi * temp; 
    
    temp = fourmi; 
    while ( temp -> voisinSuiv != NULL){
        if (temp-> type == FOURMILIERE)  test = 1; 
        temp = temp -> voisinSuiv; 
    }
    
    while (temp -> voisinPrec != NULL){
        if (temp -> type == FOURMILIERE) test = 1; 
        temp = temp -> voisinPrec; 
    }
    
    return test; 
}



Monde *creationMonde() {
    //Creation Monde
    Monde *myWorld = calloc(1, sizeof(Monde));

    //Creation plateau
    int cotePlateau = COTE;
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