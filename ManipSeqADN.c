#include <stdio.h>
#include <stdlib.h>
#include "ManipSeqADN.h"
#include "ManipSeqSimple.c"


tySeqADN* newSeqADN(){
	
	/*
	 * initialisation du pointeur vers une variable de type tySeqADN
	 * à qui alloue de la mémoire de la taille de la structure en question
	*/
	tySeqADN *nouv = malloc(sizeof(tySeqADN));
	
	// Vérification de la valeur retournée par malloc
	
	if (nouv == NULL){
		exit(1);
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
		compl->seq[i] = Nt_Complementaire(nt);
	}
	return compl;
}

tySeqADN *readFasta(char *nomFi){
	//Ouverture du fichier
	FILE* pF = NULL;
	

	pF = fopen(nomFi,"r");

	if (pF == NULL){
		free(pF);
		exit(1);
	}
	// Allouer la séquence
	tySeqADN *seqL; 
	int lgMax;
	seqL = newSeqADN(); // ini nouv seq, lecture
	
	seqL->seq = malloc(sizeof(char)*SIZE_SEQ); //allocation provisoire pour la seq
	
	if (seqL->seq == NULL){
		exit(1);
	}
	lgMax = SIZE_SEQ;
	// Lecture de la première ligne
	char* ligne= malloc(sizeof(char)*lgMax);
	
	fgets(ligne,lgMax,pF);
	
	// Lecture des lignes suivantes
	int lg,lgSeq=0;
	
	while (fgets(ligne,lgMax,pF)!= NULL){
		lg = strlen(ligne);
		if(ligne[lg-1] == '\n'){ //supprimer les retours chariots de fin de ligne
			ligne[lg-1] = 0;
		}
		lgSeq += lg;
		
		if (lgSeq+ seqL->lg >= lgMax) { // si la longueur de la ligne + taille seq allouée  > longueur max def
			char *tmp;
			
			tmp = realloc(seqL->seq, lgMax+2000);
			if (tmp == NULL){
				free(tmp);
				free(seqL);
				exit(1);
			}
			seqL->seq = tmp;
		}
		
		strcat(seqL->seq, ligne);

	}
	
	// ajout de \0 à la fin
	strcat(seqL->seq, "\0");
	seqL->lg = lgSeq; // affectation de la longueur de la seq
	seqL->GC = GC(seqL->seq,lgSeq);
	fclose(pF);
	return seqL;
	
	
}




