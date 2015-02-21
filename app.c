#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "app.h"

#define TMAX 256
#define TRESOR 50

Fourmi *initialisation(Couleur couleur, Plateau *plateau) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    //Test allocation memoire
    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = FOURMILIERE;

    if (couleur == ROUGE) plateau->cases[0].fourmi = fourmi;
    if (couleur == NOIR) plateau->cases[plateau->nombrecases - 1].fourmi = fourmi;

    fourmi->suivant = NULL;
    fourmi->precedant = NULL;
    fourmi->tempsProd = 0;

    return fourmi;
}

Fourmi *initialReine(Couleur couleur, Plateau *plateau, Fourmi *fourmiOrigine) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = REINE;
    fourmi->origine = fourmiOrigine;
    fourmi->precedant = fourmiOrigine;
    fourmi->suivant = NULL;

    fourmiOrigine->suivant = fourmi;

    if (couleur == ROUGE) {
        plateau->cases[map(1, 0, plateau->cote)].fourmi = fourmi;
        fourmi->position = map(1, 0, plateau->cote);
    }
    if (couleur == NOIR) {
        plateau->cases[map(plateau->cote - 2, plateau->cote - 1, plateau->cote)].fourmi = fourmi;
        fourmi->position = map(plateau->cote - 2, plateau->cote - 1, plateau->cote);
    }
    return fourmi;

}

Fourmi *initialOuvriere(Couleur couleur, Plateau *plateau, Fourmi *reine) {
    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = OUVRIERE;

    reine->suivant = fourmi;
    fourmi->precedant = reine;
    fourmi->suivant = NULL;

    if (couleur == ROUGE) {
        plateau->cases[map(0, 1, plateau->cote)].fourmi = fourmi;
        fourmi->position = map(0, 1, plateau->cote);
    }
    if (couleur == NOIR) {
        plateau->cases[map(plateau->cote - 1, plateau->cote - 2, plateau->cote)].fourmi = fourmi;
        fourmi->position = map(plateau->cote - 1, plateau->cote - 2, plateau->cote);
    }
    return fourmi;
}

void creationFourmi(Couleur couleur, TypeFourmi typefourmi, Monde *myWorld, int indice) {

    Fourmi *fourmi = calloc(1, sizeof(Fourmi));

    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
    }

    fourmi->couleur = couleur;
    fourmi->type = typefourmi;

    Fourmi *listeFourmi;
    if (couleur == ROUGE) {
        listeFourmi = myWorld->rouge->suivant;
    } else {
        listeFourmi = myWorld->noire->suivant;
    }

    while (listeFourmi->suivant != NULL) {
        listeFourmi = listeFourmi->suivant;
    }

    listeFourmi->suivant = fourmi;
    fourmi->precedant = listeFourmi;
    fourmi->suivant = NULL;

    if (!estLibre(myWorld, indice)) {
        printf("case occupée try again\n");
        return;
    }

    myWorld->plateau->cases[indice].fourmi = fourmi;

}

/*void supprimeFourmi (Fourmi * fourmi, Monde * myWorld){
    
    Fourmi* tmp1 = calloc(1, sizeof(Fourmi)); 
    Fourmi* tmp2 = calloc(1, sizeof(Fourmi)); 
    
    
    
    if ( fourmi -> type != FOURMILIERE){
        tmp1 = fourmi; 
        tmp1 -> precedant -> suivant = tmp1 -> suivant; 
        tmp1 -> suivant -> precedant = tmp1 -> precedant; 
        free (fourmi); 
    }
    else { // si c fourmiliere 
        
        while (fourmi != NULL){
            tmp1 = fourmi; 
            if (tmp1 -> type != OUVRIERE){
                fourmi= fourmi -> suivant;
                fourmi -> precedant = NULL; 
                free(tmp); 
            }
            else { // si c'est une ouvriere 
                if (tmp1 -> couleur == ROUGE){
                    tmp1 -> couleur = NOIR;
                    tmp2 = myWorld -> noire; 
                    while (tmp2 -> suivant != NULL){
                        tmp2 = tmp2 -> suivant; 
                    }
                    tmp1 -> precedant = tmp2; 
                    tmp2 -> suivant = tmp1; 
                    tmp1 -> suivant = NULL; 
                } else {
                    tmp1 -> couleur = ROUGE; 
                    tmp2 = myWorld -> rouge; 
                    while (tmp2 -> suivant != NULL){
                        tmp2 = tmp2 -> suivant; 
                    }
                    tmp1 -> precedant = tmp2; 
                    tmp2 -> suivant= tmp1; 
                    tmp1 -> suivant = NULL; 
                }
                fourmi = fourmi -> suivante; 
            }
        }
    }
    myWorld -> plateau -> cases[ fourmi -> position].fourmi = NULL; 
    
}*/

