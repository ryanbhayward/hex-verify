#include "bitset.h"
#include <stdio.h>
#include <string.h>

// print
// Prints out a hex representation of the bitset
void BS__print( BitSet_t a )
{
	int i;
	for (i=0; i<BITSETSIZE; i++)
		printf( "%.8x", a[i] );
}

void BS__printBinary( BitSet_t a )
{
	int i, j;
	for (i=0; i<BITSETSIZE; i++)
	{
		for (j=0; j<32; j++)
		{
			if ( a[i] & bitmasks[j] )
				printf( "1" );
			else
				printf( "0" );
		}
		printf( "\n" );
	}
}

/*
int main()
{
	BitSet_t mybs;

	BS__clear( mybs );
	BS__print( mybs );
	printf( "\n" );
	BS__printBinary( mybs );
	printf( "\n" );

	printf( "Blah %d, %d\n", BS__bitsetIndex(5), BS__subIndex(5) );

	BS__setBit( 0, mybs );
	BS__print( mybs );
	printf( "\n" );
	BS__printBinary( mybs );
	printf("\n" );

	return 1;
}
*/
