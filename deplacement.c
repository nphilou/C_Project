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
    //int couleur = fourmi -> couleur; 

    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (yF > ordonnee) {
        indice = map(xF + 1, yF - 1, cote);
    } else if (yF == ordonnee) {
        indice = map(xF + 1, yF, cote);
    } else {
        indice = map(xF + 1, yF + 1, cote);
    }
    
    /*
    if (!estLibre(myWorld, indice)) {
        switch (myWorld -> plateau -> cases[indice].fourmi -> couleur){
            case couleur: 
                ajoutFourmi (myWorld, fourmi,indice);
                break; 
            default: 
                combatCase (myWorld,  fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
    */
    
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
} 

// if xF> *abscisse
void deplacementOuest(Monde *myWorld, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;

    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (yF > ordonnee) {
        indice = map(xF - 1, yF - 1, cote);
    }
    else if (yF == ordonnee) {
        indice = map(xF - 1, yF, cote);
    }
    else {
        indice = map(xF - 1, yF + 1, cote);
    }
    
    /*
    if (!estLibre(myWorld, indice)) {
        switch (myWorld -> plateau -> cases[indice].fourmi -> couleur){
            case couleur: 
                ajoutFourmi (myWorld, fourmi,indice);
                break; 
            default: 
                combatCase (myWorld,  fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
    */
    
    
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
    }
    else if (xF == abscisse) {
        indice = map(xF, yF + 1, cote);
    }
    else {
        indice = map(xF + 1, yF + 1, cote);
    }
    
    /*
    if (!estLibre(myWorld, indice)) {
        switch (myWorld -> plateau -> cases[indice].fourmi -> couleur){
            case couleur: 
                ajoutFourmi (myWorld, fourmi,indice);
                break; 
            default: 
                combatCase (myWorld,  fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
    */
    
    
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
    }
    else if (xF == abscisse) {
        indice = map(xF, yF - 1, cote);
    }
    else {
        indice = map(xF + 1, yF - 1, cote);
    }
    
    /*
    if (!estLibre(myWorld, indice)) {
        switch (myWorld -> plateau -> cases[indice].fourmi -> couleur){
            case couleur: 
                ajoutFourmi (myWorld, fourmi,indice);
                break; 
            default: 
                combatCase (myWorld,  fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
    */
    
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


void ajoutFourmi (Monde* myWorld, Fourmi * fourmi, int indice){
    
    Fourmi* temp; 
    
    temp= myWorld -> plateau -> cases[indice].fourmi; 
    while (temp -> voisinSuiv != NULL){
        temp = temp -> voisinSuiv; 
    }
     
    temp -> voisinSuiv = fourmi; 
    fourmi -> voisinPrec = temp; 
    fourmi -> voisinSuiv = NULL; 
    fourmi -> position = indice; 
}

void combatCase (Monde * myWorld, Fourmi * fourmi, int indice){
    
    Fourmi * temp; 
    temp = myWorld -> plateau -> cases[indice].fourmi; 
    
    
    while (temp -> voisinSuiv != NULL && fourmi !=NULL){
        temp = temp -> voisinSuiv; 
        combatFourmi(fourmi, temp, myWorld);
    }
    
    if (fourmi != NULL){
        myWorld -> plateau -> cases[indice].fourmi = fourmi; 
        fourmi -> position = indice; 
    } else {
        printf("vous avez perdu le combat, pas de chance");
    }
    
}