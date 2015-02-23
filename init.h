#include "plateau.h"

Fourmi *initialisation(Couleur couleur, Plateau *plateau);

Fourmi *initialReine(Couleur couleur, Plateau *plateau, Fourmi *fourmiOrigine);

Fourmi *initialOuvriere(Couleur couleur, Plateau *plateau, Fourmi *reine);

void creationFourmi(Couleur couleur, TypeFourmi typefourmi, Monde *myWorld, int indice);

void supprimeFourmi(Fourmi *fourmi, Monde *myWorld, Fourmi *fourmiAttaquante);

Monde *creationMonde();