int map(int abscisse, int ordonnee, int cote) {
    return cote * ordonnee + abscisse;
}

int chercheOrdonnee(Monde *myWorld, int indice) {
    return indice / myWorld->plateau->cote;
}

int chercheAbscisse(Monde *myWorld, int indice) {
    return indice % myWorld->plateau->cote;
}

Monde *creationMonde() {
    //Creation Monde
    Monde *myWorld = calloc(1, sizeof(Monde));

    //Creation plateau
    int cotePlateau = 5;
    printf("Taille du plateau ? ");
    //scanf("%d", &cotePlateau);

    //Test valeur saisie >1
    if (cotePlateau <= 1) {
        printf("Bah bravo MORRAY !\n");
        exit(1);
    }

    Plateau *plateau = calloc((size_t) pow(cotePlateau, 2), sizeof(Case));
    plateau->nombrecases = (int) pow(cotePlateau, 2);
    plateau->cote = cotePlateau;
    printf("plateau->nombrecases = %d \n", plateau->nombrecases);


    myWorld->plateau = plateau;

    //Creation fourmilieres rouge et noire
    myWorld->noire = initialisation(NOIR, plateau);
    myWorld->rouge = initialisation(ROUGE, plateau);


    //Creation reines
    myWorld->noire->suivant = initialReine(NOIR, plateau, myWorld->noire);
    myWorld->rouge->suivant = initialReine(ROUGE, plateau, myWorld->rouge);

    //Creation ouvrieres
    myWorld->noire->suivant->suivant = initialOuvriere(NOIR, plateau, myWorld->noire->suivant);
    myWorld->rouge->suivant->suivant = initialOuvriere(ROUGE, plateau, myWorld->rouge->suivant);

    myWorld->tresorNoire = TRESOR;
    myWorld->tresorRouge = TRESOR;

    return myWorld;
}

int estLibre(Monde *myWorld, int indice) {
    int nombrecases = myWorld->plateau->nombrecases;

    if (indice < 0 || indice > nombrecases - 1) return -1;

    if (myWorld->plateau->cases[indice].fourmi != NULL) {
        return 0;
    }
    return 1;
}

