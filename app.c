#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "app.h"
#include "structures.h"


typedef struct {
    Fourmi fourmi;
    Element * element_suivant;
} Element;

void creationFourmi(){

}

void creationJoueur(){

}

void creationMonde(){
    int cotePlateau;
    printf("Taille du plateau");
    scanf("%d", &cotePlateau);
    malloc(sizeof(Case)*pow(cotePlateau, 2));

}