
#ifndef __DETECTION_ORF__
#define __DETECTION_ORF__

#include "ManipSeqADN.h"
#include "ManipORF.h"

tyListeORFs *findORF(tySeqADN *pS);


void TrouveLesPremiersStarts(tyListeORFs *lesORF);

void ChangeLesStarts(tyListeORFs *lesORF);

#endif
