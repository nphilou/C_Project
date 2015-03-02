#ifndef DEF_DEPLACEMENT
#define DEF_DEPLACEMENT

void demandeDestination(Monde *monde, Fourmi *fourmi, int *abscisse, int *ordonnee);

void deplacementFourmi(Monde *monde, Fourmi *fourmi, int abscisse, int ordonnee);

void deplacementNord(Monde *monde, Fourmi *fourmi, int abscisse);

void deplacementSud(Monde *monde, Fourmi *fourmi, int abscisse);

void deplacementOuest(Monde *monde, Fourmi *fourmi, int ordonnee);

void deplacementEst(Monde *monde, Fourmi *fourmi, int ordonnee);

void ajoutFourmi(Monde *monde, Fourmi *fourmi, int indice);

int combatCase(Monde *monde, Fourmi *fourmi, int indice);

void modifVoisin(Monde *monde, Fourmi *fourmi, int caseInitiale);

#endif