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
	int debutORF = pORF->debut, finORF = pORF->stop-1;
	int i;
	for (i=debutORF; i<finORF; i++){
		if ((i-debutORF)%70==0){
			fprintf(pF,"\n");
		}
		fprintf(pF,"%c",seqORF[i]);

	}
	fprintf(pF,"\n");

}

tyListeORFs* ajouterORF(tyListeORFs *pL, int iDebut, int stop, int start, tySeqADN *pS){
	/* Premier argument : liste a remplir
	 * les autres arguments sont les composantes du type ORF a ajouter */

	tyORF *nouvORF=NULL; // initialisation de la nouvelle ORF
	tyListeORFs *pLnouv=NULL; /* initialisation du nouv element listeORF qui contiendra
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
	nouvORF->GC = compteGC3en3(pS->seq, stop-iDebut);


	pLnouv->pORF = nouvORF; // affectation composante pORF vers nouvORF
	pLnouv->pSuiv = pL; //affectation ORF suivante au premier element liste pL
	return pLnouv;
}

tyListeORFs* freeListeORFs(tyListeORFs *pL){
	tyListeORFs *tmp=NULL;
	for (tmp = pL; tmp->pSuiv != NULL; tmp=tmp->pSuiv){
		freeORF(tmp->pORF);
  		}
	return pL;
}

tyListeORFs* SupprimerORF(tyListeORFs *pL, tyListeORFs *pOrfASupprimer){

	if (pL == NULL){
		return pL;
	}

	tyListeORFs *tmp=NULL;
	tyListeORFs *prec=NULL;


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


	tyListeORFs *tmp=NULL;
	tyListeORFs *prec=NULL;
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

tyListeORFs* FiltreNoStart (tyListeORFs *pL){

	/* Determiner quels sont les ORF de longuer < lgMin */
	tyListeORFs *sup, *prec, *n;

	/* Supprimer les ORFs start -1 du début */
	while (pL != NULL && pL->pORF->start == -1){
		sup = pL;
		pL= pL->pSuiv;
		free (sup);
	}
	/* Supprimer les ORFs start -1 suivants */
	if (pL != NULL){
		prec = pL;
		n = pL->pSuiv; //pointeur sur le suivant à suppr
		while (n != NULL){
			while (n!= NULL && n->pORF->start == -1){
				sup = n;
				n = n->pSuiv;
				prec->pSuiv = n; // liaison n-1 n+1
				free (sup);
			}
			if (n!=NULL){
				prec = n;
				n = n->pSuiv;
			}
		}
	}
	return pL;
}


void FiltreORFsLg (tyListeORFs *pL, int lgMin){

	/* Determiner quels sont les ORF de longuer < lgMin */
	tyListeORFs *tmp=NULL;
	tyListeORFs *prec=NULL;
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

void FiltreORFsCompoGC (tyListeORFs *pL){

	tyListeORFs *tmp=NULL;
	tyListeORFs *prec=NULL;
	int debut, stop;
	float propor_GC;
	float Chi2;
	if (pL == NULL){
		printf("erreur liste\n");
	}

	prec = pL;
	tmp = prec->pSuiv;

	while (tmp != NULL){

		debut = tmp->pORF->debut;
		stop = tmp->pORF->stop;

		propor_GC = GC (tmp->pORF->pSeq->seq,stop-debut);
		char* seq = tmp->pORF->pSeq->seq;
		Chi2 = calcChi2Conformite(&seq[debut], stop-debut, propor_GC);

		//  alpha = 0.05 ddl = 1; chi2 = 3.84

		if(Chi2 < 3.84){

			pL = SupprimerORF(pL, tmp);

		}
	prec = tmp;

	tmp = tmp->pSuiv;
	}


}

void ecrireListeORFtoCDS(tyListeORFs *pL, FILE *pF, int compl_seq){ // ajout argument int compl_seq


	tyListeORFs *tmp;
	tyListeORFs *prec;
	if (pL == NULL){
		printf("erreur liste\n");
	}

	prec = pL;
	tmp = prec->pSuiv;
	while (tmp != NULL){
		printCDS(pF, tmp->pORF, compl_seq);

	prec = tmp;
	tmp = tmp->pSuiv;
	}


}

void printCDS(FILE *pF, tyORF *pORF, int compl_seq){

	/* écriture de la première ligne
	 * on suppose que int complementaire = 0 si brin direct et 1 si indirect
	 */
	int taille = pORF->pSeq->lg;
	switch (compl_seq){
	   case(0) : fprintf(pF,"> %d-%d",pORF->debut,pORF->stop-1); break;
	   case(1) : fprintf(pF,"> c%d-%d",taille-(pORF->start+1),taille-(pORF->stop-1)); break;
	}

	/* Ecriture de l'ORF, il faut que chaque ligne fasse 80 caractères max */
	char *seqORF = pORF->pSeq->seq; // seq de l'ORF en brin direct
	int debutORF = pORF->start, finORF = pORF->stop-1;
	int i;
	for (i=debutORF; i<finORF; i++){
	   if ((i-debutORF)%70==0){
		   fprintf(pF,"\n");
	   }
	   fprintf(pF,"%c",seqORF[i]);

	}
	fprintf(pF,"\n");
}
