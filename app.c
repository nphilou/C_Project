#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "app.h"

Fourmi *initialisation(Couleur couleur, Plateau* plateau) {
	Fourmi *fourmi = calloc(1, sizeof(Fourmi));
	
	//Test allocation memoire
	if (fourmi == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fourmi->couleur = couleur;
	fourmi->type = FOURMILIERE;

	if (couleur == ROUGE)plateau->cases[0].fourmi = fourmi;
	if (couleur == NOIR) plateau->cases[plateau->nombrecases-1].fourmi = fourmi;

	fourmi->suivant = NULL;
	fourmi->precedant = NULL;
	
	return fourmi;
}

int map(int ordonnee, int abscisse, int cote) {
    return cote * ordonnee + abscisse;
}

Monde* creationMonde(){
	//Creation Monde
	Monde* myWorld = calloc(1, sizeof(Monde));
	
	//Creation plateau
	int cotePlateau;
	printf("Taille du plateau ? ");
	scanf("%d", &cotePlateau);

    //Test valeur saisie >1
    if(cotePlateau<=1){
        printf("Bah bravo MORRAY !\n");
        exit(1);
    }

	Plateau *plateau = calloc(pow(cotePlateau,2), sizeof(Case));
	plateau->nombrecases = pow(cotePlateau,2);
    plateau->cote = cotePlateau;
    printf("plateau->nombrecases = %d \n", plateau->nombrecases);

    
    myWorld->plateau = plateau;

	//Creation fourmilieres rouge et noire
	myWorld->noire = initialisation(NOIR, plateau);
	myWorld->rouge = initialisation(ROUGE, plateau);
	
	
	return myWorld;
}

void affichePlateau(Plateau* plateau){
    int largeur, hauteur;
    for(hauteur = 0; hauteur < plateau->cote; hauteur++) {
        for (largeur = 0; largeur < plateau->cote; largeur++) {
            //printf("mappage : %d", map(hauteur, largeur, plateau->cote));
            if (plateau->cases[map(hauteur, largeur, plateau->cote)].fourmi == NULL) {
                printf("   ");
            } else {
                switch (plateau->cases[map(hauteur, largeur, plateau->cote)].fourmi->type) {
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
        printf("\n\n");
    }
}