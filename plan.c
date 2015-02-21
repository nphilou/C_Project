int map(int abscisse, int ordonnee, int cote) {
    if (abscisse < 0 || abscisse >= cote || ordonnee < 0 || ordonnee >= cote){
        return -1;
    }
    return cote * ordonnee + abscisse;
}

int chercheOrdonnee(Monde *myWorld, int indice) {
    return indice / myWorld->plateau->cote;
}

int chercheAbscisse(Monde *myWorld, int indice) {
    return indice % myWorld->plateau->cote;
}