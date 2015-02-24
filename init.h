#include "plateau.h"

Fourmi *initialisation(Couleur couleur, Plateau *plateau);

Fourmi *initialReine(Couleur couleur, Plateau *plateau, Fourmi *fourmiOrigine);

Fourmi *initialOuvriere(Couleur couleur, Plateau *plateau, Fourmi *reine);

void creationFourmi(Couleur couleur, TypeFourmi typefourmi,Fourmi *origine, Monde *myWorld, int indice);


void suicideeFourmi(Fourmi *fourmi, Monde *myWorld);
void supprimeAgent(Fourmi *fourmi, Monde *myWorld);
void priseFourmiliere (Fourmi *fourmi, Monde *myWorld, Fourmi * ennemie);
void supprimeFourmiliere (Fourmi* fourmi, Monde * myWorld);
void changeCouleur(Fourmi* fourmi, Couleur couleur, Monde *myWorld, Fourmi *ennemie);

Monde *creationMonde();