#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "structures.h"
#include "affichage.h"
#include "plateau.h"

static SDL_Surface *ecran = NULL,

        *fourmiliereR = NULL,
        *ouvriereR = NULL,
        *reineR = NULL,
        *soldatR = NULL,

        *fourmiliereN = NULL,
        *ouvriereN = NULL,
        *reineN = NULL,
        *soldatN = NULL,

        *vide = NULL,
        *caseplateau = NULL,

        *texteNoir = NULL,
        *texteRouge = NULL;

static TTF_Font *police = NULL;


void initPlateau() {
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE);

    fourmiliereR = IMG_Load("miniatures/fourmiliereR.png");
    ouvriereR = IMG_Load("miniatures/ouvriereR.png");
    reineR = IMG_Load("miniatures/reineR.png");
    soldatR = IMG_Load("miniatures/soldatR.png");

    fourmiliereN = IMG_Load("miniatures/fourmiliere.png");
    ouvriereN = IMG_Load("miniatures/ouvriere.png");
    reineN = IMG_Load("miniatures/reine.png");
    soldatN = IMG_Load("miniatures/soldat.png");

    caseplateau = IMG_Load("miniatures/case.png");
    vide = IMG_Load("miniatures/vide.png");

    texteNoir = NULL;
    texteRouge = NULL;

    police = TTF_OpenFont("fonts/minecraftia.ttf", 30);
}

void affichePlateauSDL(Monde *myWorld) {

    //On veut declarer les images une seule fois
    static int initialisation = 0;
    if (!initialisation) {
        initPlateau();
        initialisation = 1;
    }

    //Couleur plateau
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 200, 200, 200));

    SDL_Rect position;

    //Texte tresor
    char tresorNoir[20] = "";
    char tresorRouge[20] = "";

    //Definition couleurs
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurRouge = {255, 60, 60};

    //Definition position *optionnel*
    position.x = 0;
    position.y = 0;

    //Variables pour l'affichage 2D
    int largeur, hauteur, couleur;
    int cote = myWorld->plateau->cote;

    for (hauteur = 0; hauteur < cote; hauteur++) {
        for (largeur = 0; largeur < cote; largeur++) {

            position.x = largeur * TAILLE_CASE + 20;
            position.y = hauteur * TAILLE_CASE + 20;

            SDL_BlitSurface(caseplateau, NULL, ecran, &position);

            if (myWorld->plateau->cases[map(largeur, hauteur, cote)].fourmi == NULL) {
                SDL_BlitSurface(vide, NULL, ecran, &position);
                continue;
            }

            couleur = (int) myWorld->plateau->cases[map(largeur, hauteur, cote)].fourmi->couleur;
            switch (myWorld->plateau->cases[map(largeur, hauteur, cote)].fourmi->type) {

                case FOURMILIERE:
                    if (!couleur) SDL_BlitSurface(fourmiliereR, NULL, ecran, &position);
                    else
                        SDL_BlitSurface(fourmiliereN, NULL, ecran, &position);
                    break;

                case SOLDAT:
                    if (!couleur) SDL_BlitSurface(soldatR, NULL, ecran, &position);
                    else
                        SDL_BlitSurface(soldatN, NULL, ecran, &position);
                    break;

                case OUVRIERE:
                    if (!couleur) SDL_BlitSurface(ouvriereR, NULL, ecran, &position);
                    else
                        SDL_BlitSurface(ouvriereN, NULL, ecran, &position);
                    break;

                case REINE:
                    if (!couleur) SDL_BlitSurface(reineR, NULL, ecran, &position);
                    else
                        SDL_BlitSurface(reineN, NULL, ecran, &position);
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
    position.y = 120;
    SDL_BlitSurface(texteNoir, NULL, ecran, &position);

    //Chaine tresorRouge
    sprintf(tresorRouge, "Tresor : %d", myWorld->tresorRouge);
    texteRouge = TTF_RenderText_Blended(police, tresorRouge, couleurRouge);
    position.x = 600;
    position.y = 60;
    SDL_BlitSurface(texteRouge, NULL, ecran, &position);

    SDL_Flip(ecran);
}