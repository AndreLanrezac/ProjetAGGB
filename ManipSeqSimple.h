
#ifndef __MANIP_SEQ_SIMPLE__
#define __MANIP_SEQ_SIMPLE__


void AfficheSeq(char seq[], int lg);

void AfficheSeqBornes(char seq[], int debut, int fin);

void InitSeqAlea(char seq[], int lg);
float GC(char seq[], int lg);
char Nt_Complementaire(char nt);
int estStart(char *seq);
int estStop(char *seq);

int compteGC3en3(char *seq, int lgSeq);
float calcChi2Conformite(char *seq, int lg, float GCGlobal );


#endif
