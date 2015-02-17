#include "structures.h"

//Place les 2 fourmilieres de depart
Fourmi *initialisation(Couleur couleur, Plateau* plateau);
Fourmi * initialReine (Couleur couleur, Plateau* plateau, Fourmi* fourmiOrigine);
Fourmi * initialOuvriere (Couleur couleur, Plateau * plateau, Fourmi * reine);

void  creationFourmi (Couleur couleur, TypeFourmi typefourmi, Monde* myWorld, int abscisse, int ordonnee);
void supprimeFourmi (Fourmi * fourmi, Monde * myWorld); 

void DeplacementFourmi (Monde * myWorld, Fourmi * fourmi, int abscisse, int ordonnee); 
int estLibre(Monde* myWorld, int abscisse, int ordonnee); 

void CombatFourmi ( Fourmi * fourmiAttaquante , Fourmi * fourmi2,  Monde * myworld); 

int map(int ordonnee, int abscisse, int cote);

Monde* creationMonde();

void affichePlateau(Plateau* plateau);
