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
    Couleur couleur = fourmi -> couleur;

    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (yF > ordonnee) {
        indice = map(xF + 1, yF - 1, cote);
    } else if (yF == ordonnee) {
        indice = map(xF + 1, yF, cote);
    } else {
        indice = map(xF + 1, yF + 1, cote);
    }


    if (!estLibre(myWorld, indice)) {
        if(myWorld -> plateau -> cases[indice].fourmi -> couleur == couleur){
            ajoutFourmi (myWorld, fourmi,indice);
            affichePlateau(myWorld->plateau);
            printf("position fourmi precedente:%d\n", fourmi -> voisinPrec -> position );
        } else {
            printf("position*** fourmi:%d\n",indice);
            combatCase (myWorld,  fourmi, indice);
        }
    } else {
        printf("case libre\n");
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }


    /*
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
    */
}

// if xF> *abscisse
void deplacementOuest(Monde *myWorld, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi -> couleur;

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


    if (!estLibre(myWorld, indice)) {
        if(myWorld -> plateau -> cases[indice].fourmi -> couleur == couleur){
            ajoutFourmi (myWorld, fourmi,indice);
        } else {
            combatCase (myWorld,  fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
/*
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
    */
}

//if yF < *ordonnee
void deplacementSud(Monde *myWorld, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;

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


    if (!estLibre(myWorld, indice)) {
        if (myWorld->plateau->cases[indice].fourmi->couleur == couleur) {
            ajoutFourmi(myWorld, fourmi, indice);
        } else {
            printf("position*** fourmi:%d\n", indice);
            combatCase(myWorld, fourmi, indice);
            printf("bou");
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
/*
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
    */
}

// if yF > *ordonnee
void deplacementNord(Monde *myWorld, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi -> couleur;

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


    if (!estLibre(myWorld, indice)) {
        if(myWorld -> plateau -> cases[indice].fourmi -> couleur == couleur){
            ajoutFourmi (myWorld, fourmi,indice);
        } else {
            combatCase (myWorld,  fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }

/*
    myWorld->plateau->cases[indice].fourmi = fourmi;
    fourmi->position = indice;
    */
}



void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int abscisse, int ordonnee) {


    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int caseInitial = map(xF, yF, myWorld->plateau->cote);
    fourmi->destination = map(abscisse, ordonnee, myWorld->plateau->cote);

    myWorld->plateau->cases[caseInitial].fourmi = NULL;

    if (xF < abscisse) {
        printf("ici *\n");
        deplacementEst(myWorld, fourmi,  ordonnee);

    }
    else if (xF > abscisse) {
        deplacementOuest(myWorld, fourmi, ordonnee);
        printf("ici**\n");
    }
    else if (yF < ordonnee) {
        deplacementSud(myWorld, fourmi, abscisse);
        printf("ici***\n");
    }
    else if (yF > ordonnee) {
        deplacementNord(myWorld, fourmi, abscisse);
        printf("ici****\n");
    }
/*
    xF = chercheAbscisse(myWorld, fourmi->position);
    yF = chercheOrdonnee(myWorld, fourmi->position);
    printf("*l'abscisse de la fourmi: %d, l'ordonnee: %d\n", xF, yF);
*/
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

    printf("combat case2\n");

    Fourmi * temp;
    temp = myWorld -> plateau -> cases[indice].fourmi;
    int combat = 1;
    printf("combat=%d\n", combat);

    while ((temp -> voisinSuiv != NULL) && (combat ==1)){
        printf("combat voisin\n");
        temp = temp -> voisinSuiv;
        combat = combatFourmi(fourmi, temp-> voisinSuiv, myWorld);
    }

    combat = combatFourmi(fourmi, temp , myWorld);
    if (combat == 1){
        printf("remporte le combat\n");
        myWorld -> plateau -> cases[indice].fourmi = fourmi;
        fourmi -> position = indice;
    } else {
        printf("vous avez perdu le combat, pas de chance\n");
    }
}