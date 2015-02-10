#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

//DECLARATION STRUCTURES
typedef struct {
} Coordonees;

typedef struct {
} Reine;
typedef struct {
} Soldat;
typedef struct {
} Ouvriere;

typedef struct {
} Fourmi;
typedef struct {
} Monde;
typedef struct {
} Fourmiliere;
typedef struct {
} Plateau;

//DECLARATION FONCTIONS (A FAIRE)

//DEFINITION STRUCTURES
typedef struct {
    int x;
    int y;
} Coordonnees;

typedef struct {
    int tempsProd;
} Reine;

typedef struct {
    int tempsProd;
} Soldat;

typedef struct {
    int tempsProd;
} Ouvriere;

typedef enum {
    REINE;
    SOLDAT;
    OUVRIERE;
} TypeFourmi;

typedef struct {
    char couleur;
    TypeFourmi type;
    Coordonnees destination;
    Coordonnees position;
    Fourmiliere *origine;
    Fourmi *suiv;
} Fourmi;

typedef struct {
    Fourmiliere *rouge;
    Fourmiliere *noire;
    Plateau *plateau;
} Monde;

typedef struct fourmiliere {
    int couleur;
    Coordonnees *position;
    int tmpProduc;
    char type[10];
    struct fourmiliere *origine;
    struct fourmiliere *suiv;
} Fourmiliere;

typedef struct {


} Plateau;

void pause() {
    int continuer = 1;
    SDL_Event event;

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    SDL_WM_SetCaption("Hohoho", NULL);

    pause(); // Mise en pause du programme

    SDL_Quit(); // Arrêt de la SDL

    return EXIT_SUCCESS; // Fermeture du programme
}