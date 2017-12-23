#!/bin/bash

if [ $# -le 1 ]; then
	echo "Not enough arguments: "$#
	echo "USAGE: "$0" <your ORFs in fasta format> <reference fasta file>"
	exit 1
fi

fiORF=$1
fiRef=$2
echo $fiORF
grep ">" ${fiORF}  |cut -f 2 -d " " > ${fiORF}_$$
grep ">" ${fiRef} | cut -f 5 -d "|" | cut -f 1 -d " " |sed 's/://' > ${fiRef}_$$

sort ${fiORF}_$$ > $$
mv -f $$ ${fiORF}_$$
sort ${fiRef}_$$ > $$
mv -f $$ ${fiRef}_$$

join ${fiORF}_$$ ${fiRef}_$$ > $$
nbORF_OK=`wc -l $$ |awk '{print $1}'`
echo "ORF trouvées dans les deux fichiers :" 
cat $$

join -v 1 ${fiORF}_$$ ${fiRef}_$$ > $$
nbORF=`wc -l $$ |awk '{print $1}'`
echo "ORF uniquement dans votre fichiers :" 
cat $$

join -v 2 ${fiORF}_$$ ${fiRef}_$$ > $$
nbORF_REF=`wc -l $$ |awk '{print $1}'`
echo "ORF uniquement dans le fichiers de reference:" 
cat $$
declare v=0.0
(( v = nbORF_OK + nbORF ))
(( d = nbORF_OK *100 / v ))
(( v = nbORF_OK + nbORF_REF ))
(( e = nbORF_OK *100 / v ))

echo $nbORF_OK" orf communes, "$nbORF_REF" orf non trouvees, "$nbORF" orf incorrectes"
echo "soit "$d"% d'orf correctes parmi les prédites et "$e"% d'orf vraies trouvées"
rm -f ${fiORF}_$$ ${fiRef}_$$ $$
#for i in `cat fiORF_$$`; do echo $i; grep ":"$i"-" ${fiRef}_$$; done
