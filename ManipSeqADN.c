#include <stdio.h>
#include <stdlib.h>
#include "ManipSeqSimple.c"
#include "ManipSeqADN.h"


tySeqADN* newSeqADN(){
	
	/*
	 * initialisation du pointeur vers une variable de type tySeqADN
	 * à qui alloue de la mémoire de la taille de la structure en question
	*/
	tySeqADN *nouv = malloc(sizeof(tySeqADN));
	
	// Vérification de la valeur retournée par malloc
	
	if (nouv == NULL){
		exit(0);
	}

	// intialisation des composantes
	nouv->seq = NULL; // équivalent à (*nouv).seq = NULL
	nouv->lg = 0;
	nouv->GC = 0.0;

	return nouv; // return du pointeur de la nouvelle structure alloué
	
}


tySeqADN* freeSeqADN(tySeqADN *pS){
	
	free(pS);
	return pS;
}


tySeqADN* complementaire(tySeqADN *pS){
	tySeqADN *compl; //initialisation nouv pointeur vers var type tySeqADN
	compl = newSeqADN();  //allocation espace et initialisation des champs
	
	compl->lg = pS->lg;
	compl->seq = malloc(sizeof(char)*pS->lg);
	int i;
	char nt;
	for (i=0; i<pS->lg; i++){
		nt = pS->seq[i];
		printf("print : %c\n",nt);
		compl->seq[i] = Nt_Complementaire(nt);
	}
	return compl;
}

