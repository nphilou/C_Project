#ifndef DEF_INIT
#define DEF_INIT

Fourmi *initialisation(Couleur couleur, Plateau *plateau);

void creationFourmi(Monde *monde, Fourmi *origine, Couleur couleur, TypeFourmi typefourmi, int indice, int instruction);

void creationFourmiliere(Monde *monde, Couleur couleur, int indice, int instruction);

void transformeFourmi(Monde *monde, Fourmi *reine);

void suicideFourmi(Monde *monde, Fourmi *fourmi);

void supprimeAgent(Monde *monde, Fourmi *fourmi);

void priseFourmiliere(Monde *monde, Fourmi *fourmiliere, Fourmi *ennemie);

void supprimeFourmiliereFin(Monde *monde, Fourmi *fourmiliere);

void supprimeFourmiliere(Monde *monde, Fourmi *fourmiliere);

void changeCouleur(Monde *monde, Fourmi *fourmi, Fourmi *ennemie);

int chercheFourmiliere(Fourmi *fourmi);

Monde *creationMonde();

#endif