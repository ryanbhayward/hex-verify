%{
#include <string.h>
#include <stdlib.h>
#include "verifier.h"

int yylex();
int yyerror(char *s);

extern char *yytext;

// pre: undefined relations should be set to -1;
//      mapping should be able to hold 512 entries
// post: returns 1 if still 1-1, otherwise 0;
int update_mapping(int *mapping, hlist_t *a, hlist_t *b)
{
	int i,j;
	if (a->n != b->n) return 0;
	for (i=0; i<a->n; i++) {
		if (mapping[a->h[i]] == -1) {
			// make sure nothing already maps to it
			for (j=0; j<512; j++) { 
				if (mapping[j] == b->h[i]) {
					error("mapping not 1-1: cannot map %s onto %s since %s already maps to %s",
					   bit_to_label(a->h[i]), bit_to_label(b->h[i]), 
					   bit_to_label(j), bit_to_label(b->h[i]));
					return 0;
				}
			}
			mapping[a->h[i]] = b->h[i];
		} else if (mapping[a->h[i]] != b->h[i]) {
			error("mapping not 1-1: %s already maps to %s",
			      bit_to_label(a->h[i]), bit_to_label(mapping[a->h[i]]));
			return 0;
		}
	}
	return 1;
}

%}

%union
{
	int ival;
	char str[64];
	node_t *node;
	BitSet_t bs;
	hlist_t hlist;
	pattern_t *pattern;
}

%token  ID DIGIT BOARDSIZE ALL

%type <ival> DIGIT
%type <str> ID ALL pat_start name
%type <node> tree_1ps tree_1ps_list tree_2ps tree_2ps_list pattern_call
%type <hlist> hexlist hexes hexlistlist hexlist_a pat_connect pat_empty pat_play 
%type <pattern> pattern pattern_list

%%

input_file    : board_info pattern_list 
{
	pattern_summary();
}
              ;

board_info    : '(' BOARDSIZE DIGIT ')'
{
	if ($3 <= 0 || $3 >= 19) shutdown ("bad board size: %d\n", $3);
	printf("board size: %d\n\n", $3);
	init_board($3);   
}
               | '(' error ')'
{
	printf("error in board size.\n");
}
;


//
// Pattern definition
//
pattern_list  : pattern
              | pattern_list pattern
              ;

pattern       : '(' pat_start pat_connect pat_empty pat_play tree_2ps ')'
{
	hlist_t *hl;
	pattern_t *ret = getpattern();
	strcpy(ret->name, $2);
	ret->valid = 1;

	ret->connect = $3;
	ret->empty = $4;
	ret->played = $5;
	ret->proof = $6;
	$$ = ret;

	pattern_print_info(ret);

	if ((ret->valid = verify_pattern(ret))) {
		printf("VALID pattern.\n");
	} else {
		printf("INVALID pattern.\n");
	}

	addpattern(ret);
	if (pstricks_on && ret->valid) pattern_pstricks(ret);

	printf("\n");	
}
| '(' pat_start pat_connect pat_empty pat_play error ')'
{
	pattern_t *ret = getpattern();	
	error("Badly formed proof");
	ret->valid = 0;
	$$ = ret;
}
| '(' error ')'
{
	pattern_t *ret = getpattern();
	error("Badly formed pattern.");
	ret->valid = 0;
	$$ = ret;
}
;

pat_start : ID
{
	printf("%s\n", $1);
	strcpy($$,$1);
}
;

pat_connect: hexlistlist
{
	$$ = $1;
}
;

pat_empty  : hexlist
{
	$$ = $1;
}
;

pat_play   : hexlist
{
	$$ = $1;
}
;

hexlistlist : '(' hexlist_a ')'
{
	$$ = $2;
}

hexlist_a : hexlist
{
	$$ = $1;

}
| hexlist_a hexlist
{
	hlist_t *c, *h = malloc(sizeof(hlist_t));
	*h = $2;
	$$ = $1;
	for (c=&$$; c->next; c=c->next);
	c->next = h;
}
;

hexlist      : '(' ')'
{
	$$.n = 0;
	$$.h = NULL;
	$$.next = NULL;
	BS__clear($$.hunion);
}
             | '(' hexes ')'
{
	$$ = $2;
}
             | '(' error ')'
{
	error("error in list");
	$$.n = 0;
	$$.h = NULL;
	$$.next = NULL;
	BS__clear($$.hunion);
}
;

hexes        : ID
{
	int bit = label_to_bit($1);
	if (bit == -1) error ("invalid hex");
	$$.n = 1;
	$$.h = addhex(bit);
	$$.next = NULL;
	BS__clear($$.hunion);
	BS__setBit(bit, $$.hunion);
}
             | hexes ID
{
	int bit = label_to_bit($2);
	if (bit == -1) error("invalid hex");
	else {
		$$.n++;
		addhex(bit);
		if (BS__isBitSet(bit, $$.hunion)) 
			warning("hex (%s) duplicated in list", bit_to_label(bit));
		BS__setBit(bit, $$.hunion);
	}
}            | hexes error
{
	error("expected hex");
}
;

//
// Leaf
//
tree_1ps     : '(' ID ')'
{
	node_t *ret = getnode();

	$$ = ret;
	ret->type = NODE_1PS;
	ret->valid = 1;
	ret->numpaths = 1;
	ret->numLeafs = 1;
	ret->label = label_to_bit($2);
	BS__clear(ret->cUnion);

	if (ret->label == -1) {
		error ("invalid hex");
		ret->valid = 0;
	} else {
		BS__setBit(ret->label, ret->cUnion);
	}
}

