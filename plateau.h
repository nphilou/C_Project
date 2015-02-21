#include "structures.h"

int map(int abscisse, int ordonnee, int cote);

int chercheOrdonnee(Monde *myWorld, int indice);

int chercheAbscisse(Monde *myWorld, int indice);

int estLibre(Monde *myWorld, int indice);

void affichePlateau(Plateau *plateau);

int chercheLibre(int centre, Monde *myWorld);