
#ifndef __MANIP_ORF__
#define __MANIP_ORF__

#include <stdlib.h>
#include <stdio.h>
#include "ManipSeqADN.h"

// Structure pour manipuler une ORF
typedef struct {
	int debut; /*indice de debut (apres le stop precedent)*/
	int stop; /*indice du stop*/
	int start; /*indice du start choisi*/
	tySeqADN *pSeq; /*Pointeur vers la sequence (le debut genome entier)*/
	float GC; /*% GC en 3e position*/
} tyORF;

// Structure pour manipuler une liste d'ORF
typedef struct _tyListeORFs{
	tyORF *pORF; // pointeur vers l'ORF
	struct _tyListeORFs *pSuiv; // pointeur vers l'ORF suivante (NULL si fin de liste)
} tyListeORFs;

void printORF(FILE *pF, tyORF *pORF, int complementaire);
tyORF* newORF();
tyORF* freeORF(tyORF *pO);


tyListeORFs* freeListeORFs(tyListeORFs *pL);
tyListeORFs* ajouterORF(tyListeORFs *pL, int iDebut, int stop, int start, tySeqADN *pS);
tyListeORFs* SupprimerORF(tyListeORFs *pL, tyListeORFs *pOrfASupprimer);
void ecrireListeORF(tyListeORFs *pL, FILE *pF);

#endif
