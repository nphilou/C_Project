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
    int resCombat;

    int caseInitiale = fourmi->position;
    // modifVoisin(myWorld, fourmi, caseInitiale);

    if (yF > ordonnee) {
        indice = map(xF + 1, yF - 1, cote);
    } else if (yF == ordonnee) {
        indice = map(xF + 1, yF, cote);
    } else {
        indice = map(xF + 1, yF + 1, cote);
    }

    if (!estLibre(myWorld, indice)) {
        if (myWorld->plateau->cases[indice].fourmi->couleur == couleur) {
            modifVoisin(myWorld, fourmi, caseInitiale);
            affichePlateauSDL(myWorld);
            ajoutFourmi(myWorld, fourmi, indice);
            affichePlateauSDL(myWorld);
        } else {
            resCombat = combatCase(myWorld, fourmi, indice);
            if (resCombat == 1) {
                affichePlateauSDL(myWorld);
                modifVoisin(myWorld, fourmi, caseInitiale);
                affichePlateauSDL(myWorld);
            }
        }
    } else {
        modifVoisin(myWorld, fourmi, caseInitiale);
        affichePlateauSDL(myWorld);
        myWorld->plateau->cases[indice].fourmi = fourmi;
        affichePlateauSDL(myWorld);
        fourmi->position = indice;
    }
}

// if xF> *abscisse
void deplacementOuest(Monde *myWorld, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;
    int resCombat;

    int caseInitiale = fourmi->position;
    //modifVoisin(myWorld, fourmi, caseInitiale);

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
            modifVoisin(myWorld, fourmi, caseInitiale);
            affichePlateauSDL(myWorld);
            ajoutFourmi(myWorld, fourmi, indice);
            affichePlateauSDL(myWorld);
        } else {
            resCombat = combatCase(myWorld, fourmi, indice);
            affichePlateauSDL(myWorld);
            if (resCombat == 1) {
                modifVoisin(myWorld, fourmi, caseInitiale);
                affichePlateauSDL(myWorld);
            }
        }
    } else {
        modifVoisin(myWorld, fourmi, caseInitiale);
        affichePlateauSDL(myWorld);
        myWorld->plateau->cases[indice].fourmi = fourmi;
        affichePlateauSDL(myWorld);
        fourmi->position = indice;
    }
}

//if yF < *ordonnee
void deplacementSud(Monde *myWorld, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;
    int resCombat;

    int caseInitiale = fourmi->position;
    //modifVoisin(myWorld, fourmi, caseInitiale);

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
            modifVoisin(myWorld, fourmi, caseInitiale);
            affichePlateauSDL(myWorld);
            ajoutFourmi(myWorld, fourmi, indice);
            affichePlateauSDL(myWorld);
        } else {
            resCombat = combatCase(myWorld, fourmi, indice);
            if (resCombat == 1) {
                modifVoisin(myWorld, fourmi, caseInitiale);
            }
        }
    } else {
        modifVoisin(myWorld, fourmi, caseInitiale);
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
    int resCombat;

    int caseInitiale = fourmi->position;

    if (xF > abscisse) {
        indice = map(xF - 1, yF - 1, cote);
    } else if (xF == abscisse) {
        indice = map(xF, yF - 1, cote);
    } else {
        indice = map(xF + 1, yF - 1, cote);
    }


    if (!estLibre(myWorld, indice)) {
        if (myWorld->plateau->cases[indice].fourmi->couleur == couleur) {
            modifVoisin(myWorld, fourmi, caseInitiale);
            affichePlateauSDL(myWorld);
            ajoutFourmi(myWorld, fourmi, indice);
            affichePlateauSDL(myWorld);
        } else {
            resCombat = combatCase(myWorld, fourmi, indice);
            if (resCombat == 1) {
                modifVoisin(myWorld, fourmi, caseInitiale);
                affichePlateauSDL(myWorld);
            }
        }
    } else {
        modifVoisin(myWorld, fourmi, caseInitiale);
        affichePlateauSDL(myWorld);
        myWorld->plateau->cases[indice].fourmi = fourmi;
        affichePlateauSDL(myWorld);
        fourmi->position = indice;
    }
}


void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int abscisse, int ordonnee) {


    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    fourmi->destination = map(abscisse, ordonnee, myWorld->plateau->cote);

    if (xF < abscisse) {
        deplacementEst(myWorld, fourmi, ordonnee);
        affichePlateauSDL(myWorld);
    }
    else if (xF > abscisse) {
        deplacementOuest(myWorld, fourmi, ordonnee);
        affichePlateauSDL(myWorld);
    }
    else if (yF < ordonnee) {
        deplacementSud(myWorld, fourmi, abscisse);
        affichePlateauSDL(myWorld);
    }
    else if (yF > ordonnee) {
        deplacementNord(myWorld, fourmi, abscisse);
        affichePlateauSDL(myWorld);
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

int combatCase(Monde *myWorld, Fourmi *fourmi, int indice) {

    Fourmi *temp;
    temp = myWorld->plateau->cases[indice].fourmi;
    int combat = 1;

    if (temp-> type == FOURMILIERE){
        while ((temp -> voisinSuiv != NULL) && (combat == 1)) {
            printf("combat voisin\n");
            combat = combatFourmi(myWorld, fourmi, temp-> voisinSuiv);
        }
        if (combat)combat = combatFourmi(myWorld, fourmi, temp);
        if (combat == 1) {
            printf("remporte le combat\n");
            myWorld->plateau->cases[indice].fourmi = fourmi;
            fourmi->position = indice;
        } else {
            printf("*** vous avez perdu le combat ***\n");
        }

    }else {

        while ((temp != NULL) && (combat == 1)) {
            printf("combat voisin\n");
            combat = combatFourmi(myWorld, fourmi, temp);
            temp = temp->voisinSuiv;
        }
        if (combat == 1) {
            printf("remporte le combat\n");
            myWorld->plateau->cases[indice].fourmi = fourmi;
            fourmi->position = indice;
        } else {
            printf("*** vous avez perdu le combat ***\n");
        }
    }
    return combat;
}

void modifVoisin(Monde *myWorld, Fourmi *fourmi, int caseInitiale) {

    Fourmi *temp;
    temp = fourmi;

    //cas voisinPrec et voisinSuiv
    if (temp->voisinSuiv != NULL && temp->voisinPrec != NULL) {
        temp->voisinSuiv->voisinPrec = temp->voisinPrec;
        temp->voisinPrec->voisinSuiv = temp->voisinSuiv;

    } else if (temp->voisinSuiv != NULL && temp->voisinPrec == NULL) {
        temp->voisinSuiv->voisinPrec = NULL;
        myWorld->plateau->cases[caseInitiale].fourmi = temp->voisinSuiv;

    } else if (temp->voisinSuiv == NULL && temp->voisinPrec != NULL) {
        temp->voisinPrec->voisinSuiv = NULL;

    } else {
        myWorld->plateau->cases[caseInitiale].fourmi = NULL;
    }

    fourmi->voisinPrec = NULL;
    fourmi->voisinSuiv = NULL;

}