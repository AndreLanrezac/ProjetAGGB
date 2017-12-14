#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DetectionORFs.h"
#include "ManipSeqADN.h"
#include "ManipSeqSimple.h"
#include "ManipORF.h"
#include "Main.h"
#include "codons.h"

// gcc -Wall -o exe main.c ManipSeqADN.c; ./exe test.fasta 
// gcc -Wall -Wextra -Werror --std=c99  -o exe main.c ManipSeqADN.c; ./exe test.fasta
    


/************************************/
int main(int argc, char *argv[]){
    
    tySeqADN *pS; //*pComp;//, *pS2; Création d'un pointeur pS vers un objet de type tySeqADN
    //tyListeORFs *lesORFs=NULL, *lesORFsComp=NULL, *pTmp;
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
	//if (seq1[lg] == "\0"){ printf("OK\n"); };
    complementaire(pS);
    
    FIN TEST */
    
    
    //	srand(time(NULL));
    
    if(argc==1){
        fprintf(stderr, "USAGE: %s <fasta file>\n", argv[0]);
        exit(1);
    }
    nomFi=argv[1];
    
	pS=readFasta(nomFi);
	
    if (pS==NULL){
        fprintf(stderr, "Pas de sequence lue.\nArret...\n");
        exit(1);
    }
    
    tyORF *testORF;
    
    testORF = newORF();
    testORF->debut = 251;
    testORF->stop = 450;
    testORF->start = 29;
    testORF->pSeq = pS;
    testORF->GC = GC(pS->seq,pS->lg);
    
    FILE* pF = NULL;
    printORF(pF, testORF, 0);
    
    /*
    lesORFs=findORF(pS);
    ecrireListeORF(lesORFs, stdout);

    printf("Les Complémentaires\n");
   pComp=complementaire(pS);
    lesORFsComp=findORF(pComp);
    ecrireListeORF(lesORFsComp, stdout);

    lesORFsComp=freeListeORFs(lesORFsComp);
    lesORFs=freeListeORFs(lesORFs);
    pComp=freeSeqADN(pComp);
    pS=freeSeqADN(pS);
    */
    return 0;
}




