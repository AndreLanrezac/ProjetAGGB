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
    
    tySeqADN *pS, *pComp;//, *pS2; Création d'un pointeur pS vers un objet de type tySeqADN
    tyListeORFs *lesORFs=NULL, *lesORFsComp=NULL;// *pTmp;
    /*int lgMinORF=100;*/
    char *nomFi;
    
/* TEST
    pS = newSeqADN(); //pS pointeur vers une nouvelle structure
    
    printf ("test seq : %s\n",pS->seq);
	printf ("test lg : %d\n",pS->lg);
    printf ("test GC : %f\n",pS->GC);


	int lg1 = 20 +1; //ne pas oublier le \0 à la fin d'une chaine de caractères
	char seq1[lg1]; 
	InitSeqAlea (seq1, lg1);
	pS = newSeqADN(); //pS pointeur vers une nouvelle structure
	pS->seq = seq1;
	pS->lg = lg1;

*/
    
    
    //	srand(time(NULL));
    
    if(argc==1){
        fprintf(stderr, "USAGE: %s <fasta file>\n", argv[0]);
        exit(1);
    }
    nomFi=argv[1];
    
	pS=readFasta(nomFi);
	pComp=complementaire(pS);
	
    if (pS==NULL){
        fprintf(stderr, "Pas de sequence lue.\nArret...\n");
        exit(1);
    }
	/*
    tyORF *testORF;
    testORF = newORF();
    testORF->debut = 251;
    testORF->stop = 450;
    testORF->start = 29;
    testORF->pSeq = pS;
    testORF->GC = GC(pS->seq,pS->lg);
    
    FILE* pF = NULL;
    printORF(pF, testORF, 1);
 */
 
    
    lesORFs=findORF(pS); // Recherche des ORFs et affectation dans listesORF
    
    /* Affichage longueur lesOFRS : nbr d'ORF 
    int i=0;
    while (lesORFs->pSuiv != NULL){
		i+=1;
		printf("Debut : %d ; Fin : %d\n",lesORFs->pORF->debut, lesORFs->pORF->stop);
		lesORFs = lesORFs->pSuiv;
	}
	printf("nombre : %d\n",i);
	 ------------------------------------*/
	
    //AfficheSeqBornes(pS->seq,5,17);
    
    FILE *pF; // Fichier a remplir
    pF = fopen("ORF.fasta","w"); // OUverture du fichier
	if (pF == NULL){
		exit(1);
	}
	
    ecrireListeORF(lesORFs, stdout); //Ecriture des ORFs
    fclose(pF);
    
    /*
    printf("Les Complémentaires\n");
    pComp=complementaire(pS); // Seq compl de pS dans pComp
    lesORFsComp=findORF(pComp); // Recherche des ORFs et affectation dans lesORFsComp
    ecrireListeORF(lesORFsComp, stdout); //Ecriture des ORFs dans la console
    */
    // lesORFsComp=freeListeORFs(lesORFsComp); 
    lesORFs=freeListeORFs(lesORFs);
    //pComp=freeSeqADN(pComp);
    pS=freeSeqADN(pS);
    
    
    return 0;
}




