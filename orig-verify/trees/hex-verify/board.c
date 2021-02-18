#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bitset.h"


/* This is my own board stuff, but I should use the stuff from benzene */
/* I use the same board layout though */

#define MAX_BOARDSIZE 11

int NEdge,SEdge,EEdge,WEdge,Null;
char bittostr[MAX_BOARDSIZE*MAX_BOARDSIZE][8];
int nbs[MAX_BOARDSIZE*MAX_BOARDSIZE][6];

int sets[MAX_BOARDSIZE*MAX_BOARDSIZE];

int boardsize = 3;
BitSet_t board;

void label_to_BS(char *str, BitSet_t out)
{
}

int is_null(int a)
{
	return (a == Null) ? 1 : 0;
}

int label_to_bit(char *str)
{
	int ret,a;
	if (!strcmp(str, "#")) ret = Null;
	else if (!strcmp(str, "TR")) ret = NEdge;
	else if (!strcmp(str, "BL")) ret = SEdge;
	else if (!strcmp(str, "BR")) ret = EEdge;
	else if (!strcmp(str, "TL")) ret = WEdge; 
	else {
		if (sscanf(&str[1], "%d", &a) != 1 || a < 1 || a > boardsize || 
		    str[0] < 'a' || str[0] >= 'a' + boardsize) return -1;
		ret = (str[0]-'a')*boardsize + a-1;
	}
	return ret;
}

char *bit_to_label(int b)
{
	return bittostr[b];
}

void init_bittostr()
{
	int i,r,c;
	char str[8];
	for (i=0; i<boardsize*boardsize; i++) {
		r = i / boardsize;
		c = i % boardsize;
		bittostr[i][0] = 'a'+r;
		bittostr[i][1] = 0;
		sprintf(str, "%d", c+1);
		strcat(bittostr[i], str);
	}
	strcpy(bittostr[NEdge = i++], "TR");
	strcpy(bittostr[EEdge = i++], "BR");
	strcpy(bittostr[SEdge = i++], "BL");
	strcpy(bittostr[WEdge = i++], "TL");
	strcpy(bittostr[Null = i++], "#");
}


// FIXME: everything fine here with isomorphisms?
typedef enum {LEFT,UPL,UPR,RIGHT,DOWNR,DOWNL} move_t;
void init_neighbor()
{
	int i,r,c;
	for (r=i=0; r<boardsize; r++) for (c=0; c<boardsize; c++,i++) {
		nbs[i][UPL] = (r == 0) ? WEdge : i - boardsize;
		nbs[i][DOWNR] = (r == boardsize-1) ? EEdge : i+boardsize;
		nbs[i][LEFT] = (c == 0) ? SEdge : i - 1;
		nbs[i][RIGHT] = (c == boardsize-1) ? NEdge : i + 1;

		if (r == 0) {
			nbs[i][UPR] = WEdge;
		} else {
			nbs[i][UPR] = (c == boardsize-1) ? NEdge : i-boardsize+1;
		}
		
		if (r == boardsize-1) {
			nbs[i][DOWNL] = EEdge;
		} else {
			nbs[i][DOWNL] = (c == 0) ? SEdge : i+boardsize-1;
		}
	}
}

void init_board(int size)
{
	boardsize = size;
	init_bittostr();
	init_neighbor();
}


/* Union find stuff */
int getRoot(int x){
	if(sets[x] < 0) return x;
	return sets[x] = getRoot(sets[x]);
}

void Union(int a, int b){
	int ra = getRoot(a);
	int rb = getRoot(b);
	if(ra != rb){
		sets[ra] += sets[rb];
		sets[rb] = ra;
	}
}

void print_bitset_to_str(BitSet_t p, char *s)
{
	int i,j;
	sprintf(s, "(");
	for (i=j=0; i<boardsize*boardsize+4; i++) {
		if (BS__isBitSet(i,p)) {
			if (j) strcat(s, " ");
			strcat(s, bittostr[i]);
			j = 1;
		}
	}
	strcat(s,")");
}

void print_bitset_as_label(BitSet_t p)
{
	char str[2048];
	print_bitset_to_str(p, str);
	printf("%s", str);
}

void set_all_playable(BitSet_t b)
{
	BitSet_t z;
	BS__clear(z);
	BS__NOT(b, z);
	BS__resetBit(NEdge,b);
	BS__resetBit(SEdge,b);
	BS__resetBit(EEdge,b);
	BS__resetBit(WEdge,b);
}

void set_starting_board()
{
	BS__clear(board);
	memset(sets, -1, sizeof(sets));
}

void play_move(int m)
{
	int j;
	assert(m <= boardsize*boardsize+4);
	BS__setBit(m, board);
	if (m >= boardsize*boardsize) return;

	for (j=0; j<6; j++) {
		if (BS__isBitSet(nbs[m][j],board)) {
			Union(m, nbs[m][j]);
		}
	}
}

void play_moves(BitSet_t p)
{
	int i;

	// play edge moves first so that later moves will
	// connect up with them
	for (i=boardsize*boardsize; i<boardsize*boardsize+4; i++) {
		if (BS__isBitSet(i, p)) play_move(i);
	}

	// now play normal board moves
	for (i=0; i<boardsize*boardsize; i++) {
		if (BS__isBitSet(i, p)) play_move(i);
	}
}


/* determine if all set bits in 's' are connected */
int winning(BitSet_t s)
{
	int i,j;
	for (i=0, j=-1; i<boardsize*boardsize+4; i++) {
		if (!BS__isBitSet(i,s)) continue;
		if (j == -1) j = getRoot(i);
		else if (j != getRoot(i)) return 0;
	}
	return 1;
}

// are the two hexes adjacent?
int are_adjacent(int a, int b)
{
	int i;
	assert(0 <= a && a < boardsize*boardsize+4);
	assert(0 <= b && b < boardsize*boardsize+4);
	
	if (a >= boardsize*boardsize) {
		// FIXME: here we are assume all edges are adjacent to each other
		// is this ok?  (an edge is not adjacent to itself however)
		if (b >= boardsize*boardsize) return (a==b)?0:1;
		a ^= b ^= a ^= b; // swap them
	}
	for (i=0; i<6; i++) if (nbs[a][i] == b) return 1;
	return 0;
}

// assumes 
void init_mapping(int mapping[512])
{
	memset(mapping, -1, 512*sizeof(int));
	mapping[Null] = Null;
}

// determine if a 1-1 mapping is isomorphic 
int isomorphic_mapping(int *mapping)
{
	int i,j;

	for (i=0; i<boardsize*boardsize+4; i++) {
		if (mapping[i]==-1) continue;
		for (j=0; j<boardsize*boardsize+4; j++) {
			if (mapping[j]==-1) continue;

			/* printf("(%s,%s) (%s,%s)\n",  */
/* 			       bit_to_label(i),bit_to_label(j), */
/* 			       bit_to_label(mapping[i]), */
/* 			       bit_to_label(mapping[j])); */

			if (are_adjacent(i,j)!=are_adjacent(mapping[i],mapping[j])){
				return 0;
			}
		}
	}
	return 1;
}
