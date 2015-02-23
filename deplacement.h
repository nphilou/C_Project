#include "combat.h"

void demandeDestination(int *abscisse, int *ordonnee, Monde* monde);

int deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int * abscisse, int * ordonnee);


void deplacementNord (Monde * myWorld, Fourmi * fourmi, int * abscisse, int * ordonnee);
void deplacementSud (Monde * myWorld, Fourmi* fourmi, int * abscisse, int * ordonnee);
void deplacementOuest (Monde * myWorld, Fourmi*fourmi, int * abscisse, int * ordonnee);
void deplacementEst (Monde * myWorld, Fourmi* fourmi, int *abscisse, int * ordonnee);