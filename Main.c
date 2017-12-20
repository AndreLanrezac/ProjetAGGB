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
    
    tySeqADN *pS, *pComp; //, *pS2; Création d'un pointeur pS vers un objet de type tySeqADN
    tyListeORFs *lesORFs=NULL; //*lesORFsComp=NULL;// *pTmp;
    /*int lgMinORF=100;*/
    char *nomFi;
    
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
    
    lesORFs=findORF(pS); // Recherche des ORFs et affectation dans listesORF
    
    /* Affichage longueur lesOFRS : nbr d'ORF 
    int i=0;
    while (lesORFs->pSuiv != NULL){
		i+=1;
		printf("Debut : %d ; Fin : %d\n",lesORFs->pORF->debut, lesORFs->pORF->stop);
		lesORFs = lesORFs->pSuiv;
	}
	printf("nombre : %d\n",i);
	* AfficheSeqBornes(pS->seq,5,17);
	 ------------------------------------*/
	
	
    /* Ouverture du fichier */
    FILE *pF; // Fichier a remplir
    pF = fopen("ORF.fasta","w"); 
	if (pF == NULL){
		exit(1);
	}
	
	TrouveLesPremiersStarts(lesORFs); // Ajout composante start dans les ORFs
	
	
	
	
	int lg = 30; // on pose longueur min ORF
	
	
	
	FiltreORFsLg(lesORFs,lg);
	
    ecrireListeORF(lesORFs, pF); //Ecriture des ORFs
    
    
    fclose(pF);

   
    
    
    //AfficheSeqBornes(pS->seq,780,986);
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




