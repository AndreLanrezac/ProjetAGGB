#include <stdio.h>
#include <stdlib.h>
#include "ManipSeqADN.h"


/*
* Fonction qui alloue de la mémoire pour un élément de type tySeqADN
* 	char *seq  -> NULL		int lg -> 0		float GC -> 0
* Initialisation d'une strucure, on met en général les variables à 0,
* les pointeurs à NULL par convention. 
* 
* renvoie des pointeurs indiquants l'adresse que l'OS a réservé pour les
* composantes de la structure de type tySeqADN.
*/


tySeqADN* newSeqADN(){
	
	tySeqADN *nouv = malloc(sizeof(tySeqADN));

	nouv->seq = NULL; // équivalent à (*nouv).seq = NULL
	nouv->lg = 0;
	nouv->GC = 0.0;

	return nouv;
	
}


