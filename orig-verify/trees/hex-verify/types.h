#define NODE_1PS     0
#define NODE_2PS     1
#define NODE_PATTERN 2


typedef struct node_s {
	int type;
	int valid;                   
	int numpaths;                /* # of root to leaf paths in this tree */
	int rightpaths;              /* # paths in children to our right */
	int label;                   /* hex to play */

	int numOR, numAND, numLeafs;

	BitSet_t cUnion;             /* all labels in our tree */
	struct node_s *parent,*child,*nextsib;
} node_t;

typedef struct hlist_s {
	int n;
	int *h;
	BitSet_t hunion;
	struct hlist_s *next;
} hlist_t;

typedef struct {
	char name[64];
	int valid;
	hlist_t connect;
	hlist_t empty;
	hlist_t played;
	node_t *proof;                   /* the proof of this pattern */
} pattern_t;
