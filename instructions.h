#include <stdio.h>
#include <stdlib.h>

#ifndef DEF_INSTRUCTION
#define DEF_INSTRUCTION

void lireEntier(int *entier);

int *couleurTresor(Monde *myWorld, Fourmi *fourmi);

Instruction demandeInstructionFourmiliere(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionReine(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionSoldat(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionOuvriere(Monde *myWorld, Fourmi *listeFourmi);

int demandeProduction(Monde *myWorld, Fourmi *fourmi);

void traiteInstructionActuelle(Monde *myWorld, Fourmi *fourmi);

void traiteInstruction(Monde *myWorld, Fourmi *fourmi);

Instruction demandeInstruction(Monde *myWorld, Fourmi *fourmi);

void tour(Monde *myWorld, Fourmi *joueur, Fourmi *joueurAdverse);

#endif