#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "structures.h"
#include "affichage.h"
#include "plateau.h"

static SDL_Surface *ecran = NULL,
        *fourmiliere = NULL,
        *ouvriere = NULL,
        *reine = NULL,
        *soldat = NULL,
        *vide = NULL,
        *texteNoir = NULL,
        *texteRouge = NULL;

static TTF_Font *police = NULL;

void pause() {
    int continuer = 1;
    SDL_Event event;

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
            default:break;
        }
    }
}

void initPlateau() {
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE);
    fourmiliere = IMG_Load("miniatures/fourmiliere.png");
    ouvriere = IMG_Load("miniatures/ouvriere.png");
    reine = IMG_Load("miniatures/reine.png");
    soldat = IMG_Load("miniatures/soldat.png");
    vide = IMG_Load("miniatures/vide.png");
    texteNoir = NULL;
    texteRouge = NULL;

    police = TTF_OpenFont("fonts/minecraftia.ttf", 30);
}

void affichePlateauSDL(Monde *myWorld) {

    static int initialisation = 0;
    if (!initialisation) {
        //Declaration surfaces, unites, evenement, police
        initPlateau();
        initialisation = 1;
    }

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    SDL_Rect position;

    char tresorNoir[20] = "";
    char tresorRouge[20] = "";

    //Definition couleurs
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurRouge = {255, 0, 0};

    //Definition position *optionnel*
    position.x = 0;
    position.y = 0;

    //Effacement de l'ecran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    //Variables pour l'affichage 2D
    int largeur, hauteur, couleur;
    int cote = myWorld->plateau->cote;

    for (hauteur = 0; hauteur < cote; hauteur++) {
        for (largeur = 0; largeur < cote; largeur++) {

            position.x = largeur * TAILLE_CASE;
            position.y = hauteur * TAILLE_CASE;
            //print3
            // f("x = %d et y = %d\n", position.x, position.y);

            if (myWorld->plateau->cases[map(largeur, hauteur, cote)].fourmi == NULL) {
                SDL_BlitSurface(vide, NULL, ecran, &position);
                continue;
            }

            couleur = (int) myWorld->plateau->cases[map(largeur, hauteur, cote)].fourmi->couleur;
            switch (myWorld->plateau->cases[map(largeur, hauteur, cote)].fourmi->type) {
                case FOURMILIERE:
                    SDL_BlitSurface(fourmiliere, NULL, ecran, &position);
                    break;
                case SOLDAT:
                    SDL_BlitSurface(soldat, NULL, ecran, &position);
                    break;
                case OUVRIERE:
                    SDL_BlitSurface(ouvriere, NULL, ecran, &position);
                    break;
                case REINE:
                    SDL_BlitSurface(reine, NULL, ecran, &position);
                    break;
                default:
                    SDL_BlitSurface(vide, NULL, ecran, &position);
                    break;
            }
        }
    }

    //Chaine tresorNoir
    sprintf(tresorNoir, "Tresor : %d", myWorld->tresorNoire);
    texteNoir = TTF_RenderText_Blended(police, tresorNoir, couleurNoire);
    position.x = 600;
    position.y = 60;
    SDL_BlitSurface(texteNoir, NULL, ecran, &position);

    //Chaine tresorRouge
    sprintf(tresorRouge, "Tresor : %d", myWorld->tresorRouge);
    texteRouge = TTF_RenderText_Blended(police, tresorRouge, couleurRouge);
    position.x = 600;
    position.y = 120;
    SDL_BlitSurface(texteRouge, NULL, ecran, &position);

    SDL_Flip(ecran);
}

void videPlateau() {
    TTF_CloseFont(police);

    SDL_FreeSurface(fourmiliere);
    SDL_FreeSurface(ouvriere);
    SDL_FreeSurface(reine);
    SDL_FreeSurface(soldat);
    SDL_FreeSurface(vide);
    SDL_FreeSurface(texteNoir);
    SDL_FreeSurface(texteRouge);
}