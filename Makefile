
# Makefile 

CC=gcc

GCC_FLAGS = -Wall -g

SRC=DetectionORFs.c  ManipSeqSimple.c ManipSeqADN.c ManipORF.c Main.c
OBJ= $(SRC:.c=.o)
HDR= $(SRC:.c=.h) codons.h

PROG=Detect_ORF

#Les programmes
all:  $(PROG)

#Compilation des fichiers .c
%.o	: %.c
	$(CC) $(GCC_FLAGS) -o $@ -c $^


#Compilation des programmes
Detect_ORF: $(HDR) $(OBJ)  main.o
	$(CC) $(GCC_FLAGS) -o Detect_ORF $(OBJ)
	

clean	:
	rm -f *.o $(PROG)
