#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "app.h"

#define TAILLE_CASE 80

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

void affichePlateauSDL(Monde *myWorld, TTF_Font *police, SDL_Surface *ecran, SDL_Surface *fourmiliere, SDL_Surface *ouvriere, SDL_Surface *reine, SDL_Surface *soldat, SDL_Surface *vide, SDL_Surface *texteNoir, SDL_Surface *texteRouge){
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
            //printf("x = %d et y = %d\n", position.x, position.y);

            if(myWorld->plateau->cases[map(largeur, hauteur, cote)].fourmi == NULL){
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

int main(int argc, char *argv[]) {

    //Creation monde
    Monde *myWorld = creationMonde();
    affichePlateau(myWorld->plateau);


    //Declaration surfaces, unites, evenement, police
    SDL_Surface *ecran = NULL, *fourmiliere = NULL, *ouvriere = NULL, *reine = NULL, *soldat = NULL, *vide = NULL;
    SDL_Surface *texteNoir = NULL, *texteRouge = NULL;
    TTF_Font *police = NULL;
    SDL_Event event;

    //Initialisation SDL et SDL_ttf
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //Creation fenetre
    ecran = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_WM_SetCaption("Hohoho", NULL);

    //Chargement miniatures unites
    fourmiliere = IMG_Load("miniatures/fourmiliere.png");
    reine = IMG_Load("miniatures/reine.png");
    ouvriere = IMG_Load("miniatures/ouvriere.png");
    soldat = IMG_Load("miniatures/soldat.png");
    vide = IMG_Load("miniatures/vide.png");

    //Chargement police
    police = TTF_OpenFont("fonts/minecraftia.ttf", 30);

    SDL_EnableKeyRepeat(10, 10);

    affichePlateauSDL(myWorld, police, ecran, fourmiliere, ouvriere, reine, soldat, vide, texteNoir, texteRouge);

    int premierJoueur = (int) ROUGE;
    int i = 1;
    while(i){
        printf("((((((((((((((((TOUR ROUGE))))))))))))))))\n");
        tour(myWorld, myWorld->rouge, myWorld->noire);
        printf("((((((((((((((((TOUR NOIR))))))))))))))))\n");
        tour(myWorld, myWorld->noire, myWorld->rouge);
        printf("Quitter ? OUI(0), NON(1)");
        scanf("%d", &i);
    }

    SDL_Flip(ecran);

    affichePlateauSDL(myWorld, police, ecran, fourmiliere, ouvriere, reine, soldat, vide, texteNoir, texteRouge);

    pause();

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(fourmiliere);
    SDL_FreeSurface(ouvriere);
    SDL_FreeSurface(reine);
    SDL_FreeSurface(soldat);
    SDL_FreeSurface(vide);
    SDL_FreeSurface(texteNoir);
    SDL_FreeSurface(texteRouge);

    SDL_Quit();


    /*
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

    }*/
/*
    SDL_FreeSurface(fourmiliere);
    SDL_FreeSurface(ouvriere);
    SDL_FreeSurface(reine);
    SDL_FreeSurface(soldat);
    SDL_FreeSurface(vide);
    SDL_Quit();
*/
    
/*
    int premierJoueur = (int) ROUGE;
    int i = 1;
    while(i){
        printf("((((((((((((((((TOUR ROUGE))))))))))))))))\n");
        tour(myWorld, myWorld->rouge, myWorld->noire);
        printf("((((((((((((((((TOUR NOIR))))))))))))))))\n");
        tour(myWorld, myWorld->noire, myWorld->rouge);
        printf("Quitter ? OUI(0), NON(1)");
        scanf("%d", &i);
    }
    */
    return 0;
}