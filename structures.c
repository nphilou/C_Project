#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

typedef struct {
} Case;

typedef struct {
} Reine;

typedef struct {
} Soldat;

typedef struct {

} Ouvriere;

typedef enum {
    REINE,
    SOLDAT,
    OUVRIERE,
    FOURMILIERE,
} TypeFourmi;

typedef enum {
    ROUGE,
    NOIR,
} Couleur;

typedef struct{
    Couleur couleur;
    TypeFourmi type;
    Case destination;
    Case position;
    Fourmiliere *origine;
    Fourmi *suiv;
} Fourmi;

typedef struct {
    Fourmi* fourmi;
    int x;
    int y;
} Case;

typedef struct {
    Fourmiliere *rouge;
    Fourmiliere *noire;
    Case * plateau[5][5];
} Monde;

typedef struct {
    int couleur;
    Case *position;
    int tmpProduc;
    char type[10];
    struct Fourmiliere *origine;
    struct Fourmiliere *suiv;
} Fourmiliere;