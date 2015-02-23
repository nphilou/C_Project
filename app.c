#include <stdio.h>
#include <stdlib.h>
#include "app.h"

#define TMAX 256

//SUPPRIME FOURMI, A FAIRE ET A METTRE DANS INIT

void supprimeFourmi (Fourmi*fourmi, Monde*myWorld, Fourmi * fourmiAttaquante){
    
    Fourmi* tmp1 = calloc(1, sizeof(Fourmi)); 
    Fourmi* autreEquipe = calloc(1, sizeof(Fourmi)); 
    int indice; 
    
    
    if (fourmi-> type != FOURMILIERE){
        
        printf("je supprime l'ouvriere noire\n");
        indice = fourmi -> position; 
        tmp1 = fourmi; 
        
        if ( tmp1 -> suivant != NULL){
            tmp1 -> precedant -> suivant = tmp1 -> suivant; 
            tmp1 -> suivant -> precedant = tmp1 -> precedant; 
        }
        else {
            tmp1 -> precedant -> suivant = NULL; 
        }
        free (fourmi); 
        myWorld -> plateau -> cases[indice].fourmi = NULL; 
    }
    
    else {  // FOURMILIERE 
        
        
        while (fourmi -> suivant != NULL){
            
            //tmp1 = calloc(1, sizeof(Fourmi)); 
            affichePlateau(myWorld->plateau);
            indice = fourmi -> position;
            
            if (fourmi -> type != OUVRIERE){
            
                indice = fourmi -> position;
                tmp1 = fourmi; 
                fourmi = fourmi -> suivant;
                fourmi -> precedant = NULL; 
                free(tmp1);
                myWorld -> plateau -> cases[indice].fourmi = NULL; 
                
            }
            
            
            
            else { // si c'est une ouvriere 
                tmp1 = fourmi; 
                if (fourmi -> suivant !=NULL){
                    fourmi-> precedant -> suivant = fourmi -> suivant; 
                    fourmi -> suivant -> precedant = fourmi -> precedant; 
                }
                else {
                    fourmi-> precedant -> suivant = NULL; 
                }
                
                if (tmp1 -> couleur == ROUGE){
                    tmp1 -> couleur = NOIR; 
                    tmp1 -> suivant = NULL; 
                    //tmp1 -> origine = fourmiAttaquante;
                    
                    autreEquipe = myWorld -> noire;
                    while (autreEquipe -> suivant !=NULL){
                        autreEquipe = autreEquipe -> suivant;
                    }
                    tmp1 -> precedant = autreEquipe;
                    autreEquipe -> suivant = tmp1; 
                    
                }
                else {
                    tmp1 -> couleur = ROUGE; 
                    tmp1 -> suivant = NULL; 
                    //tmp1 -> origine = fourmiAttaquante;
                    
                    autreEquipe = myWorld -> rouge;
                    while (autreEquipe -> suivant !=NULL){
                        autreEquipe = autreEquipe -> suivant;
                    }
                    tmp1 -> precedant = autreEquipe;
                    autreEquipe -> suivant= tmp1; 
                    
                }
                
                fourmi= fourmi -> suivant; 
            }
            
        }
    
    }
    
}

