#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


typedef struct{
    int x;
    int y;
 } Coordonnee;

typedef struct {
    Fourmiliere* rouge;
    Fourmiliere* noire;
    Plateau* plateau;
}Monde;

typedef struct {
    int couleur;
    Coordonnee * position;
    int tmpProduc:
    char type[10];
    Fourmiliere* debut;
    Fourmiliere* suiv;
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


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO); // Démarrage de la SDL (ici : chargement du système vidéo)

    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
