
#ifndef __DETECTION_ORF__
#define __DETECTION_ORF__

#include "ManipORF.h" // def tyListeORFs

tyListeORFs *findORF(tySeqADN *pS);


void TrouveLesPremiersStarts(tyListeORFs *lesORF);

void ChangeLesStarts(tyListeORFs *lesORF);

#endif
