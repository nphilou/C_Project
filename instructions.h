#include <stdio.h>
#include <stdlib.h>

#ifndef DEF_INSTRUCTION
#define DEF_INSTRUCTION

void lireEntier(int *entier);

int *couleurTresor(Monde *monde, Fourmi *fourmi);

Instruction demandeInstructionFourmiliere(Monde *monde, Fourmi *listeFourmi);

Instruction demandeInstructionReine(Monde *monde, Fourmi *listeFourmi);

Instruction demandeInstructionSoldat(Monde *monde, Fourmi *listeFourmi);

Instruction demandeInstructionOuvriere(Monde *monde, Fourmi *listeFourmi);

int demandeProduction(Monde *monde, Fourmi *fourmiliere);

void traiteInstructionActuelle(Monde *monde, Fourmi *fourmi);

void traiteInstruction(Monde *monde, Fourmi *fourmi);

Instruction demandeInstruction(Monde *monde, Fourmi *fourmi);

void tour(Monde *monde, Fourmi *joueur, Fourmi *joueurAdverse);

#endif