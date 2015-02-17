#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "app.h"
#define TMAX 256

Fourmi *initialisation(Couleur couleur, Plateau* plateau) {
	Fourmi *fourmi = calloc(1, sizeof(Fourmi));
	
	//Test allocation memoire
	if (fourmi == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fourmi->couleur = couleur;
	fourmi->type = FOURMILIERE;

	if (couleur == ROUGE) plateau->cases[0].fourmi = fourmi;
	if (couleur == NOIR) plateau->cases[plateau->nombrecases-1].fourmi = fourmi;

	fourmi->suivant = NULL;
	fourmi->precedant = NULL;
	
	return fourmi;
}

Fourmi *initialReine (Couleur couleur, Plateau * plateau, Fourmi * fourmiOrigine){
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
	if (couleur == NOIR) plateau->cases[map(plateau-> cote-1,plateau-> cote-2,plateau->cote)].fourmi = fourmi;

	return fourmi;
	
}

Fourmi *initialOuvriere (Couleur couleur, Plateau * plateau, Fourmi * reine){
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

void  creationFourmi (Couleur couleur, TypeFourmi typefourmi, Monde* myWorld, int indice){
    
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
    
    if ( !estLibre(myWorld, indice)){
         printf("case occupée try again"); 
         return;
    } 
    
    myWorld->plateau -> cases [indice].fourmi = fourmi; 
    
}

void supprimeFourmi (Fourmi * fourmi, Monde * myWorld){
    
    Fourmi* tmp1 = calloc(1, sizeof(Fourmi)); 
    Fourmi* tmp2 = calloc(1, sizeof(Fourmi)); 
    
    if ( fourmi -> type != FOURMILIERE){
        tmp1 = fourmi; 
        tmp1 -> precedent -> suivant = tmp1 -> suivant; 
        tmp1 -> suivant -> precedant = tmp -> precedeant; 
        free (fourmi2); 
    }
    else { // si c fourmiliere 
        
        while (fourmi != NULL){
            tmp1 = fourmi; 
            if (tmp1 -> type != OUVRIERE){
                fourmi= fourmi -> suivant;
                fourmi -> precedant = NULL; 
                free(tmp); 
            }
            else { // si c'est une ouvriere 
                if (tmp1 -> couleur == ROUGE){
                    tmp1 -> couleur = NOIR;
                    tmp2 = myWorld -> noire; 
                    while (tmp2 -> suivant != NULL){
                        tmp2 = tmp2 -> suivant; 
                    }
                    tmp1 -> precedant = tmp2; 
                    tmp2 -> suivant = tmp1; 
                    tmp1 -> suivant = NULL; 
                } else {
                    tmp1 -> couleur = ROUGE; 
                    tmp2 = myWorld -> rouge; 
                    while (tmp2 -> suivant != NULL){
                        tmp2 = tmp2 -> suivant; 
                    }
                    tmp1 -> precedent = tmp2; 
                    tmp2 -> suivant= tmp1; 
                    tmp1 -> suivant = NULL; 
                }
                fourmi = fourmi -> suivante; 
            }
        }
    }
    myWorld -> plateau -> cases[ fourmi -> position].fourmi = NULL; 
    
}

int map(int ordonnee, int abscisse, int cote){
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

/*int estLibre(Monde* myWorld, int abscisse, int ordonnee){
    int cote = myWorld->plateau->cote;
    
    if (abscisse < 0 || ordonnee < 0 || abscisse > cote-1 || ordonnee > cote-1 ) return -1;
    
    if (myWorld -> plateau -> cases[map(ordonnee, abscisse, cote)].fourmi != NULL) {
        return 0; 
    }
    return 1;
}*/

int estLibre(Monde* myWorld, int indice){
    int cote = myWorld->plateau->cote;
    
    if (indice < 0 || indice > cote-1) return -1;
    
    if (myWorld -> plateau -> cases[indice].fourmi != NULL) {
        return 0; 
    }
    return 1;
}

void deplacementFourmi (Monde * myWorld, Fourmi * fourmi, int abscisse, int ordonnee){
    int cote = myWorld->plateau->cote;
    int indice = map(ordonnee, abscisse, cote);
    
    
    int cheminParcouru [TMAX]; //met un #define plutot
    int cheminPrec [TMAX];
    
    
    //J'ai fini ma fonction en theorie, go dodo + +
    
    
   
    if (estLibre(myWorld, indice)==1) {
        myWorld->plateau-> cases[indice].fourmi = fourmi;
    }
    //A SUIVRE... HAVE FUN
    if (estLibre(myWorld, indice)==0){
        printf (" la case est déja occupée par une fourmi, etes vous sur ?"); 
        //A CONTINUER...
    } 
    if (estLibre(myWorld, indice)==0 /*et qu'on est juste à cote*/){
        
    }
    if (estLibre(myWorld, indice)==-1) {
        printf ("Bravo MORRAY, tu veux pas aller sur la Lune tant que tu y es ?"); 
    }
}

/*LATER
void combatFourmi ( Fourmi * fourmiAttaquante , Fourmi * fourmi2,  Monde * myWorld){
   
   int scoreFourmiAttaquante = 0; 
   int scoreFourmi2 =0; 
   srand(time(NULL)); 
   
   if (fourmiAttaquante -> type == SOLDAT && fourmi2->type != SOLDAT){
      do {
          scoreFourmiAttaquante = (rand()%101)*3; 
          scoreFourmi2= rand()%101; 
          
        } while ((scoreFourmiAttaquante==50)&&(scoreFourmi2==50)); 
   }
    
    if (fourmiAttaquante.type != SOLDAT && fourmi2.type == SOLDAT){
        do {
          scoreFourmi2 = (rand()%101)*3; 
          scoreFourmiAttaquante= rand()%101; 
        } while ((scoreFourmi2==50) && (scoreFourmiAttaquante==50); 
    }
    
    if (fourmiAttaquante.type != SOLDAT && fourmi2.type != SOLDAT){
        do {
          scoreFourmi2 = rand()%101;
          scoreFourmiAttaquante= rand()%101; 
          
        } while (scoreFourmi2==50); 
    }
    
    
    if (scoreFourmiAttaquante > scoreFourmi2){
        printf (" la fourmi attaquante remporte le combat"); 
        plateau -> cases[fourmi2.position].fourmi= fourmiAttaquante; 
        supprimeFourmi (fourmi2, myWorld); 
    } 
    else {
        printf("c'est la fourmiAttaquant a perdu le combat"); 
        supprimeFourmi(fourmiAttaquante, myWorld); 
    }
          
}
*/

int chercheLibre(int centre, Monde* myWorld){
    
    int cote = myWorld->plateau->cote; //raccourci
    int rayon = 1;
    int haut, droite, bas, gauche;

    //if plateau rempli
    
    //on s'eloigne du centre (rayon augmente)
    for(rayon; rayon < cote; rayon++){
        
        //haut
        for(haut = centre - rayon*cote + rayon; haut > centre + rayon*cote - rayon; haut--){
            if(estLibre(myWorld, haut)) {
                //test
                creationFourmi(ROUGE, SOLDAT, myWorld, haut);
                return haut;
            }
        }
        
        //gauche
        for(gauche = centre - (rayon-1)*cote - rayon; gauche < centre + (rayon-1)*cote - rayon; gauche+ = cote){
            if(estLibre(myWorld, gauche)) {
                return gauche;
            }
        }
        
        //bas
        for(bas = centre + rayon*cote - rayon; bas < centre + rayon*cote + rayon; bas++){
            if(estLibre(myWorld, bas)) {
                return bas;
            }
        }
        
        //droite
        for(droite = centre + (rayon-1)*cote + rayon; droite > centre - (rayon-1)*cote + rayon; droite- = cote){
            if(estLibre(myWorld, droite)) {
                return droite;
            }
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
6. Free !!!
7. abs/or => indice

*/