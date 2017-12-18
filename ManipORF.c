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

void printORF(FILE *pF, tyORF *pORF, int compl_seq){
	/* écrire dans pF la seq de l'ORF pORF au format fasta
	 * 
	 * On commence par ouvrir le fichier pF en mode écriture
	 */
	//printf ("%s",pF);
	
	pF = fopen("ORF.fasta","a");

	if (pF == NULL){
		free(pF);
		exit(1);
	}
	/* écriture de la première ligne
	 * on suppose que int complementaire = 0 si brin direct et 1 si indirect
	 */
	switch (compl_seq){
		case(0) : fprintf(pF,"> %d-%d",pORF->debut,pORF->stop); break;	
		case(1) : fprintf(pF,"> c%d-%d",pORF->debut,pORF->stop); break;
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
	fprintf(pF,"\n");
	fclose(pF);
}

tyListeORFs* ajouterORF(tyListeORFs *pL, int iDebut, int stop, int start, tySeqADN *pS){
	/* Premier argument : liste a remplir 
	 * les autres arguments sont les composantes du type ORF a ajouter */
	
	tyORF *nouvORF; // initialisation de la nouvelle ORF
	tyListeORFs *pLnouv; /* initialisation du nouv element listeORF qui contiendra
	un pointeur vers le nouveau ORF crée a partir des arguments et un pointeur vers 
	le premier élément de la liste pL (ajout en début de liste)*/

	/* initialisation de pLnouv */
	pLnouv = malloc(sizeof(tyListeORFs));
	
	if (pLnouv == NULL){
		exit(1);
	}
	/* ------------ */
	/* Affecation des composantes du nouv ORF */
	nouvORF = newORF();
	nouvORF->debut = iDebut;
	nouvORF->stop = stop;
	nouvORF->start = start;
	nouvORF->pSeq = pS;
	
	
	pLnouv->pORF = nouvORF; // affectation composante pORF vers nouvORF
	pLnouv->pSuiv = pL; //affectation ORF suivante au premier element liste pL
	
	return pLnouv;
}

tyListeORFs* freeListeORFs(tyListeORFs *pL){
	tyListeORFs *tmp;
	for (tmp = pL; tmp->pSuiv != NULL; tmp=tmp->pSuiv){
		freeORF(tmp->pORF);
  		}
	return pL;
}

tyListeORFs* SupprimerORF(tyListeORFs *pL, tyListeORFs *pOrfASupprimer){
	tyListeORFs *tmp;
	
	for (tmp = pL; tmp->pSuiv != NULL ; tmp=tmp->pSuiv){
		if ( tmp->pSuiv == pOrfASupprimer->pSuiv ) {
			free(tmp->pSuiv);
		}

	}
	return pL;
}

void ecrireListeORF(tyListeORFs *pL, FILE *pF){
	tyListeORFs *tmp;
	
	pF = fopen("ORF.fasta","w");
	fclose(pF);
	
	for (tmp = pL; tmp->pSuiv != NULL ; tmp=tmp->pSuiv){
		
		
		printORF(pF, tmp->pORF, 0);
	
	}
}


