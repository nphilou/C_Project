#include "deplacement.h"

Instruction demandeInstructionFourmiliere(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionReine(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionSoldat(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionOuvriere(Monde *myWorld, Fourmi *listeFourmi);

void demandeInstruction(Monde *myWorld, Fourmi *joueur);

void traitementInstruction(Instruction instruction, Monde *myWorld, Fourmi *listeFourmi);
