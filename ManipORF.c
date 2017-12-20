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
	
	
	/* écriture de la première ligne
	 * on suppose que int complementaire = 0 si brin direct et 1 si indirect
	 */
	 
	
	switch (compl_seq){
		case(0) : fprintf(pF,"> %d-%d",pORF->debut,pORF->stop-1); break;	
		case(1) : fprintf(pF,"> c%d-%d",pORF->debut,pORF->stop-1); break;
	}

	/* Ecriture de l'ORF, il faut que chaque ligne fasse 80 caractères max */
	char *seqORF = pORF->pSeq->seq; // seq de l'ORF en brin direct
	int debutORF = pORF->debut-1, finORF = pORF->stop-1;
	int i;
	for (i=debutORF; i<finORF; i++){
		if ((i-debutORF)%80 != 0){
				fprintf(pF,"%c",seqORF[i]);
		}
		else{ fprintf(pF,"\n"); };
		//printf("indice : %d\n",i);
		
	}
	fprintf(pF,"\n");
	
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
	tyListeORFs *prec;
	
	if (pL == NULL){
		return pL;
	}
	prec = pL; // premier element
	tmp = prec->pSuiv; // prec element precedent et tmp element suivant
	
	while (tmp != NULL){
		if (tmp == pOrfASupprimer){
			prec->pSuiv = tmp->pSuiv; //fusion n-1 et n+1 avant suppression de n
			
			free (tmp);
			
			return pL; // on peut retourner direct la liste quand on a supprime
		}
	/* iteration +1 chaine  */
	prec = tmp; 
	tmp = tmp->pSuiv;
	}
	return pL;

}

void ecrireListeORF(tyListeORFs *pL, FILE *pF){
	
	
	tyListeORFs *tmp;
	tyListeORFs *prec;
	if (pL == NULL){
		printf("erreur liste\n");
	}
	
	prec = pL;
	tmp = prec->pSuiv;
	
	while (tmp != NULL){
		
		printORF(pF, tmp->pORF, 0);

		
	prec = tmp;
	
	tmp = tmp->pSuiv;
	}
	
}

void FiltreORFsLg (tyListeORFs *pL, int lgMin){
	
	/* Determiner quels sont les ORF de longuer < lgMin */
	tyListeORFs *tmp;
	tyListeORFs *prec;
	int debut, stop;
	if (pL == NULL){
		printf("erreur liste\n");
	}
	
	prec = pL;
	tmp = prec->pSuiv;

	while (tmp != NULL){
		
		debut = tmp->pORF->debut;
		stop = tmp->pORF->stop;

		if (stop-debut <= lgMin){
			
			pL = SupprimerORF(pL, tmp);
		}
	prec = tmp;
	
	tmp = tmp->pSuiv;
	}
	
	
}
