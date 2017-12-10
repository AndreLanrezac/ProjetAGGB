

#ifndef __MANIP_SEQ_ADN__
#define __MANIP_SEQ_ADN__


// Structure pour manipuler des séquences ADNo
typedef struct {
	char *seq; //sequence
	int lg; //longueur de la sequence 
	float GC; // composition en GC de la seq
} tySeqADN;


tySeqADN *readFasta(char *nomFi);
tySeqADN* complementaire(tySeqADN *pS);
tySeqADN* freeSeqADN(tySeqADN *pS);
tySeqADN* newSeqADN();



#endif
