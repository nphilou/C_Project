#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"


void combatFourmi(Fourmi * attaque, Fourmi * defense, Monde *myWorld) {  

    int scoreFourmi = 0;
    int indice = defense->position; 

    if (attaque->type == SOLDAT && defense->type != SOLDAT) {
        srand(time(NULL));
        scoreFourmi = rand() % 101;
        if (scoreFourmi >= 25) {
            printf(" vous avez remporté le combat\n");
            myWorld->plateau->cases[indice].fourmi = attaque;
            supprimeFourmi(myWorld, defense, attaque); 
            return;
        } else {
            printf("vous avez perdu le combat\n");
            supprimeAgent(attaque, myWorld);
            return;
        }
    }

    if (attaque->type != SOLDAT && defense ->type == SOLDAT) {
        srand(time(NULL));
        scoreFourmi = rand() % 101;
        if (scoreFourmi <= 25) {
            printf(" vous avez remporté le combat\n");
            myWorld->plateau->cases[indice].fourmi = attaque;
            supprimeAgent(defense, myWorld);
            return;
        } else {
            printf("vous avez perdu le combat\n");
            supprimeFourmi (myWorld, attaque, defense); 
            return; 
        }
    }


    if (attaque->type != SOLDAT && defense->type != SOLDAT) {
        srand(time(NULL));
        scoreFourmi = rand() % 101;
        do {
            if (scoreFourmi > 50) {
                printf(" vous avez remporté le combat\n");
                myWorld->plateau->cases[indice].fourmi = attaque;
                supprimeFourmi (myWorld, defense, attaque);
                return; 
            } else {
                printf("vous avez perdu le combat\n");
                supprimeFourmi (myWorld, attaque, defense); 
                return;
            }
        } while (scoreFourmi == 50);
    }
}

void supprimeFourmi (Monde * myWorld, Fourmi * aSupprimer,  Fourmi * gagnante){
    
    int type = aSupprimer-> type; 
    
    if (type == FOURMILIERE){
        priseFourmiliere(aSupprimer, myWorld, gagnante); 
    } else {
        supprimeAgent (aSupprimer, myWorld); 
    }
}