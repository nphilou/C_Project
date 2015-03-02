#ifndef DEF_DEPLACEMENT
#define DEF_DEPLACEMENT

void demandeDestination(int *abscisse, int *ordonnee, Monde *monde, Fourmi *fourmi);

void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int abscisse, int ordonnee);

void deplacementNord(Monde *myWorld, Fourmi *fourmi, int abscisse);

void deplacementSud(Monde *myWorld, Fourmi *fourmi, int abscisse);

void deplacementOuest(Monde *myWorld, Fourmi *fourmi, int ordonnee);

void deplacementEst(Monde *myWorld, Fourmi *fourmi, int ordonnee);

void ajoutFourmi(Monde *myWorld, Fourmi *fourmi, int indice);

int combatCase(Monde *myWorld, Fourmi *fourmi, int indice);

void modifVoisin(Monde *myWorld, Fourmi *fourmi, int caseInitiale);

#endif