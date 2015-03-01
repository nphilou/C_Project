#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "structures.h"
#include "plateau.h"
#include "init.h"
#include "affichage.h"
#include "instructions.h"
#include "deplacement.h"

void lireEntier(int *entier) {
    char saisie[255];
    while (1) {
        fgets(saisie, 255, stdin);
        if (sscanf(saisie, "%d", entier) == 1) break;
        printf("Veuillez entrer un entier !\n");
    }
}

int *couleurTresor(Monde *myWorld, Fourmi *fourmi) {
    if (fourmi->couleur == ROUGE) return &myWorld->tresorRouge;
    else return &myWorld->tresorNoire;
}

Instruction demandeInstructionFourmiliere(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;
    int productionPossible;

    do {
        printf("Donnez une instruction pour la fourmiliere à la case %d, %d.\n",
                chercheAbscisse(myWorld, listeFourmi->position),
                chercheOrdonnee(myWorld, listeFourmi->position));

        printf("PRODUCTION(0), SUICIDE(1), IMMOBILISATION (2): ");
        lireEntier(&instructiontemp);

        if(!instructiontemp) productionPossible = demandeProduction(myWorld, listeFourmi);

        if (!instructiontemp && !productionPossible){
            printf("Ressources insuffisantes\n");
            continue;
        }

        if (instructiontemp < 0 || instructiontemp > 2)
            printf("Vous m'expliquez ? 0 à 2, ce n'est pas si dur ?\n");

    } while (instructiontemp < 0 || instructiontemp > 2);

    instruction = (Instruction) instructiontemp;

    return instruction;
}

Instruction demandeInstructionReine(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;
    int *tresor = couleurTresor(myWorld, listeFourmi);

    if (*tresor >= COUT_TRANSFORMATION && !chercheFourmiliere(listeFourmi)) {
        do {
            printf("Donnez une instruction pour la reine à la case %d, %d\n",
                    chercheAbscisse(myWorld, listeFourmi->position),
                    chercheOrdonnee(myWorld, listeFourmi->position));
            printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3), TRANSFORMATION(4)(%d) : ", COUT_TRANSFORMATION);
            lireEntier(&instructiontemp);

            if (instructiontemp < 1 || instructiontemp > 4) {
                printf("Vous m'expliquez ? 1 à 4, ce n'est pas si dur ?\n");
            }

        } while (instructiontemp < 1 || instructiontemp > 4);
    } else {
        do {
            printf("Donnez une instruction pour la reine à la case %d, %d\n",
                    chercheAbscisse(myWorld, listeFourmi->position),
                    chercheOrdonnee(myWorld, listeFourmi->position));
            printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3), *transformation impossible* : ");
            lireEntier(&instructiontemp);

            if (instructiontemp < 1 || instructiontemp > 3) {
                printf("Vous m'expliquez ? 1 à 3, ce n'est pas si dur ?\n");
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
        printf("Donnez une instruction pour le soldat à la case %d, %d\n",
                chercheAbscisse(myWorld, listeFourmi->position),
                chercheOrdonnee(myWorld, listeFourmi->position));
        printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3) : ");
        scanf("%d", &instructiontemp);

        if (instructiontemp < 1 || instructiontemp > 3)
            printf("Vous m'expliquez ? 1 à 3, ce n'est pas si dur ?\n");

    } while (instructiontemp < 1 || instructiontemp > 3);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

Instruction demandeInstructionOuvriere(Monde *myWorld, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("Donnez une instruction pour l'ouvriere à la case %d, %d\n",
                chercheAbscisse(myWorld, listeFourmi->position),
                chercheOrdonnee(myWorld, listeFourmi->position));
        printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3) : ");
        scanf("%d", &instructiontemp);

        if (instructiontemp < 1 || instructiontemp > 3)
            printf("Vous m'expliquez ? 1 à 3, ce n'est pas si dur ?\n");

    } while (instructiontemp < 1 || instructiontemp > 3);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

