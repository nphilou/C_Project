#ifndef DEF_JEU
#define DEF_JEU

void sauvegarde(Monde *monde);

Monde *chargement();

void jeu();

void afficherGagnant(Monde *monde);

Monde *chargementMonde(int compt, int tresor[], int type[], int origine[], int couleur[], int position[], int instruction[]);

void videMemoire(Monde *monde);

#endif