//
// Internal AND node
//
|  '(' name tree_2ps_list ')'
{
	int i,j,invalid;
	node_t *c,*d,*node = getnode();
	BitSet_t cInt;

	$$ = node;
	node->type = NODE_1PS;
	node->numpaths = 1;
	node->numAND = 1;
	node->child = $3;
	BS__clear(node->cUnion);
 	for (c=node->child; c; c=c->nextsib) {
		node->numAND += c->numAND;
		node->numOR += c->numOR;
		node->numLeafs += c->numLeafs;
		node->numpaths *= c->numpaths;
		c->parent = node; 
	}
	
	node->label = label_to_bit($2);
	if (node->label == -1) {
		error ("invalid hex");
		node->valid = 0;
		break;
	}

	// compute union and check pairwise intersections
	node->valid = 1;
	invalid = 0;
	for (i=1,c=node->child; c; c=c->nextsib,i++) { 
		if (!c->valid) { invalid++; continue; }

		BS__OR(node->cUnion, node->cUnion, c->cUnion);

		for (j=i+1,d=c->nextsib; d; d=d->nextsib,j++) {
			BS__AND(cInt, c->cUnion, d->cUnion);
			if (!BS__isEmpty(cInt)) {
				char str[2048];
				print_bitset_to_str(cInt,str);
				error("nonempty intersection between child %d & %d: %s", i,j,str);
				node->valid = 0;
			}
		}
	}

	if (invalid) {
		node->valid = 0;
		error("%d invalid substrateg%s", invalid,(invalid!=1)?"ies":"y");
	}

	// skip this if we have a # label
	if (!is_null(node->label)) {
		// do we appear in a valid subtree below us?
		if (BS__isBitSet(node->label,node->cUnion)) {
			error("root label appears below");
			node->valid = 0;
		}
		
		// add ourselves to our union
		BS__setBit(node->label, node->cUnion);
	}
}
;

name:   ID
{
	strcpy($$, $1);
} 
;

tree_1ps_list: tree_1ps
{
	$$ = $1;
}
| tree_1ps_list tree_1ps
{
	node_t *t;
	for (t=$1; t->nextsib; t=t->nextsib);
	t->nextsib = $2;
	$$ = $1;
}
;

//
// Internal OR node
//
tree_2ps     : '[' tree_1ps tree_1ps_list ']'
{
	int a=0;
	node_t *c,*node = getnode();
	BitSet_t cInt;

	$$ = node;
	node->type = NODE_2PS;
	node->child = $2;
	node->child->nextsib = $3;
	node->numpaths = 0;
	node->numOR = 1;
	node->valid = 0;
	node->label = -2;          // FIXME: is this ok?

 	for (c=node->child; c; c=c->nextsib) {
		node->numAND += c->numAND;
		node->numOR += c->numOR;
		node->numLeafs += c->numLeafs;
		node->numpaths += c->numpaths;
		c->parent = node; 
	}

	// compute union and check combined intersection
	BS__clear(node->cUnion);
	BS__clear(cInt);
	BS__NOT(cInt, cInt);
	for (c=node->child; c; c=c->nextsib) { 
		if (c->valid) {
			a++;
			BS__OR(node->cUnion, node->cUnion, c->cUnion);
			BS__AND(cInt, cInt, c->cUnion);
		}
	}

	if (BS__isEmpty(cInt)) {
		node->valid = 1;
	} else if (a < 2) {
		error("%d valid substrateg%s; need at least 2", 
		      a,(a!=1)?"ies":"y");
	} else {
		char str[2048];
		print_bitset_to_str(cInt,str);
		error("nonempty intersection: %s", str);
	} 
}
| '[' pattern_call ']'
{
	$$ = $2;
}
| '[' error ']'
{
	error("badly formed OR node; need at least 2 valid children");
	$$ = getnode();
	$$->valid = 0;
}
;

//
// Pattern call
//
pattern_call: '(' ID pat_empty pat_play ')'
{
	node_t *ret = getnode();
	pattern_t *pat;
	int mapping[512];

	$$ = ret;
	ret->type = NODE_2PS;
	ret->numpaths = 1;
	ret->valid = 0;

	pat = findpattern($2);
	if (!pat) {
		error("pattern '%s' does not exist", $2);
		break;
	} 

/* 	if (pat->connect.n != $3.n) { */
/* 		error ("connect lists differ in length");  */
/* 		break; */
/* 	} else  */
        if (pat->empty.n != $3.n) {
		error ("empty lists differ in length");
		break;
	} else if (pat->played.n != $4.n) {
		error ("played lists differ in length");
		break;
	}

	// compute the 1-1 mapping
	init_mapping(mapping);
	if (//!update_mapping(mapping, &pat->connect, &$3) ||
	    !update_mapping(mapping, &pat->empty, &$3)   ||
	    !update_mapping(mapping, &pat->played, &$4)) 
        {
		break;
	}

	// do iso test
	// FIXME: check pattern is connected region?
	if (!isomorphic_mapping(mapping)) {
		error("mapping is not isomorphic");
		break;
	}

	// insert the mapped proof
	$$ = copy_tree(pat->proof, mapping);
}
;


tree_2ps_list: tree_2ps
{
	$$ = $1;
}
| tree_2ps_list tree_2ps
{
	node_t *t;

	/* - add $2 to end of list */
	/* - also, update the number of paths to the right for
	     each tree already in this list */
	for (t=$1; t->nextsib; t=t->nextsib) 
		t->rightpaths *= $2->numpaths;
	t->nextsib = $2;
	t->rightpaths *= $2->numpaths;
	$$ = $1;
}
;

%%

int yyerror(char *s) { return 0; }

