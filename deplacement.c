#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "plateau.h"
#include "deplacement.h"
#include "combat.h"
#include "instructions.h"
#include "affichage.h"

void demandeDestination(int *abscisse, int *ordonnee, Monde *monde, Fourmi *fourmi) {
    int tmp0, tmp1;
    do {
        printf("Donnez une destination : abscisse ? \n");
        lireEntier(&tmp0);
        *abscisse = tmp0;
        printf("ordonnee ? \n");
        lireEntier(&tmp1);
        *ordonnee = tmp1;

    } while (map(tmp0, tmp1, monde->plateau->cote) < 0);
    fourmi->destination = map(tmp0, tmp1, monde->plateau->cote);
}

// si xF < *abscisse
void deplacementEst(Monde *myWorld, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;

    int caseInitiale = fourmi->position;
    modifVoisin(myWorld, fourmi, caseInitiale);

    if (yF > ordonnee) {
        indice = map(xF + 1, yF - 1, cote);
    } else if (yF == ordonnee) {
        indice = map(xF + 1, yF, cote);
    } else {
        indice = map(xF + 1, yF + 1, cote);
    }

    if (!estLibre(myWorld, indice)) {
        if (myWorld->plateau->cases[indice].fourmi->couleur == couleur) {
            ajoutFourmi(myWorld, fourmi, indice);
            affichePlateauSDL(myWorld);
        } else {
            combatCase(myWorld, fourmi, indice);
        }
    } else {
        printf("case libre\n");
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
}

// if xF> *abscisse
void deplacementOuest(Monde *myWorld, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;

    int caseInitiale = fourmi->position;
    modifVoisin(myWorld, fourmi, caseInitiale);

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
        if (myWorld->plateau->cases[indice].fourmi->couleur == couleur) {
            ajoutFourmi(myWorld, fourmi, indice);
        } else {
            combatCase(myWorld, fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
}

//if yF < *ordonnee
void deplacementSud(Monde *myWorld, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;

    int caseInitiale = fourmi->position;
    modifVoisin(myWorld, fourmi, caseInitiale);

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
            combatCase(myWorld, fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
}

// if yF > *ordonnee
void deplacementNord(Monde *myWorld, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;

    int caseInitiale = fourmi->position;
    modifVoisin(myWorld, fourmi, caseInitiale);

    if (xF > abscisse) {
        indice = map(xF - 1, yF - 1, cote);
    } else if (xF == abscisse) {
        indice = map(xF, yF - 1, cote);
    } else {
        indice = map(xF + 1, yF - 1, cote);
    }


    if (!estLibre(myWorld, indice)) {
        if (myWorld->plateau->cases[indice].fourmi->couleur == couleur) {
            ajoutFourmi(myWorld, fourmi, indice);
        } else {
            combatCase(myWorld, fourmi, indice);
        }
    } else {
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
}


void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int abscisse, int ordonnee) {


    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    fourmi->destination = map(abscisse, ordonnee, myWorld->plateau->cote);

    if (xF < abscisse) {
        deplacementEst(myWorld, fourmi, ordonnee);
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
}


void ajoutFourmi(Monde *myWorld, Fourmi *fourmi, int indice) {

    Fourmi *temp;

    temp = myWorld->plateau->cases[indice].fourmi;
    while (temp->voisinSuiv != NULL) {
        temp = temp->voisinSuiv;
    }

    temp->voisinSuiv = fourmi;
    fourmi->voisinPrec = temp;
    fourmi->voisinSuiv = NULL;
    fourmi->position = indice;
}

void combatCase(Monde *myWorld, Fourmi *fourmi, int indice) {

    Fourmi *temp;
    temp = myWorld->plateau->cases[indice].fourmi;
    int combat = 1;

    while ((temp != NULL) && (combat == 1)) {
        printf("combat voisin\n");
        printf("type de la fourmi:%d\n", temp->type);
        combat = combatFourmi(myWorld, fourmi, temp);
        printf("combat=%d\n", combat);
        temp = temp->voisinSuiv;
    }
    if (combat == 1) {
        printf("remporte le combat\n");
        myWorld->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    } else {
        printf("vous avez perdu le combat, pas de chance\n");
    }
}

void modifVoisin(Monde *myWorld, Fourmi *fourmi, int caseInitiale) {

    Fourmi *temp;
    temp = fourmi;

    //savoir si la fourmi que je veux deplacer est celle sur laquelle pointe la case ou non ..

    //cas voisinPrec et voisinSuiv
    if (temp->voisinSuiv != NULL && temp->voisinPrec != NULL) {
        temp->voisinSuiv->voisinPrec = temp->voisinPrec;
        temp->voisinPrec->voisinSuiv = temp->voisinSuiv;

        //modification pointeur tableau cases
        if (myWorld->plateau->cases[caseInitiale].fourmi == temp) {
            myWorld->plateau->cases[caseInitiale].fourmi = temp->voisinSuiv;
        }

    } else if (temp->voisinSuiv != NULL && temp->voisinPrec == NULL) {
        temp->voisinSuiv->voisinPrec = NULL;

        if (myWorld->plateau->cases[caseInitiale].fourmi == temp) {
            myWorld->plateau->cases[caseInitiale].fourmi = temp->voisinSuiv;
        }

    } else if (temp->voisinSuiv == NULL && temp->voisinPrec != NULL) {
        temp->voisinPrec->voisinSuiv = NULL;

        if (myWorld->plateau->cases[caseInitiale].fourmi == temp) {
            myWorld->plateau->cases[caseInitiale].fourmi = temp->voisinPrec;
        }

    } else {
        myWorld->plateau->cases[caseInitiale].fourmi = NULL;
    }

}