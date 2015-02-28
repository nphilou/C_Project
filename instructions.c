#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "structures.h"
#include "instructions.h"
#include "plateau.h"
#include "init.h"
#include "affichage.h"




//renommer listefourmi + isdigit !

int *couleurTresor(Monde *myWorld, Fourmi *fourmi) {
    if (fourmi->couleur == ROUGE) return &myWorld->tresorRouge;
    else return &myWorld->tresorNoire;
}

Instruction demandeInstructionFourmiliere(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("Donnez une instruction pour la fourmiliere à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
        printf("PRODUCTION(0), SUICIDE(1), IMMOBILISATION (2): ");
        scanf("%d", &instructiontemp);

        if (!instructiontemp && !demandeProduction(myWorld, listeFourmi)) {
            printf("Ressources insuffisantes\n");
        }
        if (instructiontemp < 0 || instructiontemp > 2) {
            printf("Vous m'expliquez ? 0 à 2, c'est pas si dur ?\n"); //A REVOIR
        }
    } while (instructiontemp < 0 || instructiontemp > 2);

    instruction = (Instruction) instructiontemp;

    return instruction;
}

Instruction demandeInstructionReine(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;
    int *tresor = couleurTresor(myWorld, listeFourmi);

    if (*tresor > COUT_TRANSFORMATION) {
        do {
            printf("Donnez une instruction pour la reine à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
            printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3), TRANSFORMATION(4) : ");
            scanf("%d", &instructiontemp);
            if (instructiontemp < 1 || instructiontemp > 4) {
                printf("Vous m'expliquez ? 1 à 4, c'est pas si dur ?\n");
            }
        } while (instructiontemp < 1 || instructiontemp > 4);
    } else {
        do {
            printf("Donnez une instruction pour la reine à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
            printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3), *tresor insuffisant pour la tranformation* : ");
            scanf("%d", &instructiontemp);
            if (instructiontemp < 1 || instructiontemp > 3) {
                printf("Vous m'expliquez ? 1 à 4, c'est pas si dur ?\n");
            }
        } while (instructiontemp < 1 || instructiontemp > 3);
    }

    instruction = (Instruction) instructiontemp;
    return instruction;
}

Instruction demandeInstructionSoldat(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("Donnez une instruction pour le soldat à la case %d, %d\n", chercheAbscisse(myWorld, listeFourmi->position), chercheOrdonnee(myWorld, listeFourmi->position));
        printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3) : ");
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
        printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3) : ");
        scanf("%d", &instructiontemp);
        if (instructiontemp < 1 || instructiontemp > 3) {
            printf("Vous m'expliquez ? 1 à 3, c'est pas si dur ?\n");
        }
    } while (instructiontemp < 1 || instructiontemp > 3);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

int demandeProduction(Monde *myWorld, Fourmi *fourmi) {
    TypeFourmi production;
    int productiontemp;
    int *tresor = couleurTresor(myWorld, fourmi);

    do {
        printf("Que voulez vous produire ?\n");
        printf("REINE(0), SOLDAT(1), OUVRIERE(2) : "); //donner temps !
        scanf("%d", &productiontemp);
        production = (TypeFourmi) productiontemp;

        switch (production) {
            case REINE:
                if (*tresor < COUT_REINE) return 0;
                fourmi->tempsProd = TEMPS_REINE;
                *tresor -= COUT_REINE;
                break;

            case SOLDAT:
                if (*tresor < COUT_SOLDAT) return 0;
                fourmi->tempsProd = TEMPS_SOLDAT;
                *tresor -= COUT_SOLDAT;
                break;

            case OUVRIERE:
                if (*tresor < COUT_OUVRIERE) return 0;
                fourmi->tempsProd = TEMPS_OUVRIERE;
                *tresor -= COUT_OUVRIERE;
                break;

            default:
                printf("Type de fourmi à produire invalide !\n");
        }
    } while (productiontemp < 0 || productiontemp > 2);

    fourmi->production = production;

    return 1;
}

