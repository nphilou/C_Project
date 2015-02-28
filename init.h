#ifndef DEF_INIT
#define DEF_INIT

    Fourmi *initialisation(Couleur couleur, Plateau *plateau);
    void creationFourmi(Couleur couleur, TypeFourmi typefourmi, Fourmi *origine, Monde *myWorld, int indice);
    //void creationFourmiliere(Couleur couleur, Monde * myWorld , int indice);
    void transformeFourmi(Fourmi *fourmi, Monde *myWorld);
    void suicideFourmi(Fourmi *fourmi, Monde *myWorld);
    void supprimeAgent(Fourmi *fourmi, Monde *myWorld);
    void priseFourmiliere(Fourmi *fourmi, Monde *myWorld, Fourmi *ennemie);
    void supprimeFourmiliereFin(Fourmi *fourmi, Monde *myWorld);
    void supprimeFourmiliere(Fourmi *fourmi, Monde *myWorld);
    void changeCouleur(Monde *myWorld, Fourmi *fourmi, Fourmi *ennemie);
    int chercheFourmiliere(Fourmi *fourmi, Monde *myWorld);
    Monde *creationMonde();

#endif