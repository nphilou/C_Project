
typedef struct Fourmiliere Fourmiliere;

typedef struct Fourmi Fourmi;

typedef struct {
    Fourmi* fourmi;
    int x;
    int y;
} Case;

typedef struct {
    int taille;
    Case * cases[];
} Plateau;

/*typedef struct {
} Reine;

typedef struct {
} Soldat;

typedef struct {

} Ouvriere;*/

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
    Fourmiliere *rouge;
    Fourmiliere *noire;
    Case * plateau[5][5];
} Monde;


struct Fourmi {
    Couleur couleur;
    TypeFourmi type;
    Case destination;
    Case position;
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
