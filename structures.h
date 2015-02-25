#include "config.h"

typedef struct Fourmi Fourmi;

typedef struct {
    Fourmi *fourmi;
} Case;

typedef struct {
    int cote;
    int nombrecases;
    Case cases[256];
} Plateau;

typedef enum {
    REINE,
    SOLDAT,
    OUVRIERE,
    FOURMILIERE,
} TypeFourmi;

typedef enum {
    PRODUCTION,
    SUICIDE,
    IMMOBILISATION,
    DEPLACEMENT,
    TRANSFORMATION,
    AUCUNE,
} Instruction;

typedef enum {
    ROUGE,
    NOIR,
} Couleur;

typedef struct {
    int tresorRouge;
    int tresorNoire;
    Fourmi *rouge;
    Fourmi *noire;
    Plateau *plateau;
} Monde;

struct Fourmi {
    Couleur couleur;
    TypeFourmi type;
    Instruction instruction;
    int position;
    int destination;

    Fourmi *origine;
    Fourmi *precedant;
    Fourmi *suivant;
    
    Fourmi * voisinSuiv; 
    Fourmi * voisinPrec;
    
    int tempsProd;
    TypeFourmi production;
    Fourmi *fourmiliereSuiv;
    Fourmi *fourmilierePrec;
};