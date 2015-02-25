#include <stdio.h>
#include <stdlib.h>
#include "deplacement.h"

void demandeDestination(int *abscisse, int *ordonnee, Monde *monde, Fourmi *fourmi) {
    int tmp0, tmp1;
    do {
        printf("Donnez une destination : abscisse ? \n");
        scanf("%d", &tmp0);
        *abscisse = tmp0;
        printf("ordonnee ? \n");
        scanf("%d", &tmp1);
        *ordonnee = tmp1;

    } while (map(tmp0, tmp1, monde->plateau->cote) < 0);
    fourmi->destination = map(tmp0, tmp1, monde->plateau->cote);
}

// si xF < *abscisse
void deplacementEst(Monde *myWorld, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;

    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (yF > ordonnee) {
        indice = map(xF + 1, yF - 1, cote);
        //if (!estLibre(myWorld, indice)) {
    } else if (yF == ordonnee) {
        indice = map(xF + 1, yF, cote);
        //if (!estLibre(myWorld, indice)) { // 1.COMBAT   ou 2. AJOUT FOURMI LISTE CHAINE CASE 
    } else {
        indice = map(xF + 1, yF + 1, cote);
        //if (!estLibre(myWorld, indice) && myWorld->plateau->cases[indice].fourmi->couleur != fourmi->couleur) {
    }
    
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
} //A REPRODUIRE !!! ;)

// if xF> *abscisse
void deplacementOuest(Monde *myWorld, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;

    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (yF > ordonnee) {
        indice = map(xF - 1, yF - 1, cote);
        //if (estLibre(myWorld, indice)) {
    }
    else if (yF == ordonnee) {
        indice = map(xF - 1, yF, cote);
        //if (estLibre(myWorld, indice)) {
        
    }
    else {
        indice = map(xF - 1, yF + 1, cote);
        //if (estLibre(myWorld, indice)) {
        
    }
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
}

//if yF < *ordonnee
void deplacementSud(Monde *myWorld, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;

    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (xF > abscisse) {
        indice = map(xF - 1, yF + 1, cote);
        //if (estLibre(myWorld, indice)) {
    }
    else if (xF == abscisse) {
        indice = map(xF, yF + 1, cote);
        //if (estLibre(myWorld, indice)) {
    }
    else {
        indice = map(xF + 1, yF + 1, cote);
        //if (estLibre(myWorld, indice)) {
    }
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
}

// if yF > *ordonnee
void deplacementNord(Monde *myWorld, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;

    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (xF > abscisse) {
        indice = map(xF - 1, yF - 1, cote);
        //if (estLibre(myWorld, indice)) {
    }
    else if (xF == abscisse) {
        indice = map(xF, yF - 1, cote);
        //if (estLibre(myWorld, indice)) {
    }
    else {
        indice = map(xF + 1, yF - 1, cote);
        //if (estLibre(myWorld, indice)) {
    }
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
}

void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int abscisse, int ordonnee) {


    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    fourmi->destination = map(abscisse, ordonnee, myWorld->plateau->cote);

    myWorld->plateau->cases[caseInitial].fourmi = NULL;

   

    if (xF < abscisse) {
        deplacementEst(myWorld, fourmi,  ordonnee);
    }
    else if (xF > abscisse) {
        deplacementOuest(myWorld, fourmi, ordonnee);
    }
    else if (yF < ordonnee) {
        deplacementSud(myWorld, fourmi, abscisse);
    }
    else if (yF > ordonnee) {
        deplacementNord(myWorld, fourmi, abscisse);
    }

    xF = chercheAbscisse(myWorld, fourmi->position);
    yF = chercheOrdonnee(myWorld, fourmi->position);
    //printf("***l'abscisse de la fourmi: %d, l'ordonnee: %d\n", xF, yF);

    //affichePlateau(myWorld->plateau);
}

