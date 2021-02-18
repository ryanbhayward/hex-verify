//
// Pattern and proof trees
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verifier.h"

#define MAX_PATTERNS   4096
int numpatterns = 0;
pattern_t *patterns[MAX_PATTERNS];
int numinvalid = 0;

#define MAX_HEXES      1<<20
int numhexes = 0;
int hhlist[MAX_HEXES];


int *addhex(int h)
{
	if (numhexes >= MAX_HEXES) shutdown("hex overflow");
	hhlist[numhexes] = h;
	return &hhlist[numhexes++];
}

void print_hlist(hlist_t *h)
{
	int i;
	printf("(");
	if (h->n) printf("%s", bit_to_label(h->h[0]));
	for (i=1; i<h->n; i++) printf(" %s", bit_to_label(h->h[i]));
	printf(")");
}


//
// Trees
// 
node_t *getnode()
{
	node_t *ret = malloc (sizeof(node_t));
	if (!ret) shutdown("insufficient memory for node");
	ret->numpaths = 0;
	ret->rightpaths = 1;
	ret->numOR = ret->numAND = ret->numLeafs = 0;
	ret->parent = ret->child = ret->nextsib = NULL;
	return ret;
}

void print_tree(node_t *t)
{
	node_t *c;
	if (t->type == NODE_1PS) {
		printf("(%s", bit_to_label(t->label));
		for (c=t->child; c; c=c->nextsib) print_tree(c);
		printf(")");
	} else {
		printf("[");
		for (c=t->child; c; c=c->nextsib) print_tree(c);
		printf("]");
	}	
}

void tree_pstricks(node_t *t, FILE *fp, int root)
{
	node_t *c;

	if (t->child) {
		fprintf(fp, "\\pstree");
		if (root) {
			fprintf(fp, "[treemode=R, levelsep=6ex, treesep=4pt,");
			fprintf(fp, "nodesep=1pt, treefit=tight]");
		}
		if (t->type == NODE_1PS) 
			fprintf(fp, "{\%s{%s}}", 
				(pstricks_circles)?"\\Tcircle":"\\TR",
				bit_to_label(t->label));
		else 
			fprintf(fp, "{\\Tdot}");

		fprintf(fp, "{\n");
		for (c=t->child; c; c=c->nextsib) tree_pstricks(c, fp, 0);
		fprintf(fp, "}\n");
	} else {
		assert(t->type == NODE_1PS);
		fprintf(fp, "\%s{%s}", 
			(pstricks_circles)?"\\Tcircle":"\\TR",
			bit_to_label(t->label));
	}
}

// THIS IS VERY BAD
// FIXME: switch when if we switch bitset size!!!
void map_bitset(BitSet_t bs, int *mapping)
{
	int i;
	BitSet_t t;
	BS__copy(t, bs);
	BS__clear(bs);
	for (i=0; i<128; i++) {
		if (BS__isBitSet(i,t)) BS__setBit(mapping[i],bs);
	}
}

node_t *copy_tree(const node_t *orig, int *mapping)
{
	node_t *a,*c,*ret = getnode();
	*ret = *orig;

	if (ret->type == NODE_1PS) ret->label = mapping[orig->label];
	map_bitset(ret->cUnion, mapping);
	if (!ret->child) return ret;

	ret->child = a = copy_tree(orig->child, mapping);
	for (c=orig->child->nextsib; c; c=c->nextsib) {
		a->nextsib = copy_tree(c, mapping);
		a = a->nextsib;
	}
	return ret;
}

void get_path(node_t *tree, int n, BitSet_t p)
{
	node_t *c;

	if (n >= tree->numpaths) 
		shutdown("n = %d, numpaths = %d\n", n, tree->numpaths);

	if (tree->type == NODE_2PS) {
		for (c=tree->child; c; c=c->nextsib) {
			if (n < c->numpaths) {
				get_path(c, n, p);
				break;
			}
			n -= c->numpaths;
		}
	} else {
		if (!is_null(tree->label)) BS__setBit(tree->label,p);
		if (!tree->child) return;

		for (c=tree->child; c; c=c->nextsib) {
			get_path(c, n / c->rightpaths, p);
			n %= c->rightpaths;
		}
	}
}

//
// Patterns
//
pattern_t *getpattern()
{
	pattern_t *ret = malloc (sizeof(pattern_t));
	memset(ret, 0, sizeof(ret));
	return ret;
}

pattern_t *findpattern(char *name)
{
	int i;
	for (i=0; i<numpatterns; i++) 
		if (!strcmp(name, patterns[i]->name)) return patterns[i];
	return NULL;
}

