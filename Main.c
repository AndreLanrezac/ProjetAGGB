#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "Main.h"
#include "codons.h"
#include "ManipSeqSimple.h"
#include "ManipSeqADN.h"
#include "ManipORF.h"
#include "DetectionORFs.h"



// gcc -Wall -o exe main.c DetectionORFs.c; ./exe test.fasta
// gcc -Wall -o exe main.c ManipSeqADN.c; ./exe test.fasta
// gcc -Wall -Wextra -Werror --std=c99  -o exe main.c ManipSeqADN.c; ./exe test.fasta



/************************************/
int main(int argc, char *argv[]){

    tySeqADN *pS=NULL, *pComp=NULL; //, *pS2;
    tyListeORFs *lesORFs=NULL, *lesORFsComp=NULL;// *pTmp;
    int lgMinORF=1000;
    char *nomFi=NULL;

    if(argc==1){
        fprintf(stderr, "USAGE: %s <fasta file>\n", argv[0]);
        exit(1);
    }
    nomFi=argv[1];


    /* Lecture fichier fasta -----------------------------------------*/

	pS=readFasta(nomFi);
	pComp=complementaire(pS);

    if (pS==NULL){
        fprintf(stderr, "Pas de sequence lue.\nArret...\n");
        exit(1);
    }
    /* ---------------------------------------------------------------*/


    /* Recherche des ORF ---------------------------------------------*/
    printf("Recherche ORFs ----------\n");
    lesORFs=findORF(pS); // Recherche des ORFs et affectation dans listesORF
    lesORFsComp = findORF(pComp);

    printf("Application filtres ----------\n");
    FiltreORFsCompoGC(lesORFs);
    FiltreORFsCompoGC(lesORFsComp);

    FiltreORFsLg(lesORFs,lgMinORF);
    FiltreORFsLg(lesORFsComp,lgMinORF);


    printf("Recherche des starts ----------\n");
    TrouveLesPremiersStarts(lesORFs); // Ajout composante start dans les ORFs
    TrouveLesPremiersStarts(lesORFsComp); // Ajout composante start dans les ORFs


    printf("Suppression ORFs sans start ----------\n");
    lesORFs = FiltreNoStart(lesORFs); // Enlève les ORFs qui n'ont pas de Start
    lesORFsComp = FiltreNoStart(lesORFsComp); // Enlève les ORFs qui n'ont pas de Start



    /* Utiliser la fonction FiltreNoStart pour la fonction ecrireListeORF ! */

	/* ======Fichier ORF.fasta ==============*/
	/*
    FILE *pF; // Fichier a remplir
    pF = fopen("ORF.fasta","w");
	if (pF == NULL){
		exit(1);
	}
    ecrireListeORF(lesORFs, pF); //Ecriture des ORFs

    fclose(pF);
    ====================================*/

    /* ========Fichier CDS.fasta ========= */

    FILE *pFcds=NULL; // Fichier a remplir
    pFcds = fopen("CDS.fasta","w");
	if (pFcds == NULL){
		exit(1);
	}
    printf("Ecriture dans fichier CDS.fasta ----------\n");
    ecrireListeORFtoCDS(lesORFs, pFcds,0); //Ecriture des ORFs
    ecrireListeORFtoCDS(lesORFsComp, pFcds,1);


    fclose(pFcds);
    printf ("Done \n");
    /*
    printf("Les Complémentaires\n");
    pComp=complementaire(pS); // Seq compl de pS dans pComp
    lesORFsComp=findORF(pComp); // Recherche des ORFs et affectation dans lesORFsComp
    ecrireListeORF(lesORFsComp, stdout); //Ecriture des ORFs dans la console
    */


    lesORFsComp=freeListeORFs(lesORFsComp);
    lesORFs=freeListeORFs(lesORFs);
    pComp=freeSeqADN(pComp);
    pS=freeSeqADN(pS);



    return 0;
}



/* Affichage longueur lesOFRS : nbr d'ORF

int i=0;
while (lesORFs->pSuiv != NULL){
    i+=1;
    printf("Debut : %d ;Start : %d;  Fin : %d\n",lesORFs->pORF->debut,lesORFs->pORF->start, lesORFs->pORF->stop);
    lesORFs = lesORFs->pSuiv;
}
printf("nombre : %d\n",i);


	* AfficheSeqBornes(pS->seq,5,17);
	 ------------------------------------*/
