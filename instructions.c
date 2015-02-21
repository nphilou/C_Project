#include <stdio.h>
#include <stdlib.h>

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
