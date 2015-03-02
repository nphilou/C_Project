#ifndef DEF_JEU
#define DEF_JEU

void sauvegarde (Monde* myWorld, int joueur);
Monde* chargement ();
void jeu ();
void afficherGagnant (Monde*myWorld);
Monde * chargementMonde(int tresor[], int type[], int origine[], int couleur[], int position[] , int instruction[] );
void videMemoire (Monde* myWorld);
//int * recupereEntier (FILE*file, int compt);

#endif