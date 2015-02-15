
typedef struct Fourmiliere Fourmiliere;

typedef struct Fourmi Fourmi;

typedef struct Element Element;


typedef struct {
    Fourmi* fourmi;
    int x;
    int y;
} Case;

typedef struct {
    int taille;
    Case * cases[];
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
    Case* position;
    Fourmiliere *origine;
    Fourmi *suiv;
};

struct Fourmiliere {
    int couleur;
    Case *position;
    int tmpProduc;
    char type[10];
    Fourmiliere *origine;
    Fourmiliere *suiv;
};

struct Element {
	Fourmi fourmi;
	Element * element_precedant;
	Element * element_suivant;
};