#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "structures.h"
#include "combat.h"
#include "init.h"

int combatFourmi(Monde *myWorld, Fourmi *attaque, Fourmi *defense) {

    int scoreFourmi = 0;
    //int indice = defense->position;

    if (attaque->type == SOLDAT && defense->type != SOLDAT) {
        srand((unsigned int) time(NULL));
        scoreFourmi = rand() % 100;
        if (scoreFourmi >= FORCE_AGENT_VS_SOLDAT) {
            printf(" vous avez remporté le combat\n");
            supprimeFourmi(myWorld, defense, attaque);
            return 1;
        } else {
            printf("vous avez perdu le combat\n");
            supprimeAgent(attaque, myWorld);
            return 0;
        }
    }

    if (attaque->type != SOLDAT && defense->type == SOLDAT) {
        srand((unsigned int) time(NULL));
        scoreFourmi = rand() % 100;
        if (scoreFourmi <= FORCE_AGENT_VS_SOLDAT) {
            printf(" vous avez remporté le combat\n");
            supprimeAgent(defense, myWorld);
            return 1;
        } else {
            printf("vous avez perdu le combat\n");
            supprimeFourmi(myWorld, attaque, defense);
            return 0;
        }
    }


    if ((attaque->type != SOLDAT && defense->type != SOLDAT) || (attaque->type == SOLDAT && defense->type == SOLDAT)) {

        srand((unsigned int) time(NULL));

        do {
            scoreFourmi = rand() % 100;
            if (scoreFourmi > 50) {
                printf(" vous avez remporté le combat\n");
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

void supprimeFourmi(Monde *myWorld, Fourmi *aSupprimer, Fourmi *gagnante) {

    int type = aSupprimer->type;

    if (type == FOURMILIERE) {
        printf("je dois supprimer la fourmiliere\n");
        priseFourmiliere(aSupprimer, myWorld, gagnante);
    } else {
        supprimeAgent(aSupprimer, myWorld);
    }
}