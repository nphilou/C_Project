#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "app.h"
#include "structures.h"


typedef struct {
    Fourmi fourmi;
    Element * element_precedant;
    Element * element_suivant;
} Element;

Element *initialisation(Couleur couleur, Case* Plateau) {
    Element *element = malloc(sizeof(Element));
    Fourmi *fourmi = malloc(sizeof(Fourmi));

    fourmi->couleur = couleur;
    fourmi->typeFourmi = TypeFourmi.FOURMILIERE;
    fourmi->destination = NULL;
    fourmi->position ;
    Fourmiliere *origine = NULL;

    if (element == NULL) {
        exit(EXIT_FAILURE);
    }
    
    element->fourmi = fourmi;
    element->element_precedant = NULL;
    element->element_suivant = NULL;
    
    return element;
}

void creationMonde(){
    int cotePlateau;
    printf("Taille du plateau");
    scanf("%d", &cotePlateau);

    //Creation plateau
    int i;
    Case ** plateau = malloc(sizeof(Case) * cotePlateau);
    for (i = 0; i < LIGNES; i++) {
        plateau[i] = malloc(sizeof **Case * cotePlateau);
    }

    initialisation(Couleur.NOIR, plateau);
    initialisation(Couleur.ROUGE, plateau);

}