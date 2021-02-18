#ifndef BITSET_H 
#define BITSET_H 

#include <string.h>

// Defines the number of ints to make the bitset.
#define BITSETSIZE 4

typedef unsigned int BitSet_t[BITSETSIZE];

// Precalculated bit masks so we don't have to calculate them each bitset operation we do
static unsigned int bitmasks[32] = { 1U, 2U, 4U, 8U, 16U, 32U, 64U, 128U, 256U, 512U, 1024U, 2048U, 4096U, 8192U, 16384U, 32768U, 65536U, 131072U, 262144U, 524288U, 1048576U, 2097152U, 4194304U, 8388608U, 16777216U, 33554432U, 67108864U, 134217728U, 268435456U, 536870912U, 1073741824U, 2147483648U
};

// bitsetIndex
// Returns the index into the BitSet_t type where you can find the index 'index'
#define BS__bitsetIndex(index) (index/32)

// subIndex
// Returns the index into the integer for the asked for bit
#define BS__subIndex(index) ( index - BS__bitsetIndex(index)*32 )

// isBitSet
// Returns TRUE if the xth bit is set in the bitset a, false otherwise
#define BS__isBitSet(x,a) ( ((a)[ BS__bitsetIndex(x) ] & bitmasks[ BS__subIndex(x) ]) != 0)

// setBit
// Sets the specified bit to 1.
#define BS__setBit(x, a) ( (a)[ BS__bitsetIndex(x) ] |= bitmasks[ BS__subIndex(x) ] )

// resetBit
// Sets the specified bit to 0
#define BS__resetBit(x, a) ( (a)[ BS__bitsetIndex(x) ] &= ~bitmasks[ BS__subIndex(x) ] )

// clear
// sets all bits to 0
static inline void BS__clear( BitSet_t a )
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		a[i] = 0;
}

// isEmpty
// Verifies that no bits are set
static inline int BS__isEmpty( BitSet_t b )
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		if ( b[i] != 0 )
			return 0;
	return 1;
}


// emptyIntersection
// Checks to see if the two bitsets have no bits in common
static inline int BS__emptyIntersection( BitSet_t a, BitSet_t b )
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		if ( (a[i] & b[i]) != 0 )
			return 0;
	return 1;
}

// emptyIntersection3
// Checks to see if the three bitsets have no bits in common
static inline int BS__emptyIntersection3( BitSet_t a, BitSet_t b, BitSet_t c )
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		if ( ((a[i] & b[i] & c[i]) != 0) )
			return 0;
	return 1;
}

// emptyIntersection4
// Checks to see if the four bitsets have no bits in common
static inline int BS__emptyIntersection4( BitSet_t a, BitSet_t b, BitSet_t c, BitSet_t d )
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		if ( ((a[i] & b[i] & c[i] & d[i]) != 0) )
			return 0;
	return 1;
}

// emptyIntersection5// Checks to see if the five bitsets have no bits in common
static inline int BS__emptyIntersection5( BitSet_t a, BitSet_t b, BitSet_t c, BitSet_t d, BitSet_t e )
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		if ( ((a[i] & b[i] & c[i] & d[i] & e[i]) != 0) )
			return 0;
	return 1;
}

// isEqual
// Checks to see if the two bitsets are the same
static inline int BS__isEqual( BitSet_t a, BitSet_t b)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		if ( a[i] != b[i] )
			return 0;
	return 1;
}

// AND
// Performs boolean AND on two bitsets, and stores the result into a third.
static inline void BS__AND(BitSet_t c, BitSet_t a, BitSet_t b)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		c[i] = a[i] & b[i];
}

// AND3
// Performs boolean AND on three bitsets, and stores the result into a fourth.
static inline void BS__AND3(BitSet_t d, BitSet_t a, BitSet_t b, BitSet_t c)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		d[i] = a[i] & b[i] & c[i];
}

// AND4
// Performs boolean AND on four bitsets, and stores the result into a fifth.
static inline void BS__AND4(BitSet_t e, BitSet_t a, BitSet_t b, BitSet_t c, BitSet_t d)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		e[i] = a[i] & b[i] & c[i] & d[i];
}

// AND5
// Performs boolean AND on five bitsets, and stores the result into a sixth.
static inline void BS__AND5(BitSet_t f, BitSet_t a, BitSet_t b, BitSet_t c, BitSet_t d, BitSet_t e)
{
	int i;

	BitSet_t bs;

	for (i=0; i<BITSETSIZE; i++)
		f[i] = a[i] & b[i] & c[i] & d[i] & e[i];

	//XXX: random insertion of using the bit masks array
	BS__setBit( 1, bs );
}

// XOR
// Performs boolean XOR on two bitsets, and stores the result into a third.
static inline void BS__XOR(BitSet_t c, BitSet_t a, BitSet_t b)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		c[i] = a[i] ^ b[i];
}

// OR
// Performs boolean OR on two bitsets, and stores the result into a third.
static inline void BS__OR(BitSet_t c, BitSet_t a, BitSet_t b)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		c[i] = a[i] | b[i];
}

// OR3
// Performs boolean OR on three bitsets, and stores the result into a fourth.
static inline void BS__OR3(BitSet_t d, BitSet_t a, BitSet_t b, BitSet_t c)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		d[i] = a[i] | b[i] | c[i];
}

// OR4
// Performs boolean OR on four bitsets, and stores the result into a fifth.
static inline void BS__OR4(BitSet_t e, BitSet_t a, BitSet_t b, BitSet_t c, BitSet_t d)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		e[i] = a[i] | b[i] | c[i] | d[i];
}

// OR5
// Performs boolean OR on five bitsets, and stores the result into a sixth.
static inline void BS__OR5(BitSet_t f, BitSet_t a, BitSet_t b, BitSet_t c, BitSet_t d, BitSet_t e)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		f[i] = a[i] | b[i] | c[i] | d[i] | e[i];
}

// NOT
// Inverts a bitset and stores the results into another
static inline void BS__NOT(BitSet_t c, BitSet_t a)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		c[i] = ~a[i];
}

// LAND
// Performs logical AND; I think this is the equivalent of emptyIntersection
static inline int BS__LAND(BitSet_t a, BitSet_t b)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		if ( a[i] & b[i] )
			return 1;
	return 0;
}

// copy
// Makes a copy of a bitset
static inline void BS__copy(BitSet_t a, BitSet_t b)
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		a[i] = b[i];
}

// compare
// Compares two bitsets.  Any arbitrary method will do.
static inline int BS__compare(BitSet_t a, BitSet_t b)
{
  int i;
  for(i=0; i < BITSETSIZE; i++)
    {
      if (a[i] > b[i])
	return 1;
      if (a[i] < b[i])
	return -1;
    }
  return 0;
}

// print
// Prints out a hex representation of the bitset
void BS__print( BitSet_t a );

// print
// Prints out a  representation of the bitset
void BS__printBinary( BitSet_t a );

// subset
// is the first a subset of the second?
static inline int BS__isSubset(BitSet_t a, BitSet_t b)
{
	int i, j;
	for (i=0; i<BITSETSIZE; i++) {
		for (j=0; j<32; j++) {
			if ((a[i] & bitmasks[j]) && !(b[i] & bitmasks[j])) {
				//BS__printBinary(a);
				//BS__printBinary(b);
				return 0;
			}
		}
	}
	return 1;
}


#endif