void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int x, int y) {


    int xF = chercheAbscisse(myWorld, fourmi->position);
    int yF = chercheOrdonnee(myWorld, fourmi->position);
    int cote = myWorld->plateau->cote, indice;


    if (xF != x && yF != y) {
        if (xF > x && yF < y) {
            indice = map(xF - 1, yF + 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
        }
        if (xF < x && yF > y) {
            indice = map(xF + 1, yF - 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
        }
        if (xF < x && yF < y) {
            indice = map(xF + 1, yF + 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
            else {
                printf("the location is not empty");
            }
        }
        if (xF > x && yF > y) {
            indice = map(xF - 1, yF - 1, cote);
            if (estLibre(myWorld, indice)) {
                myWorld->plateau->cases[indice].fourmi = fourmi;
                fourmi->position = indice;
                return;
            }
            else {
                printf("the location is not empty");
            }
        }
    }
    else if (xF == x || yF == y) {
        if (yF == y && xF != x) {
            if (xF > x) {
                indice = map(xF - 1, yF, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }
            }
            else {
                indice = map(xF + 1, yF, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }

            }
        }
        if (yF != y && xF == x) {
            if (yF < y) {
                indice = map(xF, yF + 1, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }
            }
            else {
                indice = map(xF, yF - 1, cote);
                if (estLibre(myWorld, indice)) {
                    myWorld->plateau->cases[indice].fourmi = fourmi;
                    fourmi->position = indice;
                    return;
                }
            }
        }
        return;
    }
}

/*LATER
void combatFourmi ( Fourmi * fourmi , Fourmi* fourmi2, Monde * myWorld){
   
   int scoreFourmi = 0; 
   
   if (fourmi-> type == SOLDAT && fourmi2->type != SOLDAT){
        srand(time(NULL)); 
        scoreFourmi= rand()%101; 
        if (scoreFourmi >= 25){
            printf (" vous avez remporté le combat"); 
            plateau -> cases[fourmi2.position].fourmi= fourmi; 
            supprimeFourmi (fourmi2, myWorld); 
        } else {
            printf("vous avez perdu le combat");
            supprimeFourmi (fourmi, myWorld); 
            return;
        }
   }
   
    if (fourmi->type != SOLDAT && fourmi2->type == SOLDAT){
        srand(time(NULL)); 
        scoreFourmi= rand()%101; 
        if (scoreFourmi <= 25){
            printf (" vous avez remporté le combat"); 
            plateau -> cases[fourmi2.position].fourmi= fourmi; 
            supprimeFourmi (fourmi2, myWorld); 
        } else {
            printf("vous avez perdu le combat");
            supprimeFourmi (fourmi, myWorld); 
            return;
        }
    }
    
    if (fourmi -> type != SOLDAT && fourmi2 sssssssssssss->type != SOLDAT){
        srand(time(NULL)); 
        scoreFourmi= rand()%101; 
        do {
            if (scoreFourmi > 50){
                printf (" vous avez remporté le combat"); 
                plateau -> cases[fourmi2.position].fourmi= fourmi; 
                supprimeFourmi (fourmi2, myWorld); 
            } else {
                printf("vous avez perdu le combat");
                supprimeFourmi (fourmi, myWorld); 
                return;
            }
        } while (scoreFourmi==50);
    }
}
*/

int chercheLibre(int centre, Monde *myWorld) {

    int cote = myWorld->plateau->cote; //raccourci
    int rayon;
    int haut, droite, bas, gauche, ligne;
    int ordonnee = chercheOrdonnee(myWorld, centre);
    int abscisse = chercheAbscisse(myWorld, centre);

    //if plateau rempli

    //on s'eloigne du centre (rayon augmente)
    for (rayon = 1; rayon < cote; rayon++) {

        //haut
        for (haut = centre - rayon * cote + rayon; haut >= centre - rayon * cote - rayon; haut--) {
            ligne = ordonnee - rayon;
            if (haut < ligne * cote || haut >= (ligne + 1) * cote || !ordonnee) continue;
            if (estLibre(myWorld, haut)) {
                return haut;
            }
        }

        //gauche
        for (gauche = centre - (rayon - 1) * cote - rayon; gauche <= centre + (rayon - 1) * cote - rayon; gauche += cote) {
            if (!abscisse) continue;
            if (estLibre(myWorld, gauche)) {
                return gauche;
            }
        }

        //bas
        for (bas = centre + rayon * cote - rayon; bas <= centre + rayon * cote + rayon; bas++) {
            ligne = ordonnee + rayon;
            if (bas < ligne * cote || bas >= (ligne + 1) * cote || ordonnee == cote) continue;
            if (estLibre(myWorld, bas)) {
                return bas;
            }
        }

        //droite
        for (droite = centre + rayon * cote + rayon; droite >= centre - (rayon - 1) * cote + rayon; droite -= cote) {
            if (abscisse == cote - 1) continue;
            if (estLibre(myWorld, droite)) {
                return droite;
            }
        }
    }
    return -1;
}

void affichePlateau(Plateau *plateau) {
    int largeur, hauteur;

    for (largeur = 0; largeur < plateau->cote; largeur++) {
        printf(" %d ", largeur);
        printf("   ");
    }
    printf("\n");
    for (hauteur = 0; hauteur < plateau->cote; hauteur++) {
        for (largeur = 0; largeur < plateau->cote; largeur++) {

            if (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi == NULL) {
                printf("   ");
            } else {
                switch (plateau->cases[map(largeur, hauteur, plateau->cote)].fourmi->type) {
                    case FOURMILIERE:
                        printf(" F ");
                        break;
                    case SOLDAT:
                        printf(" S ");
                        break;
                    case OUVRIERE:
                        printf(" O ");
                        break;
                    case REINE:
                        printf(" R ");
                        break;
                    default:
                        printf("   ");
                }
            }
            printf(" | ");
        }
        printf(" %d\n\n", hauteur);
    }
}


/*
    SUICIDE = 0
    DEPLACEMENT = 1
    IMMOBILISATION = 2
    TRANSFORMATIONFOURMILIERE = 3
    PRODUCTION = 4
    */

Instruction demandeInstructionFourmiliere(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("Donnez une instruction pour la fourmiliere à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
        printf("PRODUCTION(0), SUICIDE(1) : ");
        scanf("%d", &instructiontemp);
        if (instructiontemp != 0 || instructiontemp != 1) {
            printf("Vous m'expliquez ? 0 ou 1, c'est pas si dur ?\n"); //A REVOIR
        }
    } while (instructiontemp != 0 || instructiontemp != 1);
    instruction = (Instruction) instructiontemp;

    return instruction;
}

Instruction demandeInstructionReine(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("Donnez une instruction pour la reine à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
        printf("SUICIDE(1), DEPLACEMENT(2), IMMOBILISATION(3), TRANSFORMATION(4) : ");
        scanf("%d", &instructiontemp);
        if (instructiontemp < 1 || instructiontemp > 4) {
            printf("Vous m'expliquez ? 1 à 4, c'est pas si dur ?\n");
        }
    } while (instructiontemp < 1 || instructiontemp > 4);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

Instruction demandeInstructionSoldat(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("Donnez une instruction pour le soldat à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
        printf("SUICIDE(1), DEPLACEMENT(2), IMMOBILISATION(3) : ");
        scanf("%d", &instructiontemp);
        if (instructiontemp < 1 || instructiontemp > 3) {
            printf("Vous m'expliquez ? 1 à 3, c'est pas si dur ?\n");
        }
    } while (instructiontemp < 1 || instructiontemp > 3);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

Instruction demandeInstructionOuvriere(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("Donnez une instruction pour l'ouvriere à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
        printf("SUICIDE(1), DEPLACEMENT(2), IMMOBILISATION(3) : ");
        scanf("%d", &instructiontemp);
        if (instructiontemp < 1 || instructiontemp > 3) {
            printf("Vous m'expliquez ? 1 à 3, c'est pas si dur ?\n");
        }
    } while (instructiontemp < 1 || instructiontemp > 3);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

void demandeDestination(int *abscisse, int *ordonnee) {
    do {
        printf("Donnez une destination : abscisse ? \n");
        scanf("%d", &abscisse);
        printf("ordonnee ? \n");
        scanf("%d", &ordonnee);

    }while (abscisse);//A CONTINUER
}

void traitementInstruction(Instruction instruction, Monde *myWorld, Fourmi *listeFourmi) {
    int x, y;
    switch (instruction) {
        case SUICIDE:
            //if fourmiliere, destruction totale (ecrire fonction pour detruire la fourmiliere avec 2 cas : prise ou suicide ?
            //tuer unité
            break;
        case DEPLACEMENT:

            deplacementFourmi(myWorld, listeFourmi, x, y);
            break;
        case IMMOBILISATION:
            //cas a traiter avec tresor et tout..
        default:
            printf("cas vide"); //renommer
    }
}

void demandeInstruction(Monde *myWorld, Fourmi *joueur) {
    Fourmi *listeFourmiliere;
    Fourmi *listeFourmi;


    Instruction instruction;
    TypeFourmi production;
    int x, y;

    Couleur couleur = joueur->couleur;
    listeFourmiliere = joueur;

    int productiontmp;

    while (listeFourmiliere != NULL) {
        listeFourmi = listeFourmiliere;
        while (listeFourmi != NULL) {
            //if pas d'instruction : immobilisation = tresor, transfo = tmptransfo--, production : tmpprod--

            if (listeFourmi->type == FOURMILIERE) {
                //Fourmiliere occupee
                if (listeFourmi->tempsProd > 0) {
                    listeFourmi->tempsProd--;
                    break;
                }

                instruction = demandeInstructionFourmiliere(myWorld, listeFourmi);

                //Traitement instruction
                switch (instruction) {
                    case SUICIDE:
                        printf("SUICIDE FOURMILIERE !!!!");
                        break;
                    case PRODUCTION:
                        printf("Que voulez vous produire ?\n");
                        printf("REINE(0), SOLDAT(1), OUVRIERE(2)");
                        scanf("%d", &productiontmp);
                        production = (TypeFourmi) productiontmp;
                        switch (production) {
                            case REINE:
                                creationFourmi(couleur, REINE, myWorld, chercheLibre(listeFourmiliere->position, myWorld));
                                //tmpprod !!!
                                break;
                            case SOLDAT:
                                creationFourmi(couleur, SOLDAT, myWorld, chercheLibre(listeFourmiliere->position, myWorld));
                                break;
                            case OUVRIERE:
                                creationFourmi(couleur, OUVRIERE, myWorld, chercheLibre(listeFourmiliere->position, myWorld));
                                break;
                            default:
                                printf("type de fourmi à produire invalide");
                        }
                        break;
                    default:
                        printf("cas vide"); //renommer
                }
            } else {

            }
            listeFourmi = listeFourmi->suivant;
        }
        listeFourmiliere = listeFourmiliere->fourmiliereSuiv;
    }

}



/* 
A FAIRE : 

1. Renommer les variables.
2. Enlever les tests.
3. Ajouter la position (entier) dans les fonctions de creation de fourmis
4. Prototypes app.h
6. Free !!!
7. if def pour savoir qui commence


*/