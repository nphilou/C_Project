#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

void affichePlateauSDL(Plateau *plateau) {
    int largeur, hauteur;
    int couleur;

    for (largeur = 0; largeur < plateau->cote; largeur++) {
        printf(" %d   ", largeur);
    }

    printf("\n");
    for (hauteur = 0; hauteur < plateau->cote; hauteur++) {
        for (largeur = 0; largeur < plateau->cote; largeur++) {
            
            

            if (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi == NULL) {
                printf("    ");
            } else {
                couleur = (int) plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi->couleur;
                switch (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi->type) {
                    case FOURMILIERE:
                        if (!couleur) printf(" Fr ");
                        else printf(" Fn ");
                        break;
                    case SOLDAT:
                        if (!couleur) printf(" Sr ");
                        else printf(" Sn ");
                        break;
                    case OUVRIERE:
                        if (!couleur) printf(" Or ");
                        else printf(" On ");
                        break;
                    case REINE:
                        if (!couleur) printf(" Rr ");
                        else printf(" Rn ");
                        break;
                    default:
                        break;
                }
            }
            printf("|");
        }
        printf(" %d\n\n", hauteur);
    }
}

int main(int argc, char *argv[]) {

    Monde *myWorld = creationMonde();
    affichePlateau(myWorld->plateau);


    SDL_Surface *ecran = NULL, *fourmiliere = NULL, *ouvriere = NULL, *reine = NULL, *soldat = NULL, *vide = NULL;
    SDL_Rect position;
    SDL_Event event;

    position.x = 0;
    position.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_WM_SetCaption("Hohoho", NULL);

    fourmiliere = IMG_Load("miniatures/fourmiliere.png");
    reine = IMG_Load("miniatures/reine.png");
    ouvriere = IMG_Load("miniatures/ouvriere.png");
    soldat = IMG_Load("miniatures/soldat.png");
    vide = IMG_Load("miniatures/vide.png");

    SDL_EnableKeyRepeat(10, 10);
    //SDL_BlitSurface(fourmiliere, NULL, ecran, &position);

    int largeur, hauteur, couleur;
    int cote = myWorld->plateau->cote;

    for (hauteur = 0; hauteur < cote; hauteur++) {
        for (largeur = 0; largeur < cote; largeur++) {

            position.x = largeur * TAILLE_CASE;
            position.y = hauteur * TAILLE_CASE;
            printf("x = %d et y = %d\n", position.x, position.y);

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

    SDL_Flip(ecran);
    pause();

    SDL_FreeSurface(fourmiliere);
    SDL_FreeSurface(ouvriere);
    SDL_FreeSurface(reine);
    SDL_FreeSurface(soldat);
    SDL_FreeSurface(vide);

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