#include <stdio.h>
#include <stdlib.h>
#include "app.h"

#define TMAX 256

/*
void sauvegarde (Monde* myWorld){
    // ttes fourmi: fourmiliere/ouviere/soldat/reine par equipe 
    // leur position 
    // derniere instruction pour chaque fourmi
    // tresor
    // a qui le tour de jouer !! 
    
    
    FILE *file = fopen (" derniere sauvegarde.txt", "w+"); 
    
    Fourmi *temp;
    
    temp = myWorld -> rouge; 
    fprintf (file, "%d %d\n", temp-> couleur, myWorld -> tresorRouge);
    while (temp -> fourmiliereSuiv!= NULL){
        while (temp -> voisinSuiv != NULL){
            while ( temp -> suivant != NULL){
                fprintf (file, "%d %d %d\n", temp -> type, temp > indice, temp-> instruction);
                temp = temp -> suivant; 
            }
            temp = temp ->voisinSuiv; 
        }
        temp = temp -> fourmiliereSuiv;
    } 
    
    temp = myWorld -> noire; 
    fprintf (file, "%d %d\n", temp-> couleur, myWorld -> tresorNoire);
    while (temp -> voisinSuiv != NULL){
        while (temp -> suivant != NULL){
            fprintf (file, "%d %d %d\n", temp -> type, temp > indice, temp-> instruction);
            temp = temp -> suivant; 
        }
        temp = temp -> voisinSuiv; 
    } 
    
}

void chargement (Monde*myWorld){
    
    FILE * file = fopen("derniere sauvegarde.txt", "r"); 
    
    if(f==NULL){
        printf("error");
        exit(EXIT_FAILURE);
    }
    
    int element; 
    do {
        element = fgetc (file);
        
        
    
    } while ( element != EOF); 
    
    fclose (file);
    
}
*/