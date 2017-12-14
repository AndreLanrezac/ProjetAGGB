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


char *strrev(char *str){
    char c, *front, *back;

    if(!str || !*str)
        return str;
    for(front=str,back=str+strlen(str)-1;front < back;front++,back--){
        c=*front;*front=*back;*back=c;
    }
    return str;
}

tySeqADN* complementaire(tySeqADN *pS){
	tySeqADN *complDirect, *complIndirect; //initialisation nouv pointeur vers var type tySeqADN
	
	complDirect = newSeqADN();  //allocation espace et initialisation des champs

	complIndirect = newSeqADN();  //allocation espace et initialisation des champs
	complIndirect->lg = pS->lg;
	
	complDirect->seq = malloc(sizeof(char)*pS->lg);
	complIndirect->seq = malloc(sizeof(char)*pS->lg);
	
	int i;
	char nt;
	for (i=0; i<pS->lg; i++){
		nt = pS->seq[i];
		complDirect->seq[i] = Nt_Complementaire(nt);
		
	}
	complIndirect->seq = strrev(complDirect->seq);
	freeSeqADN(complDirect);
	return complIndirect;
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
		strtok(ligne,"\n"); // suppression \n
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




