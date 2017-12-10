/*
 * ManipSeqSimple.c
 * 
 * 2017 André Lanrezac <andre@Andre-Lanrezac.local>
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



// Affiche la chaine de caractères seq de longueur lg
void AfficheSeq(char seq[], int lg){
	int i;
	for (i=0; i<lg; i++)
	{
		printf("%c", seq[i]);
		
	}
	printf("\n");

}


// Remplie la chaine de caractère seq de lg nucléotides tirés aléatoirement
void InitSeqAlea(char seq[], int lg){
	int i;
	char bases[5] = "ATGC\0"; 
	srand(time(NULL));
	
	for (i=0; i<lg; i++)
	{
		seq[i] = bases[rand()%3];
	}
	seq[-1] = '\0';
}


// Retourne la proportion en GC dans la séquence seq de longeur lg
float GC(char seq[], int lg){
	float GC=0;
	int i;
	
	for (i=0; i<lg; i++)
	{
		if (seq[i] == 'G' || seq[i] == 'C' ) // si une base de la seq est un G ou C
		{
			GC += 1;
		}
	}
	return GC/lg;
}

// retourne 1 si codon start ; retourne 0 si codon stop
// *seq -> pointeur de la première base du codon
int estStart(char *seq){
	char codon[4];
	
	memcpy(codon, seq, 3);
	codon[3] = '\0';

	if (strcmp(codon, "ATG") == 0) // retourne 0 si les chaines sont identiques
	{
		return 1;
	}
	else { return 0;}
	
}

int estStop(char *seq){
	
	char codon[4];
	
	memcpy(codon, seq, 3);
	codon[3] = '\0';

	if ( strcmp(codon, "TAA")== 0 \
	  || strcmp(codon, "TAG")== 0  \
	  || strcmp(codon, "TGA")== 0) // retourne 0 si les chaines sont identiques
	{
		return 1;
	}
	else { return 0;}

}


int main ()
{
	int lg = 20 +1; //ne pas oublier le \0 à la fin d'une chaine de caractères
	char seq[lg]; 
	float propor_GC;
	
	InitSeqAlea (seq, lg);
	
	AfficheSeq(seq,lg);
	
	propor_GC = GC (seq,lg);
	printf("Proportion GC : %f\n",propor_GC);
	
	printf ("%d\n", estStop(&seq[0]));
	
	return 0;
}



/*

char Nt_Complementaire(char nt);

int compteGC3en3(char *seq, int lgSeq);
float calcChi2Conformite(char *seq, int lg, float GCGlobal );
*/
