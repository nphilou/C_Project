#include "structures.h"

//Place les 2 fourmilieres de depart
Fourmi *initialisation(Couleur couleur, Plateau *plateau);

Fourmi *initialReine(Couleur couleur, Plateau *plateau, Fourmi *fourmiOrigine);

Fourmi *initialOuvriere(Couleur couleur, Plateau *plateau, Fourmi *reine);

void creationFourmi(Couleur couleur, TypeFourmi typefourmi, Monde *myWorld, int indice);

void supprimeFourmi(Fourmi *fourmi, Monde *myWorld);

void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int x, int y);

int estLibre(Monde *myWorld, int indice);

void CombatFourmi(Fourmi *fourmiAttaquante, Fourmi *fourmi2, Monde *myworld);

Monde *creationMonde();

int chercheLibre(int centre, Monde *myWorld);

void affichePlateau(Plateau *plateau);
