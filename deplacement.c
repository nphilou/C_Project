#include <stdio.h>
#include <stdlib.h>
#include "deplacement.h"

void demandeDestination(int *abscisse, int *ordonnee, Monde *monde) {
    int tmp0, tmp1;
    do {
        printf("Donnez une destination : abscisse ? \n");
        scanf("%d", &tmp0);
        *abscisse = tmp0;
        printf("ordonnee ? \n");
        scanf("%d", &tmp1);
        *ordonnee = tmp1;

    } while (map(tmp0, tmp1, monde->plateau->cote) < 0);//A CONTINUER
}

void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int x, int y) {


    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;


    if (xF != x && yF != y) {
        if (xF > x && yF < y) {
            indice = map(xF - 1, yF + 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
        }
        if (xF < x && yF > y) {
            indice = map(xF + 1, yF - 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
        }
        if (xF < x && yF < y) {
            indice = map(xF + 1, yF + 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
            else {
                printf("the location is not empty");
            }
        }
        if (xF > x && yF > y) {
            indice = map(xF - 1, yF - 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
            else {
                printf("the location is not empty");
            }
        }
    }
    else if (xF == x || yF == y) {
        if (yF == y && xF != x) {
            if (xF > x) {
                indice = map(xF - 1, yF, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }
            }
            else {
                indice = map(xF + 1, yF, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }

            }
        }
        if (yF != y && xF == x) {
            if (yF < y) {
                indice = map(xF, yF + 1, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }
            }
            else {
                indice = map(xF, yF - 1, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }
            }
        }
        return;
    }
}