#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

int map(int abscisse, int ordonnee, int cote) {
    if (abscisse < 0 || abscisse >= cote || ordonnee < 0 || ordonnee >= cote){
        return -1;
    }
    return cote * ordonnee + abscisse;
}

int chercheOrdonnee(Monde *myWorld, int indice) {
    return indice / myWorld->plateau->cote;
}

int chercheAbscisse(Monde *myWorld, int indice) {
    return indice % myWorld->plateau->cote;
}

int estLibre(Monde *myWorld, int indice) {
    int nombrecases = myWorld->plateau->nombrecases;

    if (indice < 0 || indice > nombrecases - 1) return -1;

    if (myWorld->plateau->cases[indice].fourmi != NULL) {
        return 0;
    }
    return 1;
}

void affichePlateau(Plateau *plateau) {
    int largeur, hauteur;

    for (largeur = 0; largeur < plateau->cote; largeur++) {
        printf(" %d ", largeur);
        printf("   ");
    }
    printf("\n");
    for (hauteur = 0; hauteur < plateau->cote; hauteur++) {
        for (largeur = 0; largeur < plateau->cote; largeur++) {

            if (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi == NULL) {
                printf("   ");
            } else {
                switch (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi->type) {
                    case FOURMILIERE:
                        printf(" F ");
                        break;
                    case SOLDAT:
                        printf(" S ");
                        break;
                    case OUVRIERE:
                        printf(" O ");
                        break;
                    case REINE:
                        printf(" R ");
                        break;
                    default:
                        printf("   ");
                }
            }
            printf(" | ");
        }
        printf(" %d\n\n", hauteur);
    }
}

int chercheLibre(int centre, Monde *myWorld) {

    int cote = myWorld->plateau->cote; //raccourci
    int rayon;
    int haut, droite, bas, gauche, ligne;
    int ordonnee = chercheOrdonnee(myWorld, centre);
    int abscisse = chercheAbscisse(myWorld, centre);

    //if plateau rempli

    //on s'eloigne du centre (rayon augmente)
    for (rayon = 1; rayon < cote; rayon++) {

        //haut
        for (haut = centre - rayon * cote + rayon; haut >= centre - rayon * cote - rayon; haut--) {
            ligne = ordonnee - rayon;
            if (haut < ligne * cote || haut >= (ligne + 1) * cote || !ordonnee) continue;
            if (estLibre(myWorld, haut)) {
                return haut;
            }
        }

        //gauche
        for (gauche = centre - (rayon - 1) * cote - rayon; gauche <= centre + (rayon - 1) * cote - rayon; gauche += cote) {
            if (!abscisse) continue;
            if (estLibre(myWorld, gauche)) {
                return gauche;
            }
        }

        //bas
        for (bas = centre + rayon * cote - rayon; bas <= centre + rayon * cote + rayon; bas++) {
            ligne = ordonnee + rayon;
            if (bas < ligne * cote || bas >= (ligne + 1) * cote || ordonnee == cote) continue;
            if (estLibre(myWorld, bas)) {
                return bas;
            }
        }

        //droite
        for (droite = centre + rayon * cote + rayon; droite >= centre - (rayon - 1) * cote + rayon; droite -= cote) {
            if (abscisse == cote - 1) continue;
            if (estLibre(myWorld, droite)) {
                return droite;
            }
        }
    }
    return -1;
}