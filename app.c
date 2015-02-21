#include <stdio.h>
#include <stdlib.h>
#include "app.h"

#define TMAX 256

//SUPPRIME FOURMI, A FAIRE ET A METTRE DANS INIT
/*

void supprimeFourmi (Fourmi * fourmi, Monde * myWorld){
    
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
    
}

*/



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

void demandeDestination(int *abscisse, int *ordonnee, Monde *monde) {
    int tmp0, tmp1;
    do {
        printf("Donnez une destination : abscisse ? \n");
        scanf("%d", &tmp0);
        *abscisse = tmp0;
        printf("ordonnee ? \n");
        scanf("%d", &tmp1);
        *ordonnee = tmp1;

    } while (tmp0 > monde->plateau->cote || tmp1 > monde->plateau->cote);//A CONTINUER
}

/*void traitementInstruction(Instruction instruction, Monde *myWorld, Fourmi *listeFourmi) {
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
*/
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