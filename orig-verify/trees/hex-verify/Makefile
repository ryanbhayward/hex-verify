SHELL = /bin/sh

CC=gcc
LEX=flex
YACC=bison      # NOTE - when using yacc, remove -o y.tab.c from YFLAGS

CFLAGS=-Wall -O2
GFLAGS=-man -h
LIBFLAGS= -lfl
YFLAGS=-d -t -o y.tab.c

CSRCS = verifier.c bitset.c board.c pattern.c
LSRCS = lex.l
LOBJS = lex.c
YSRCS = parser.y
YOBJS = parser.c y.tab.h
SRCS  = ${CSRCS} ${LSRCS} ${YSRCS}
OBJS  = verifier.o parser.o lex.o board.o pattern.o bitset.o
PROG  = hex

# Main rules.
default: all

hex:	${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@ ${LIBFLAGS}

# make the parser
parser.o : parser.c verifier.h types.h bitset.o

# make the lexer
lex.o : y.tab.h lex.l verifier.h
	flex -t lex.l > lex.c
	${CC} ${CFLAGS} lex.c -c 

verifier.o: verifier.h types.h verifier.c bitset.o
pattern.o: pattern.c pattern.h types.h
board.o: board.h board.c bitset.o types.h
bitset.o: bitset.h bitset.c


clean:
	rm -f core ${YOBJS} ${LOBJS} ${COBJS} ${OBJS} ${WASTE}

all: ${PROG}
