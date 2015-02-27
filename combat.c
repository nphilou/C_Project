#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"


int combatFourmi(Fourmi * attaque, Fourmi * defense, Monde *myWorld) {

    int scoreFourmi = 0;
    //int indice = defense->position;

    if (attaque->type == SOLDAT && defense->type != SOLDAT) {
        srand(time(NULL));
        scoreFourmi = rand() % 101;
        if (scoreFourmi >= FORCE_AGENT_VS_SOLDAT) {
            printf(" vous avez remporté le combat\n");
            //myWorld->plateau->cases[indice].fourmi = attaque;
            //attaque -> position= indice;
            supprimeFourmi(myWorld, defense, attaque);
            return 1;
        } else {
            printf("vous avez perdu le combat\n");
            supprimeAgent(attaque, myWorld);
            return 0;
        }
    }

    if (attaque->type != SOLDAT && defense ->type == SOLDAT) {
        srand((unsigned int) time(NULL));
        scoreFourmi = rand() % 101;
        if (scoreFourmi <= FORCE_AGENT_VS_SOLDAT) {
            printf(" vous avez remporté le combat\n");
            //myWorld->plateau->cases[indice].fourmi = attaque;
            //attaque -> position = indice;
            supprimeAgent(defense, myWorld);
            return 1;
        } else {
            printf("vous avez perdu le combat\n");
            supprimeFourmi (myWorld, attaque, defense);
            return 0;
        }
    }


    if (attaque->type != SOLDAT && defense->type != SOLDAT) {

        srand((unsigned int) time(NULL));

        do {
            scoreFourmi = rand() % 101;
            if (scoreFourmi > 50) {
                printf(" vous avez remporté le combat\n");
               // myWorld->plateau->cases[indice].fourmi = attaque;
                //attaque -> position = indice;
                supprimeFourmi(myWorld, defense, attaque);
                return 1;
            } else if (scoreFourmi < 50) {
                printf("vous avez perdu le combat\n");
                supprimeFourmi(myWorld, attaque, defense);
                return 0;
            }
        } while (scoreFourmi == 50);
    }
    return -1;
}

void supprimeFourmi (Monde * myWorld, Fourmi * aSupprimer,  Fourmi * gagnante){

    int type = aSupprimer-> type;

    if (type == FOURMILIERE){
        printf("je dois supprimer la fourmiliere\n");
        priseFourmiliere(aSupprimer, myWorld, gagnante);
    } else {
        supprimeAgent (aSupprimer, myWorld);
    }
}