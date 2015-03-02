#ifndef DEF_PLATEAU
#define DEF_PLATEAU

int map(int abscisse, int ordonnee, int cote);

int chercheOrdonnee(Monde *monde, int indice);

int chercheAbscisse(Monde *monde, int indice);

int estLibre(Monde *monde, int indice);

void affichePlateau(Plateau *plateau);

int chercheLibre(Monde *monde, int centre);

#endif