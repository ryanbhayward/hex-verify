typedef union
{
	int ival;
	char str[64];
	node_t *node;
	BitSet_t bs;
	hlist_t hlist;
	pattern_t *pattern;
} YYSTYPE;
#define	ID	257
#define	DIGIT	258
#define	BOARDSIZE	259
#define	ALL	260


extern YYSTYPE yylval;
