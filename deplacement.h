#include "combat.h"

void demandeDestination(int *abscisse, int *ordonnee, Monde *monde, Fourmi *fourmi);

void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int abscisse, int ordonnee);


void deplacementNord(Monde *myWorld, Fourmi *fourmi, int abscisse);

void deplacementSud(Monde *myWorld, Fourmi *fourmi, int abscisse);

void deplacementOuest(Monde *myWorld, Fourmi *fourmi, int ordonnee);

void deplacementEst(Monde *myWorld, Fourmi *fourmi, int ordonnee);