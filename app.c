#include <stdio.h>
#include <stdlib.h>
#include "app.h"

#define TMAX 256

//SUPPRIME FOURMI, A FAIRE ET A METTRE DANS INIT


void supprimeFourmi (Fourmi * fourmi, Monde * myWorld){
    
    int indice = fourmi -> position;
    Fourmi* tmp1 = calloc(1, sizeof(Fourmi)); 
    Fourmi* tmp2 = calloc(1, sizeof(Fourmi)); 
    
    //printf("le type de la fourmi:%d\n", fourmi->type );
    //printf("le type de la fourmi suivante:%d\n", fourmi->suivant->type );
    
    if ( fourmi -> type != FOURMILIERE){
        tmp1 = fourmi; 
        tmp1 -> precedant -> suivant = tmp1 -> suivant; 
        tmp1 -> suivant -> precedant = tmp1 -> precedant; 
        free (fourmi); 
    }
    
    else { // si c fourmiliere 
        
        while (fourmi != NULL){
            
            
            if (fourmi -> type != OUVRIERE){
                tmp1=fourmi;
                printf(" type de fourmi: %d\n", tmp1 -> type );
                fourmi = fourmi -> suivant;
                fourmi-> precedant = NULL; 
                free(tmp1); 
            }
                
            else { // si c'est une ouvriere 
                
                tmp1= fourmi;
                printf("le ** type de la fourmi est :%d\n", fourmi -> type);
                
                if (fourmi -> couleur == ROUGE){
                    tmp1 -> couleur = NOIR;
                    tmp2 = myWorld -> noire; 
                    printf("la position de la fourmiliere noire: %d\n", myWorld -> noire-> position);
                    while (tmp2 -> suivant != NULL){
                        tmp2 = tmp2 -> suivant; 
                    }
                    tmp1 -> precedant = tmp2; 
                    tmp2 -> suivant = tmp1; 
                    tmp1 -> suivant = NULL; 
                } else {
                    tmp1 -> couleur = ROUGE; 
                    tmp2 = myWorld -> rouge; 
                    while (tmp2 -> suivant != NULL){
                        tmp2 = tmp2 -> suivant; 
                    }
                    tmp1 -> precedant = tmp2; 
                    tmp2 -> suivant= tmp1; 
                    tmp1 -> suivant = NULL; 
                }
                
                fourmi = fourmi -> suivant; 
            }
    
        }
        
    }
    myWorld -> plateau -> cases[indice].fourmi = NULL; 
    
}

