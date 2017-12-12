#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DetectionORFs.h"
#include "ManipSeqADN.h"
#include "ManipSeqSimple.h"
#include "ManipORF.h"
#include "Main.h"
#include "codons.h"


/************************************/
int main(int argc, char *argv[]){
    
    tySeqADN *pS, *pComp;//, *pS2; Création d'un pointeur pS vers un objet de type tySeqADN
    tyListeORFs *lesORFs=NULL, *lesORFsComp=NULL, *pTmp;
    /*int lgMinORF=100;*/
    char *nomFi;
    
    
    // pS = newSeqADN(); //pS pointeur vers une nouvelle structure
    

    
    //	srand(time(NULL));
    
    if(argc==1){
        fprintf(stderr, "USAGE: %s <fasta file>\n", argv[0]);
        exit(1);
    }
    nomFi=argv[1];
    
   /* pS=readFasta(nomFi);
    if (pS==NULL){
        fprintf(stderr, "Pas de sequence lue.\nArret...\n");
        exit(1);
    }
    
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




