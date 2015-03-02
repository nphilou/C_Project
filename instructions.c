#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "structures.h"
#include "plateau.h"
#include "init.h"
#include "affichage.h"
#include "instructions.h"
#include "deplacement.h"

void lireEntier(int *entier) {
    char saisie[255] = "";
    char *positionEntree = NULL;

    while (1) {
        fgets(saisie, 255, stdin);
        positionEntree = strchr(saisie, '\n');

        if (positionEntree != NULL) {
            *positionEntree = '\0';
        }

        if (sscanf(saisie, "%d", entier) == 1) break;
    }
}

int *couleurTresor(Monde *monde, Fourmi *fourmi) {
    if (fourmi->couleur == ROUGE) return &monde->tresorRouge;
    else return &monde->tresorNoire;
}

Instruction demandeInstructionFourmiliere(Monde *monde, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;
    int productionPossible = 0;

    do {
        printf("\nDonnez une instruction pour la fourmiliere à la case [%d, %d].\n",
                chercheAbscisse(monde, listeFourmi->position),
                chercheOrdonnee(monde, listeFourmi->position));

        printf("PRODUCTION(0), SUICIDE(1), IMMOBILISATION (2): ");
        lireEntier(&instructiontemp);

        if (!instructiontemp) productionPossible = demandeProduction(monde, listeFourmi);

        if (!instructiontemp && !productionPossible) {
            printf("Ressources insuffisantes.\n");
            continue;
        }

        if (instructiontemp < 0 || instructiontemp > 2)
            printf("Vous m'expliquez ? 0 à 2, ce n'est pas si dur ?\n");

    } while (instructiontemp < 0 || instructiontemp > 2 || (!instructiontemp && !productionPossible));

    instruction = (Instruction) instructiontemp;

    return instruction;
}

