

#ifndef __MANIP_SEQ_ADN__
#define __MANIP_SEQ_ADN__
#define SIZE_SEQ 2000


// Structure pour manipuler des séquences ADN.
typedef struct {
	/* typedef indique qu'un alias de structure va être crée
	pour définir une nouvelle variable de type tySeqADN tel que newSeqADN,
	* on aura plus besoin décrire "struc" avant le nom de la variable
	*/
	char *seq; //sequence
	int lg; //longueur de la sequence 
	float GC; // composition en GC de la seq
} tySeqADN;

// Pointeurs sur des structures
tySeqADN *readFasta(char *nomFi);
tySeqADN* complementaire(tySeqADN *pS);
tySeqADN* freeSeqADN(tySeqADN *pS);
tySeqADN* newSeqADN(); 



#endif
