#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "app.h"
#include "structures.h"

Element *initialisation(Couleur couleur, Plateau* plateau) {
	//Element *element = calloc(1, sizeof(Element));
	
	//Test allocation memoire
	if (element == NULL) {
		exit(EXIT_FAILURE);
	}
	
	element->fourmi->couleur = couleur;
	element->fourmi->type = FOURMILIERE;
	if (couleur == ROUGE) element->fourmi->position = plateau->cases[1];
	if (couleur == NOIR) element->fourmi->position = plateau->cases[plateau->taille-1];

	element->element_precedant = NULL;
	element->element_suivant = NULL;
	
	return element;
}

int map(int numLigne, int numColonne, int taille) {
    return taille * numColonne + numLigne;
}

Monde* creationMonde(){
	//Creation Monde
	Monde* myWorld = calloc(1, sizeof(Monde));
	
	//Creation plateau
	int cotePlateau;
	printf("Taille du plateau");
	scanf("%d", &cotePlateau);

	Plateau *plateau = calloc(cotePlateau * cotePlateau, sizeof(Case));
	plateau->taille = cotePlateau * cotePlateau;
	printf("plateau->taille = %d \n", plateau->taille);
	myWorld->plateau = plateau;
	
	//Creation fourmilieres rouge et noire
	myWorld->noire = initialisation(NOIR, plateau)->fourmi;
	myWorld->rouge = initialisation(ROUGE, plateau)->fourmi;
	
	return myWorld;
}