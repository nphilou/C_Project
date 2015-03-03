#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "plateau.h"
#include "deplacement.h"
#include "combat.h"
#include "instructions.h"
#include "affichage.h"

void demandeDestination(Monde *monde, Fourmi *fourmi, int *abscisse, int *ordonnee) {
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
void deplacementEst(Monde *monde, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(monde, fourmi->position);
    int yF = chercheOrdonnee(monde, fourmi->position);
    int cote = monde->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;
    int resCombat;

    int caseInitiale = fourmi->position;

    if (yF > ordonnee) {
        indice = map(xF + 1, yF - 1, cote);
    } else if (yF == ordonnee) {
        indice = map(xF + 1, yF, cote);
    } else {
        indice = map(xF + 1, yF + 1, cote);
    }

    if (!estLibre(monde, indice)) {
        if (monde->plateau->cases[indice].fourmi->couleur == couleur) {
            modifVoisin(monde, fourmi, caseInitiale);
            affichePlateauSDL(monde);
            ajoutFourmi(monde, fourmi, indice);
            affichePlateauSDL(monde);
        } else {
            resCombat = combatCase(monde, fourmi, indice);
            if (resCombat == 1) {
                affichePlateauSDL(monde);
                modifVoisin(monde, fourmi, caseInitiale);
                affichePlateauSDL(monde);
            }
        }
    } else {
        modifVoisin(monde, fourmi, caseInitiale);
        affichePlateauSDL(monde);
        monde->plateau->cases[indice].fourmi = fourmi;
        affichePlateauSDL(monde);
        fourmi->position = indice;
    }
}

// if xF> *abscisse
void deplacementOuest(Monde *monde, Fourmi *fourmi, int ordonnee) {

    int xF = chercheAbscisse(monde, fourmi->position);
    int yF = chercheOrdonnee(monde, fourmi->position);
    int cote = monde->plateau->cote, indice;
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


    if (!estLibre(monde, indice)) {
        if (monde->plateau->cases[indice].fourmi->couleur == couleur) {
            modifVoisin(monde, fourmi, caseInitiale);
            affichePlateauSDL(monde);
            ajoutFourmi(monde, fourmi, indice);
            affichePlateauSDL(monde);
        } else {
            resCombat = combatCase(monde, fourmi, indice);
            affichePlateauSDL(monde);
            if (resCombat == 1) {
                modifVoisin(monde, fourmi, caseInitiale);
                affichePlateauSDL(monde);
            }
        }
    } else {
        modifVoisin(monde, fourmi, caseInitiale);
        affichePlateauSDL(monde);
        monde->plateau->cases[indice].fourmi = fourmi;
        affichePlateauSDL(monde);
        fourmi->position = indice;
    }
}

//if yF < *ordonnee
void deplacementSud(Monde *monde, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(monde, fourmi->position);
    int yF = chercheOrdonnee(monde, fourmi->position);
    int cote = monde->plateau->cote, indice;
    Couleur couleur = fourmi->couleur;
    int resCombat;

    int caseInitiale = fourmi->position;
    //modifVoisin(monde, fourmi, caseInitiale);

    if (xF > abscisse) {
        indice = map(xF - 1, yF + 1, cote);
    }
    else if (xF == abscisse) {
        indice = map(xF, yF + 1, cote);
    }
    else {
        indice = map(xF + 1, yF + 1, cote);
    }


    if (!estLibre(monde, indice)) {
        if (monde->plateau->cases[indice].fourmi->couleur == couleur) {
            modifVoisin(monde, fourmi, caseInitiale);
            affichePlateauSDL(monde);
            ajoutFourmi(monde, fourmi, indice);
            affichePlateauSDL(monde);
        } else {
            resCombat = combatCase(monde, fourmi, indice);
            if (resCombat == 1) {
                modifVoisin(monde, fourmi, caseInitiale);
            }
        }
    } else {
        modifVoisin(monde, fourmi, caseInitiale);
        monde->plateau->cases[indice].fourmi = fourmi;
        fourmi->position = indice;
    }
}

// if yF > *ordonnee
void deplacementNord(Monde *monde, Fourmi *fourmi, int abscisse) {

    int xF = chercheAbscisse(monde, fourmi->position);
    int yF = chercheOrdonnee(monde, fourmi->position);
    int cote = monde->plateau->cote, indice;
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


    if (!estLibre(monde, indice)) {
        if (monde->plateau->cases[indice].fourmi->couleur == couleur) {
            modifVoisin(monde, fourmi, caseInitiale);
            affichePlateauSDL(monde);
            ajoutFourmi(monde, fourmi, indice);
            affichePlateauSDL(monde);
        } else {
            resCombat = combatCase(monde, fourmi, indice);
            if (resCombat == 1) {
                modifVoisin(monde, fourmi, caseInitiale);
                affichePlateauSDL(monde);
            }
        }
    } else {
        modifVoisin(monde, fourmi, caseInitiale);
        affichePlateauSDL(monde);
        monde->plateau->cases[indice].fourmi = fourmi;
        affichePlateauSDL(monde);
        fourmi->position = indice;
    }
}


void deplacementFourmi(Monde *monde, Fourmi *fourmi, int abscisse, int ordonnee) {


    int xF = chercheAbscisse(monde, fourmi->position);
    int yF = chercheOrdonnee(monde, fourmi->position);
    fourmi->destination = map(abscisse, ordonnee, monde->plateau->cote);

    if (xF < abscisse) {
        deplacementEst(monde, fourmi, ordonnee);
        affichePlateauSDL(monde);
    }
    else if (xF > abscisse) {
        deplacementOuest(monde, fourmi, ordonnee);
        affichePlateauSDL(monde);
    }
    else if (yF < ordonnee) {
        deplacementSud(monde, fourmi, abscisse);
        affichePlateauSDL(monde);
    }
    else if (yF > ordonnee) {
        deplacementNord(monde, fourmi, abscisse);
        affichePlateauSDL(monde);
    }
}


void ajoutFourmi(Monde *monde, Fourmi *fourmi, int indice) {

    Fourmi *temp;

    temp = monde->plateau->cases[indice].fourmi;
    while (temp->voisinSuiv != NULL) {
        temp = temp->voisinSuiv;
    }

    temp->voisinSuiv = fourmi;
    fourmi->voisinPrec = temp;
    fourmi->voisinSuiv = NULL;
    fourmi->position = indice;
}

int combatCase(Monde *monde, Fourmi *fourmi, int indice) {

    Fourmi *temp;
    temp = monde->plateau->cases[indice].fourmi;
    int combat = 1;

    if (temp->type == FOURMILIERE) {
        while ((temp->voisinSuiv != NULL) && (combat == 1)) {
            combat = combatFourmi(monde, fourmi, temp->voisinSuiv);
        }
        if (combat==1){
            printf("combat ultime contre la fourmiliere\n");
            combat = combatFourmi(monde, fourmi, temp);
        }
        if (combat == 1) {
            monde->plateau->cases[indice].fourmi = fourmi;
            fourmi->position = indice;
        } else {
            printf("*** vous avez perdu le combat ***\n");
        }

    } else {

        while ((temp != NULL) && (combat == 1)) {
            combat = combatFourmi(monde, fourmi, temp);
            temp = temp->voisinSuiv;
        }
        if (combat == 1) {
            monde->plateau->cases[indice].fourmi = fourmi;
            fourmi->position = indice;
        } else {
            printf("*** vous avez perdu le combat ***\n");
        }
    }
    return combat;
}

void modifVoisin(Monde *monde, Fourmi *fourmi, int caseInitiale) {

    Fourmi *temp;
    temp = fourmi;

    //cas voisinPrec et voisinSuiv
    if (temp->voisinSuiv != NULL && temp->voisinPrec != NULL) {
        temp->voisinSuiv->voisinPrec = temp->voisinPrec;
        temp->voisinPrec->voisinSuiv = temp->voisinSuiv;

    } else if (temp->voisinSuiv != NULL && temp->voisinPrec == NULL) {
        temp->voisinSuiv->voisinPrec = NULL;
        monde->plateau->cases[caseInitiale].fourmi = temp->voisinSuiv;

    } else if (temp->voisinSuiv == NULL && temp->voisinPrec != NULL) {
        temp->voisinPrec->voisinSuiv = NULL;

    } else {
        monde->plateau->cases[caseInitiale].fourmi = NULL;
    }

    fourmi->voisinPrec = NULL;
    fourmi->voisinSuiv = NULL;

}