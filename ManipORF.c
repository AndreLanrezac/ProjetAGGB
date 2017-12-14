#include <stdio.h>
#include <stdlib.h>
#include "ManipORF.h"
#include "ManipSeqADN.c"


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

void printORF(FILE *pF, tyORF *pORF, int compl_seq){
	/* écrire dans pF la seq de l'ORF pORF au format fasta
	 * 
	 * On commence par ouvrir le fichier pF en mode écriture
	 */
	pF = fopen("ORF.fasta","w");

	if (pF == NULL){
		free(pF);
		exit(1);
	}
	/* écriture de la première ligne
	 * on suppose que int complementaire = 0 si brin direct et 1 si indirect
	 */
	switch (compl_seq){
		case(0) : fprintf(pF,"> %d-%d\n",pORF->debut,pORF->stop); break;	
		case(1) : fprintf(pF,"> c%d-%d\n",pORF->debut,pORF->stop); break;
	}

	/* Ecriture de l'ORF, il faut que chaque ligne fasse 70 caractères max */
	char *seqORF = pORF->pSeq->seq; // seq de l'ORF en brin direct
	char *seqORFcompl = complementaire(pORF->pSeq)->seq; // seq de l'ORF en brin indirect
	int debutORF = pORF->debut-1, finORF = pORF->stop-1;
	int i;
	for (i=debutORF; i<finORF; i++){
		if ((i-debutORF)%70 != 0){
			switch (compl_seq){
				case(0) : fprintf(pF,"%c",seqORF[i]); break;
				case(1) : fprintf(pF,"%c",seqORFcompl[i]); break;
			}
		}
		else{ fprintf(pF,"\n"); };
		
	}
	

	
	fclose(pF);
}
