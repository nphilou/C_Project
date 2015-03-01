#ifndef DEF_JEU
#define DEF_JEU

void sauvegarde (Monde* myWorld, int joueur);
void chargement ();
void jeu (Monde * myWorld);
Monde * chargementMonde(char ** temp, int compt );
int * recupereEntier (FILE*file, int compt);
#endif