int demandeProduction(Monde *myWorld, Fourmi *fourmi) {
    TypeFourmi production;
    int productiontemp;
    int *tresor = couleurTresor(myWorld, fourmi);

    do {
        printf("Que voulez vous produire ? UNITE(saisie)(temps)(tresor) \n");
        printf("REINE(0)(%d)(%d),"
                " SOLDAT(1)(%d)(%d),"
                " OUVRIERE(2)(%d)(%d) : ",
                TEMPS_REINE,
                COUT_REINE,
                TEMPS_SOLDAT,
                COUT_SOLDAT,
                TEMPS_OUVRIERE,
                COUT_OUVRIERE);

        lireEntier(&productiontemp);
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
                break;
        }
    } while (productiontemp < 0 || productiontemp > 2);

    fourmi->production = production;

    return 1;
}

void traiteInstructionActuelle(Monde *myWorld, Fourmi *fourmi) {
    TypeFourmi type = fourmi->type;
    Couleur couleur = fourmi->couleur;
    int caselibre;

    switch (fourmi->instruction) {

        case PRODUCTION:
            if (fourmi->tempsProd > 0)
                fourmi->tempsProd--;

            if (fourmi->tempsProd == 0) {
                caselibre = chercheLibre(fourmi->position, myWorld);
                creationFourmi(couleur, fourmi->production, fourmi->origine, myWorld, caselibre);
                fourmi->instruction = AUCUNE;
            }
            break;

        case IMMOBILISATION:
            if (type == OUVRIERE) {
                if (couleur == ROUGE) myWorld->tresorRouge += RECOLTE_OUVRIERE;
                if (couleur == NOIR) myWorld->tresorNoire += RECOLTE_OUVRIERE;
            } else {
                fourmi->instruction = AUCUNE;
            }
            break;

        case DEPLACEMENT:
            if (fourmi->position == fourmi->destination) {
                fourmi->instruction = AUCUNE;
            } else {
                deplacementFourmi(myWorld, fourmi,
                        chercheAbscisse(myWorld, fourmi->destination),
                        chercheOrdonnee(myWorld, fourmi->destination));
            }
            break;

        default:
            fourmi->instruction = AUCUNE;
            break;
    }
}

void traiteInstruction(Monde *myWorld, Fourmi *fourmi) {
    Couleur couleur = fourmi->couleur;
    int x, y;
    TypeFourmi type = fourmi->type;

    switch (fourmi->instruction) {

        case SUICIDE:
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
            if (couleur == ROUGE) myWorld->tresorRouge -= COUT_TRANSFORMATION;
            if (couleur == NOIR) myWorld->tresorNoire -= COUT_TRANSFORMATION;
            transformeFourmi(fourmi, myWorld);
            fourmi->instruction = AUCUNE;
            break;

        case PRODUCTION:
            fourmi->instruction = PRODUCTION;
            break;

        default:
            fourmi->instruction = AUCUNE;
            break;
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
            break;
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

    while (listeFourmiliereAdverse != NULL) {
        listeFourmiAdverse = listeFourmiliereAdverse;

        while (listeFourmiAdverse != NULL) {

            traiteInstructionActuelle(myWorld, listeFourmiAdverse);
            listeFourmiAdverse = listeFourmiAdverse->suivant;
        }
        listeFourmiliereAdverse = listeFourmiliereAdverse->fourmiliereSuiv;
    }

    affichePlateauSDL(myWorld);

    while (listeFourmiliere != NULL) {
        listeFourmi = listeFourmiliere;

        while (listeFourmi != NULL) {

            traiteInstructionActuelle(myWorld, listeFourmi);

            affichePlateauSDL(myWorld);

            if (listeFourmi->instruction == AUCUNE) {
                listeFourmi->instruction = demandeInstruction(myWorld, listeFourmi);
                printf("vous avez entré inst = %d", (int) listeFourmi->instruction);
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
