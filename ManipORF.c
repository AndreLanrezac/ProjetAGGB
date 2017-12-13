#include <stdio.h>
#include <stdlib.h>
#include "ManipORF.h"



tyORF* newORF(){
	
	/*
	 * initialisation du pointeur vers une variable de type tyORF
	 * à qui alloue de la mémoire de la taille de la structure en question
	*/
	
	tyORF *nouv = malloc(sizeof(tyORF));
	
	// Vérification de la valeur retournée par malloc
	
	if (nouv == NULL){
		exit(1);
	}
	// intialisation des composantes
	nouv->debut = 0; // équivalent à (*nouv).debut = NULL
	nouv->stop = 0;
	nouv->start = 0;
	nouv->pSeq = NULL;
	nouv->GC = 0.0;
	
	return nouv; // return du pointeur de la nouvelle structure alloué

}

tyORF* freeORF(tyORF *pO){
	
	free(pO);
	return pO;
}