void traiteInstructionActuelle(Monde *myWorld, Fourmi *fourmi) {
    TypeFourmi type = fourmi->type;
    Couleur couleur = fourmi->couleur;
    int caselibre;

    //printf("inst de fourmi = %d", fourmi->instruction)

    switch (fourmi->instruction) {

        case PRODUCTION:
            printf("cas production\n");
            if (fourmi->tempsProd > 0) {
                fourmi->tempsProd--;
            }
            //METTRE DANS LA MEME CASE QUE LA FOURMILIERE
            if (fourmi->tempsProd == 0) {
                caselibre = chercheLibre(fourmi->position, myWorld);
                creationFourmi(couleur, fourmi->production, fourmi->origine, myWorld, caselibre);
                fourmi->instruction = AUCUNE;
            }
            break;

        case IMMOBILISATION:
            printf("cas immo\n");
            if (type == OUVRIERE) {
                if (couleur == ROUGE) myWorld->tresorRouge += RECOLTE_OUVRIERE;
                if (couleur == NOIR) myWorld->tresorNoire += RECOLTE_OUVRIERE;
            } else {
                fourmi->instruction = AUCUNE;
            }
            break;

        case DEPLACEMENT:
            printf("cas deplacement\n");
            if (fourmi->position == fourmi->destination) {
                printf("je suis arrive !");
                fourmi->instruction = AUCUNE;
            } else {

                deplacementFourmi(myWorld, fourmi, chercheAbscisse(myWorld, fourmi->destination), chercheOrdonnee(myWorld, fourmi->destination));
            }
            break;

        case TRANSFORMATION:
            transformeFourmi(fourmi, myWorld);
            fourmi->instruction = AUCUNE;
            break;

        default:
            printf("cas defaut\n");
            fourmi->instruction = AUCUNE;
    }
}

void traiteInstruction(Monde *myWorld, Fourmi *fourmi) {
    Couleur couleur = fourmi->couleur;
    int x, y;
    TypeFourmi type = fourmi->type;

    switch (fourmi->instruction) {

        case SUICIDE:
            printf("cas suicide !!\n");
            suicideFourmi(fourmi, myWorld);
            fourmi->instruction = SUICIDE;
            break;

        case DEPLACEMENT:
            demandeDestination(&x, &y, myWorld, fourmi);
            deplacementFourmi(myWorld, fourmi, x, y);
            fourmi->instruction = DEPLACEMENT;
            break;

        case IMMOBILISATION:
            if (type == OUVRIERE) {
                if (couleur == ROUGE) myWorld->tresorRouge += RECOLTE_OUVRIERE;
                if (couleur == NOIR) myWorld->tresorNoire += RECOLTE_OUVRIERE;
            }
            fourmi->instruction = IMMOBILISATION;
            break;

        case TRANSFORMATION:
            fourmi->instruction = TRANSFORMATION;
            break;

        case PRODUCTION:
            fourmi->instruction = PRODUCTION;
            break;
        default:
            fourmi->instruction = AUCUNE;
    }
}

Instruction demandeInstruction(Monde *myWorld, Fourmi *fourmi) {
    Instruction instruction;

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
            break;

        default:
            printf("ERREUR : Type de fourmi inconnu");
            instruction = AUCUNE;
    }

    return instruction;
}

void tour(Monde *myWorld, Fourmi *joueur, Fourmi *joueurAdverse) {
    Fourmi *listeFourmiliere;
    Fourmi *listeFourmi;
    Fourmi *listeFourmiliereAdverse;
    Fourmi *listeFourmiAdverse;

    listeFourmiliere = joueur;
    listeFourmiliereAdverse = joueurAdverse;

    printf("Traitement instruction courante adverse !");
    while (listeFourmiliereAdverse != NULL) {
        listeFourmiAdverse = listeFourmiliereAdverse;

        while (listeFourmiAdverse != NULL) {

            traiteInstructionActuelle(myWorld, listeFourmiAdverse);
            //AFFICHER ?
            listeFourmiAdverse = listeFourmiAdverse->suivant;
        }
        listeFourmiliereAdverse = listeFourmiliereAdverse->fourmiliereSuiv;

    }
    printf("Traitement instruction courante adverse !");
    affichePlateauSDL(myWorld);

    while (listeFourmiliere != NULL) {
        listeFourmi = listeFourmiliere;
        while (listeFourmi != NULL) {

            traiteInstructionActuelle(myWorld, listeFourmi);

            if (listeFourmi->instruction == AUCUNE) {
                listeFourmi->instruction = demandeInstruction(myWorld, listeFourmi);

                traiteInstruction(myWorld, listeFourmi);
            }

            affichePlateauSDL(myWorld);

            if (listeFourmi->type == FOURMILIERE && listeFourmi->instruction == SUICIDE) break;
            listeFourmi = listeFourmi->suivant;
        }
        listeFourmiliere = listeFourmiliere->fourmiliereSuiv;
    }
    printf("Tour terminé !");
}