void addpattern(pattern_t *p)
{
	int i;
	for (i=0; i<numpatterns; i++) {
		if (!strcmp(p->name, patterns[i]->name)) {
			warning("shadowing old pattern '%s'", p->name);
			patterns[i] = p;
			return;
		}
	}
	if (numpatterns >= MAX_PATTERNS) 
		shutdown("Too many patterns! (%d)", MAX_PATTERNS);

	patterns[numpatterns++] = p;		
	if (!p->valid) numinvalid++;
}

void pattern_print_info(pattern_t *p)
{
	hlist_t *hl;

	printf("connect: ");
	print_hlist(&p->connect); 	
	for (hl=p->connect.next; hl; hl=hl->next) {
		printf(" | ");
		print_hlist(hl); 
	}
	printf("\n");
	printf("  empty: "); print_hlist(&p->empty); printf("\n");
	printf(" played: "); print_hlist(&p->played); printf("\n");

	if (print_proofs) {
		printf("  proof: ");
		print_tree(p->proof);
		printf("\n");
	}

	printf("  stats: AND = %d, OR = %d, Leafs = %d\n", p->proof->numAND,
	       p->proof->numOR, p->proof->numLeafs);
}


int verify_pattern(pattern_t *pat)
{
	hlist_t *hl;
	int i,npaths,good;
	BitSet_t u;

	if (pat->connect.n < 2) {
		error ("connect list must contain at least two hexes");
		return 0;
	}
	
	// ensure the empty and played lists are disjoint
	if (!BS__emptyIntersection(pat->empty.hunion,pat->played.hunion)) {
		char str[2048];
		BitSet_t cInt;
		BS__AND(cInt,pat->empty.hunion,pat->played.hunion);
		print_bitset_to_str(cInt,str);
		error("%s are both empty and played", str);
		return 0;
	}

	// make sure all moves we make in the proof are in the empty list
	// FIXME: change this if we allow duplicate moves or null moves
	//        to allow moves from the 'played' list to be played
	if (!BS__isSubset(pat->proof->cUnion, pat->empty.hunion)) {
		error ("proof contains move not in the empty list");
		printf("proof: "); print_bitset_as_label(pat->proof->cUnion); printf("\n");
		printf("empty: "); print_bitset_as_label(pat->empty.hunion); printf("\n");
		return 0;
	}

	// abort path checking if root is not valid
	if (!pat->proof->valid) {
		printf("Path checking aborted since proof marked invalid\n");
		return 0;
	}

	//printf("&u = %p, &i = %p\n", u, &i);
	npaths = pat->proof->numpaths;
	if (print_paths) printf("%d paths:\n", npaths);

	for (i=0; i<npaths; i++) {
		if (!print_paths) {
			if (npaths < 1000 || (i%1000) == 0) 
				printf("  paths: %d/%d\r", i+1, npaths);
			fflush(stdout);
		}

		set_starting_board();
		play_moves(pat->played.hunion);
		BS__clear(u);

		// *********** FIXME: WTF?!!?  ******************
		// wierd things going on here sometimes.
		// use the above comment printf if things break.
		// the address of u can change after the
		// get_path below (?!)
		// **********************************************
		get_path(pat->proof, i, u);
		
		play_moves(u);
		good = 0;
		for (hl=&pat->connect; hl; hl=hl->next) {
			if (winning(hl->hunion)) { 
				good = 1;
				break;
			}
		}
		
		if (!good) {
			printf("\n");
			print_bitset_as_label(pat->played.hunion); printf(" + ");
			print_bitset_as_label(u); 
			printf(": played stones do no satisfy a listed connection\n");
			break;
		}

		if (print_paths) {
			print_bitset_as_label(pat->played.hunion); printf(" + ");
			print_bitset_as_label(u); 
			printf("\n");
		}
	}
	if (!print_paths) printf("\n");

	return (i == npaths) ? 1 : 0;
}

void pattern_pstricks(pattern_t *pat)
{
	char name[128];
	FILE *fp;

	strcpy(name, pat->name);
	strcat(name, ".tex");
	fp = fopen(name, "w");
	if (!fp) {
		error("Could not open '%s' for writing.", name);
		return;
	}

	fprintf(fp, "\\begin{figure}[p]\n");
	fprintf(fp, "\\centering\n");
//	fprintf(fp, "\\footnotesize\n");
	fprintf(fp, "\\small\n");

	fprintf(fp, "\n");

	tree_pstricks(pat->proof, fp, 1);
	
	fprintf(fp, "\n\n");
	fprintf(fp, "\\caption{%s}\n", pat->name);
	fprintf(fp, "\\end{figure}\n");
	fclose(fp);
}

void pattern_summary()
{
	printf("Found %d pattern%s: %d valid, %d invalid.\n", 
	       numpatterns, (numpatterns > 1) ? "s" : "",
	       numpatterns-numinvalid, numinvalid);
}

