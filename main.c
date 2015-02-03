#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int x;
    int y;
 } Coordonnee;

typedef struct {
    Fourmiliere * rouge;
    Fourmiliere * noire;
    plateau * plateau;
}Monde;

typedef struct {
    int couleur;
    Coordonnee * position;
    int tmpProduc:
    char type[10];
    Fourmiliere * debut;
    Fourmiliere * suiv;
} Fourmiliere;



typedef struct {


}Plateau;


typedef struct {
    char couleur;
    char type [3];
    Coordonnee destination;
    Coordonnee position;
    int temps;
    Fourmiliere * origine;
    Fourmi * suiv;
} Fourmi;





int main()
{

    return 0;
}



