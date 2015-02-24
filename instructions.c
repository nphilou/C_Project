#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"

//renommer listefourmi

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

TypeFourmi demandeProduction(Monde *myWorld, Fourmi *fourmi) {
    TypeFourmi production;
    int productiontemp;
    Couleur couleur = fourmi->couleur;

    do {
        printf("Que voulez vous produire ?\n");
        printf("REINE(0), SOLDAT(1), OUVRIERE(2)"); //donner temps !
        scanf("%d", &productiontemp);
        production = (TypeFourmi) productiontemp;
        switch (production) {
            case REINE:
                fourmi->tempsProd = 6;
                //A SUIVRE
                break;
            case SOLDAT:
                creationFourmi(couleur, SOLDAT, fourmi->origine, myWorld, chercheLibre(fourmi->position, myWorld));
                break;
            case OUVRIERE:
                creationFourmi(couleur, OUVRIERE, fourmi->origine, myWorld, chercheLibre(fourmi->position, myWorld));
                break;
            default:
                printf("type de fourmi à produire invalide");
        }
        if (productiontemp < 0 || productiontemp != 1 || productiontemp != 2) {
            printf("Vous m'expliquez ? 0 à 2, c'est pas si dur ?\n"); //A REVOIR
        }
    } while (productiontemp != 0 || productiontemp != 1 || productiontemp != 2);
    production = (TypeFourmi) productiontemp;

    return production;
}

void traiteInstructionActuelle(Monde *myWorld, Fourmi *fourmi){
    TypeFourmi type = fourmi->type;
    Couleur couleur = fourmi->couleur;
    int caselibre;
    //TypeFourmi production = fourmi->production;

    switch (fourmi->instruction) {

        case PRODUCTION:
            if (fourmi->tempsProd > 0) {
                fourmi->tempsProd--;
            } else {
                caselibre = chercheLibre(fourmi->position, myWorld);
                creationFourmi(couleur, fourmi->production, fourmi->origine, myWorld, caselibre);
                //ca depend ! ^
                fourmi->instruction = AUCUNE;
            }
            break;

        case IMMOBILISATION:
            if (type == OUVRIERE) {
                if (couleur == ROUGE) myWorld->tresorRouge++;
                if (couleur == NOIR) myWorld->tresorNoire++;
            } else {
                fourmi->instruction = AUCUNE;
            }
            break;
            
        case DEPLACEMENT:
            if (fourmi->position == fourmi->destination) {
                fourmi->instruction = AUCUNE;
            } else {
                deplacementFourmi(myWorld, fourmi, chercheAbscisse(myWorld, fourmi->destination), chercheOrdonnee(myWorld, fourmi->destination));
            }
            break;

        default:
            fourmi->instruction = AUCUNE;
    }
}

//apres
void traiteInstruction(Monde *myWorld, Fourmi *fourmi) {
    Couleur couleur = fourmi->couleur;
    int x, y;
    TypeFourmi type = fourmi->type;

    switch (fourmi->instruction) {
    
        case SUICIDE:
            suicideFourmi(fourmi, myWorld);
            break;
            
        case DEPLACEMENT:
            demandeDestination(&x, &y, myWorld, fourmi);
            deplacementFourmi(myWorld, fourmi, x, y);
            fourmi->instruction = DEPLACEMENT;
            break;
            
        case IMMOBILISATION:
            if (type == OUVRIERE) {
                if (couleur == ROUGE) myWorld->tresorRouge++;
                if (couleur == NOIR) myWorld->tresorNoire++;
            }
            fourmi->instruction = IMMOBILISATION;
            
        case TRANSFORMATION:
            //transformation !!!
            
        case PRODUCTION:

        default:
            printf("cas vide");
    }
}

void demandeInstruction(Monde *myWorld, Fourmi *fourmi){
    switch (fourmi->type) {
        case(FOURMILIERE):
            instruction = demandeInstructionFourmiliere(myWorld, fourmi);
            break;

        case(REINE):
            instruction = demandeInstructionReine(myWorld, fourmi);
            break;

        case(SOLDAT):
            instruction = demandeInstructionSoldat(myWorld, fourmi);
            break;

        case(OUVRIERE):
            instruction = demandeInstructionOuvriere(myWorld, fourmi);
    }
}

void tour(Monde *myWorld, Fourmi *joueur) {
    Fourmi *listeFourmiliere;
    Fourmi *listeFourmi;
    Instruction instruction;
    
    listeFourmiliere = joueur;
    
    while (listeFourmiliere != NULL) {
        listeFourmi = listeFourmiliere;
        while (listeFourmi != NULL) {
            
            traiteInstruction(myWorld, listeFourmi);
            
            
            
            

            if (listeFourmi->instruction == AUCUNE) {
                demandeInstruction(myWorld, listeFourmi);
            }

            traiteInstruction(instruction);
            
            listeFourmi = listeFourmi->suivant;
        }
        listeFourmiliere = listeFourmiliere->fourmiliereSuiv;
    }
}