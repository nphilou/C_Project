#include "init.h"

void supprimeFourmi(Fourmi *fourmi, Monde *myWorld);

void deplacementFourmi(Monde *myWorld, Fourmi *fourmi, int x, int y);

//void CombatFourmi(Fourmi *fourmiAttaquante, Fourmi *fourmi2, Monde *myworld);

Instruction demandeInstructionFourmiliere(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionReine(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionSoldat(Monde *myWorld, Fourmi *listeFourmi);

Instruction demandeInstructionOuvriere(Monde *myWorld, Fourmi *listeFourmi);

void demandeDestination(int *abscisse, int *ordonnee, Monde* monde);

void traitementInstruction(Instruction instruction, Monde *myWorld, Fourmi *listeFourmi);

void demandeInstruction(Monde *myWorld, Fourmi *joueur);