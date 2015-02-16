#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "app.h"

Fourmi *initialisation(Couleur couleur, Plateau* plateau) {
	Fourmi *fourmi = calloc(1, sizeof(Fourmi));
	
	//Test allocation memoire
	if (fourmi == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fourmi->couleur = couleur;
	fourmi->type = FOURMILIERE;

	if (couleur == ROUGE)plateau->cases[0].fourmi = fourmi;
	if (couleur == NOIR) plateau->cases[plateau->nombrecases-1].fourmi = fourmi;

	fourmi->suivant = NULL;
	fourmi->precedant = NULL;
	
	return fourmi;
}

Fourmi * initialReine (Couleur couleur, Plateau * plateau, Fourmi * fourmiOrigine){
    Fourmi * fourmi =calloc (1, sizeof(Fourmi)); 
   
    if (fourmi == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fourmi-> couleur = couleur; 
	fourmi-> type = REINE; 
	
	fourmi -> origine = fourmiOrigine; 
	fourmi -> suivant = NULL; 
	fourmi -> precedant = fourmiOrigine; 
	fourmiOrigine -> suivant = fourmi; 
	
	if (couleur == ROUGE) plateau->cases[map(0,1,plateau->cote)].fourmi = fourmi;
	if (couleur == NOIR){
	    printf("bonjour = %d\n", map(plateau-> cote-1,plateau-> cote-2,plateau->cote));
	} plateau->cases[map(plateau-> cote-1,plateau-> cote-2,plateau->cote)].fourmi = fourmi;

	return fourmi;
	
}

Fourmi * initialOuvriere (Couleur couleur, Plateau * plateau, Fourmi * reine){
    Fourmi * fourmi = calloc(1, sizeof(Fourmi)); 
        
    if (fourmi == NULL) {
        exit(EXIT_FAILURE);
	}
	
	fourmi-> couleur = couleur; 
	fourmi-> type = OUVRIERE; 
	
	reine -> suivant = fourmi; 
	fourmi -> precedant = reine; 
	fourmi -> suivant = NULL;

    if (couleur == ROUGE) plateau->cases[map(1,0,plateau->cote)].fourmi = fourmi;
	if (couleur == NOIR) plateau->cases[map(plateau->cote-2,plateau->cote-1,plateau->cote)].fourmi = fourmi;
	
    return fourmi; 
}

void  creationFourmi (Couleur couleur, TypeFourmi typefourmi, Monde* myWorld, int abscisse, int ordonnee){
    
    Fourmi * fourmi = calloc(1, sizeof(Fourmi)); 
    
    if (fourmi == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fourmi -> couleur = couleur; 
	fourmi -> type = typefourmi; 
	
	Fourmi * listeFourmi; 
    if (couleur == ROUGE){
        listeFourmi = myWorld-> rouge -> suivant;  
    } else {
        listeFourmi = myWorld -> noire -> suivant; 
    }
    
	while (listeFourmi -> suivant != NULL){
	    listeFourmi = listeFourmi -> suivant;  
	}
	
    listeFourmi -> suivant = fourmi ;
    fourmi -> precedant = listeFourmi; 
    fourmi -> suivant = NULL; 
    
    if ( myWorld->plateau -> cases [map(ordonnee, abscisse, myWorld->plateau->cote)].fourmi != NULL){
         printf("Bah bravo MORRAY"); 
         return;
    } 
    
    myWorld->plateau -> cases [map(ordonnee, abscisse, myWorld->plateau->cote)].fourmi = fourmi; 
    
}

int map(int ordonnee, int abscisse, int cote) {
    return cote * ordonnee + abscisse;
}


Monde* creationMonde(){
	//Creation Monde
	Monde* myWorld = calloc(1, sizeof(Monde));
	
	//Creation plateau
	int cotePlateau;
	printf("Taille du plateau ? ");
	scanf("%d", &cotePlateau);

    //Test valeur saisie >1
    if(cotePlateau<=1){
        printf("Bah bravo MORRAY !\n");
        exit(1);
    }

	Plateau *plateau = calloc(pow(cotePlateau,2), sizeof(Case));
	plateau->nombrecases = pow(cotePlateau,2);
    plateau->cote = cotePlateau;
    printf("plateau->nombrecases = %d \n", plateau->nombrecases);

    
    myWorld->plateau = plateau;

	//Creation fourmilieres rouge et noire
	myWorld->noire = initialisation(NOIR, plateau);
	myWorld->rouge = initialisation(ROUGE, plateau);
	
	//Creation reines
    myWorld->noire->suivant = initialReine(NOIR, plateau, myWorld->noire);
	myWorld->rouge->suivant = initialReine(ROUGE, plateau, myWorld->rouge);
	
	//Creation ouvrieres
	myWorld->noire->suivant->suivant = initialOuvriere(NOIR, plateau, myWorld->noire->suivant);
	myWorld->rouge->suivant-> suivant = initialOuvriere(ROUGE, plateau, myWorld->rouge->suivant);
	
	
	
	return myWorld;
}

void DeplacementFourmi (Monde * myWorld, Fourmi * fourmi, int abscisse, int ordonnee){
    
    if (myWorld-> plateau -> cases[map(ordonnee, abscisse, myWorld-> plateau-> cote)].fourmi != NULL) {
        printf(" case déja prise"); 
        return; 
    }
    myWorld->plateau-> cases[map(ordonnee, abscisse, myWorld-> plateau-> cote)].fourmi = fourmi; 
    
}

//chiant
int chercheLibre(int centre, Plateau* plateau){
    
    int cote = plateau->cote
    int rayon = 0;
    int haut, droite, bas, gauche;
    int libre = centre;
    
    //tant qu'il n'a pas trouvé de case libre..
    while(libre == centre){
        
        //s'eloigne du centre (rayon augmente)
        for(rayon; rayon<plateau->cote; rayon++){
            
            //haut
            for(haut = centre + r*cote + r; haut > centre + r*cote - r; haut--){
                
            }
            
            //gauche
            
            //bas
            
            //droite
        }
    }
}

void affichePlateau(Plateau* plateau){
    int largeur, hauteur;
    for(hauteur = 0; hauteur < plateau->cote; hauteur++) {
        for (largeur = 0; largeur < plateau->cote; largeur++) {
            //printf("mappage : %d", map(hauteur, largeur, plateau->cote));
            if (plateau->cases[map(hauteur, largeur, plateau->cote)].fourmi == NULL) {
                printf("   ");
            } else {
                switch (plateau->cases[map(hauteur, largeur, plateau->cote)].fourmi->type) {
                    case FOURMILIERE:
                        printf(" F ");
                        break;
                    case SOLDAT:
                        printf(" S ");
                        break;
                    case OUVRIERE:
                        printf(" O ");
                        break;
                    case REINE:
                        printf(" R ");
                        break;
                    default:
                        printf("   ");
                }
            }
            printf(" | ");
        }
        printf("\n\n");
    }
}

/* 

A FAIRE : 

1. Renommer les variables.
2. Enlever les tests.
3. Ajouter la position (entier) dans les fonctions de creation de fourmis
4. Prototypes app.h
5. Fonction estLibre
dac bonne nuit philou ;) 
*/