Instruction demandeInstructionReine(Monde *monde, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;
    int *tresor = couleurTresor(monde, listeFourmi);

    if (*tresor >= COUT_TRANSFORMATION && monde->plateau->cases[listeFourmi->position].fourmi->type != FOURMILIERE) {
        do {
            printf("\nDonnez une instruction pour la reine à la case [%d, %d]\n",
                    chercheAbscisse(monde, listeFourmi->position),
                    chercheOrdonnee(monde, listeFourmi->position));
            printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3), TRANSFORMATION(4)(%d) : ", COUT_TRANSFORMATION);
            lireEntier(&instructiontemp);

            if (instructiontemp < 1 || instructiontemp > 4) {
                printf("Vous m'expliquez ? 1 à 4, ce n'est pas si dur ?\n");
            }

        } while (instructiontemp < 1 || instructiontemp > 4);
    } else {
        do {
            printf("\nDonnez une instruction pour la reine à la case [%d, %d]\n",
                    chercheAbscisse(monde, listeFourmi->position),
                    chercheOrdonnee(monde, listeFourmi->position));
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

Instruction demandeInstructionSoldat(Monde *monde, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("\nDonnez une instruction pour le soldat à la case [%d, %d]\n",
                chercheAbscisse(monde, listeFourmi->position),
                chercheOrdonnee(monde, listeFourmi->position));
        printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3) : ");
        scanf("%d", &instructiontemp);

        if (instructiontemp < 1 || instructiontemp > 3)
            printf("Vous m'expliquez ? 1 à 3, ce n'est pas si dur ?\n");

    } while (instructiontemp < 1 || instructiontemp > 3);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

Instruction demandeInstructionOuvriere(Monde *monde, Fourmi *listeFourmi) {
    Instruction instruction;
    int instructiontemp;

    do {
        printf("\nDonnez une instruction pour l'ouvriere à la case [%d, %d]\n",
                chercheAbscisse(monde, listeFourmi->position),
                chercheOrdonnee(monde, listeFourmi->position));
        printf("SUICIDE(1), IMMOBILISATION(2), DEPLACEMENT(3) : ");
        scanf("%d", &instructiontemp);

        if (instructiontemp < 1 || instructiontemp > 3)
            printf("Vous m'expliquez ? 1 à 3, ce n'est pas si dur ?\n");

    } while (instructiontemp < 1 || instructiontemp > 3);

    instruction = (Instruction) instructiontemp;
    return instruction;
}

int demandeProduction(Monde *monde, Fourmi *fourmiliere) {
    TypeFourmi production;
    int productiontemp;
    int *tresor = couleurTresor(monde, fourmiliere);

    do {
        printf("Que voulez vous produire ? \nUNITE(saisie)(temps)(tresor) \n");
        printf(" REINE(0)(%d)(%d),\n"
                " SOLDAT(1)(%d)(%d),\n"
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
                fourmiliere->tempsProd = TEMPS_REINE;
                *tresor -= COUT_REINE;
                break;

            case SOLDAT:
                if (*tresor < COUT_SOLDAT) return 0;
                fourmiliere->tempsProd = TEMPS_SOLDAT;
                *tresor -= COUT_SOLDAT;
                break;

            case OUVRIERE:
                if (*tresor < COUT_OUVRIERE) return 0;
                fourmiliere->tempsProd = TEMPS_OUVRIERE;
                *tresor -= COUT_OUVRIERE;
                break;

            default:
                printf("Type de fourmi à produire invalide !\n");
                break;
        }
    } while (productiontemp < 0 || productiontemp > 2);

    fourmiliere->production = production;
    printf("Il reste %d tours avant la production\n", fourmiliere->tempsProd);

    return 1;
}

void traiteInstructionActuelle(Monde *monde, Fourmi *fourmi) {
    TypeFourmi type = fourmi->type;
    Couleur couleur = fourmi->couleur;
    int caselibre;

    switch (fourmi->instruction) {

        case PRODUCTION:
            printf("La fourmilliere sur la case [%d, %d] est en train de produire ! \n",
                    chercheAbscisse(monde, fourmi->position),
                    chercheOrdonnee(monde, fourmi->position));
            if (fourmi->tempsProd > 0) {
                fourmi->tempsProd--;
                printf("Le temps de production restant est de %d tours.\n", fourmi->tempsProd);
            }

            if (fourmi->tempsProd == 0) {

                caselibre = chercheLibre(monde, fourmi->position);
                creationFourmi(monde, fourmi->origine, couleur, fourmi->production, caselibre, AUCUNE);
                fourmi->instruction = AUCUNE;
            }
            break;

        case IMMOBILISATION:
            if (type == OUVRIERE) {
                if (couleur == ROUGE) monde->tresorRouge += RECOLTE_OUVRIERE;
                if (couleur == NOIR) monde->tresorNoire += RECOLTE_OUVRIERE;
            } else {
                fourmi->instruction = AUCUNE;
            }
            break;

        case DEPLACEMENT:
            if (fourmi->position == fourmi->destination) {
                printf("La fourmi à la case [%d, %d] est arrivée à destination.\n",
                        chercheAbscisse(monde, fourmi->position),
                        chercheOrdonnee(monde, fourmi->position));
                fourmi->instruction = AUCUNE;
            } else {
                deplacementFourmi(monde, fourmi,
                        chercheAbscisse(monde, fourmi->destination),
                        chercheOrdonnee(monde, fourmi->destination));
            }
            break;

        case TRANSFORMATION:
            transformeFourmi(monde, fourmi);
            fourmi->instruction = AUCUNE;
            break;

        default:
            fourmi->instruction = AUCUNE;
            break;
    }
}

void traiteInstruction(Monde *monde, Fourmi *fourmi) {
    Couleur couleur = fourmi->couleur;
    int x, y;
    TypeFourmi type = fourmi->type;

    switch (fourmi->instruction) {

        case SUICIDE:
            suicideFourmi(monde, fourmi);
            fourmi->instruction = SUICIDE;
            break;

        case DEPLACEMENT:
            demandeDestination(monde, fourmi, &x, &y);
            deplacementFourmi(monde, fourmi, x, y);
            fourmi->instruction = DEPLACEMENT;
            break;

        case IMMOBILISATION:
            if (type == OUVRIERE) {
                if (couleur == ROUGE) monde->tresorRouge += RECOLTE_OUVRIERE;
                if (couleur == NOIR) monde->tresorNoire += RECOLTE_OUVRIERE;
            }
            fourmi->instruction = IMMOBILISATION;
            break;

        case TRANSFORMATION:
            if (couleur == ROUGE) monde->tresorRouge -= COUT_TRANSFORMATION;
            if (couleur == NOIR) monde->tresorNoire -= COUT_TRANSFORMATION;
            printf("La reine se transformera au prochain tour.\n");
            break;

        case PRODUCTION:
            fourmi->instruction = PRODUCTION;
            break;

        default:
            fourmi->instruction = AUCUNE;
            break;
    }
}

Instruction demandeInstruction(Monde *monde, Fourmi *fourmi) {
    Instruction instruction;

    switch (fourmi->type) {
        case(FOURMILIERE):
            instruction = demandeInstructionFourmiliere(monde, fourmi);
            break;

        case(REINE):
            instruction = demandeInstructionReine(monde, fourmi);
            break;

        case(SOLDAT):
            instruction = demandeInstructionSoldat(monde, fourmi);
            break;

        case(OUVRIERE):
            instruction = demandeInstructionOuvriere(monde, fourmi);
            break;

        default:
            printf("ERREUR : Type de fourmi inconnu.\n");
            instruction = AUCUNE;
            break;
    }

    return instruction;
}

void tour(Monde *monde, Fourmi *joueur, Fourmi *joueurAdverse) {
    Fourmi *listeFourmiliere;
    Fourmi *listeFourmi;
    Fourmi *listeFourmiliereAdverse;
    Fourmi *listeFourmiAdverse;

    listeFourmiliere = joueur;
    listeFourmiliereAdverse = joueurAdverse;

    Couleur couleurjoueur = joueur->couleur;

    printf("\n < Tour courant de l'adversaire >\n");
    while (listeFourmiliereAdverse != NULL) {
        listeFourmiAdverse = listeFourmiliereAdverse;

        while (listeFourmiAdverse != NULL) {

            traiteInstructionActuelle(monde, listeFourmiAdverse);
            listeFourmiAdverse = listeFourmiAdverse->suivant;
        }
        listeFourmiliereAdverse = listeFourmiliereAdverse->fourmiliereSuiv;
    }

    affichePlateauSDL(monde);

    int stop = 0;

    printf("\n < Votre tour >\n");
    while (listeFourmiliere != NULL) {
        listeFourmi = listeFourmiliere;

        while (listeFourmi != NULL) {

            traiteInstructionActuelle(monde, listeFourmi);

            affichePlateauSDL(monde);

            if (listeFourmi->instruction == AUCUNE) {
                listeFourmi->instruction = demandeInstruction(monde, listeFourmi);
                traiteInstruction(monde, listeFourmi);
            }

            affichePlateauSDL(monde);

            if (couleurjoueur == ROUGE) {
                if (monde->rouge == NULL){
                    stop = 1;
                    break;
                }
            }

            if (couleurjoueur == NOIR) {
                if (monde->noire == NULL) {
                    stop = 1;
                    break;
                }
            }

            listeFourmi = listeFourmi->suivant;
        }
        if(stop)break;

        listeFourmiliere = listeFourmiliere->fourmiliereSuiv;
    }
    printf("\n < Tour terminé ! >\n\n");
}
