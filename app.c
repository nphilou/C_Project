#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "app.h"
#include "structures.h"

typedef struct Element Element;

struct Element {
	Fourmi fourmi;
	Element * element_precedant;
	Element * element_suivant;
};

Element *initialisation(Couleur couleur, Case* Plateau) {
	Element *element = calloc(1, sizeof(Element));
	Fourmi *fourmi = calloc(1, sizeof(Fourmi));

	fourmi->couleur = couleur;
	fourmi->type = FOURMILIERE;
	fourmi->position ;
	//Fourmiliere *origine = NULL;

	if (element == NULL) {
		exit(EXIT_FAILURE);
	}
	
	element->fourmi = *fourmi;
	element->element_precedant = NULL;
	element->element_suivant = NULL;
	
	return element;
}

int map(int numLigne, int numColonne, int taille) {
    return taille * numColonne + numLigne;
}

void creationMonde(){
	int cotePlateau;
	printf("Taille du plateau");
	scanf("%d", &cotePlateau);

	//Creation plateau

	Case *plateau = calloc(cotePlateau * cotePlateau, sizeof(Case));

	initialisation(NOIR, plateau);
	initialisation(ROUGE, plateau);

}