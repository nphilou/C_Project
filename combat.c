#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"



void combatFourmi ( Fourmi * fourmi , Fourmi* fourmi2, Monde * myWorld){
   
   int scoreFourmi = 0; 
   int indice = fourmi2 -> position; 
   
   if (fourmi-> type == SOLDAT && fourmi2->type != SOLDAT){
        srand(time(NULL)); 
        scoreFourmi= rand()%101; 
        if (scoreFourmi >= 25){
            printf (" vous avez remporté le combat"); 
            myWorld->plateau -> cases[indice].fourmi= fourmi; 
            supprimeFourmi (fourmi2, myWorld); 
        } else {
            printf("vous avez perdu le combat");
            supprimeFourmi (fourmi, myWorld); 
            return;
        }
   }
   
    if (fourmi->type != SOLDAT && fourmi2->type == SOLDAT){
        srand(time(NULL)); 
        scoreFourmi= rand()%101; 
        if (scoreFourmi <= 25){
            printf (" vous avez remporté le combat"); 
            myWorld->plateau -> cases[indice].fourmi= fourmi; 
            supprimeFourmi (fourmi2, myWorld); 
        } else {
            printf("vous avez perdu le combat");
            supprimeFourmi (fourmi, myWorld); 
            return;
        }
    }
    
    if (fourmi -> type != SOLDAT && fourmi2 ->type != SOLDAT){
        srand(time(NULL)); 
        scoreFourmi= rand()%101; 
        do {
            if (scoreFourmi > 50){
                printf (" vous avez remporté le combat"); 
                myWorld->plateau -> cases[indice].fourmi= fourmi; 
                supprimeFourmi (fourmi2, myWorld); 
            } else {
                printf("vous avez perdu le combat");
                supprimeFourmi (fourmi, myWorld); 
                return;
            }
        } while (scoreFourmi==50);
    }
}
