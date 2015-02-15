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
	
	
	if (couleur == ROUGE){
		plateau->cases[1].x = 9;
		printf("yata");
		//plateau->cases[1]->fourmi = fourmi;
		printf("9 = %d", plateau->cases[1].x);
	} 
	printf("colorrrr= %d", fourmi->couleur);
	//if (couleur == NOIR) plateau->cases[plateau->taille-1]->fourmi = fourmi;

	fourmi->suivant = NULL;
	fourmi->precedant = NULL;
	
	return fourmi;
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

	Plateau *plateau = calloc(pow(cotePlateau,2), sizeof(Case));
	plateau->taille = pow(cotePlateau,2);
	printf("plateau->taille = %d \n", plateau->taille);
	myWorld->plateau = plateau;
	
	//Creation fourmilieres rouge et noire
	//myWorld->noire = initialisation(NOIR, plateau);
	myWorld->rouge = initialisation(ROUGE, plateau);
	
	
	return myWorld;
}

/*int main(int argc, char *argv[]) {
	printf("bon !");
    Monde *myWorld = creationMonde();
    
    return 0;
}*/