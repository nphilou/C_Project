typedef struct Fourmiliere Fourmiliere;

typedef struct Fourmi Fourmi;


typedef struct {
    Fourmi* fourmi;
    int x;
    int y;
} Case;

typedef struct {
    int taille;
    Case cases[255];
} Plateau;

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

typedef struct {
    Fourmi *rouge;
    Fourmi *noire;
    Plateau* plateau;
} Monde;

struct Fourmi {
    Couleur couleur;
    TypeFourmi type;
    Case* destination;
    Fourmi *origine;
    Fourmi *precedant;
    Fourmi *suivant;
};

struct Fourmiliere {
    int couleur;
    Case *position;
    int tmpProduc;
    char type[10];
    Fourmiliere *origine;
    Fourmiliere *suiv;
};