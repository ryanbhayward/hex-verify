
/*  A Bison parser, made from parser.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	ID	257
#define	DIGIT	258
#define	BOARDSIZE	259
#define	ALL	260

#line 1 "parser.y"

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


#line 41 "parser.y"
typedef union
{
	int ival;
	char str[64];
	node_t *node;
	BitSet_t bs;
	hlist_t hlist;
	pattern_t *pattern;
} YYSTYPE;
#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		65
#define	YYFLAG		-32768
#define	YYNTBASE	11

#define YYTRANSLATE(x) ((unsigned)(x) <= 260 ? yytranslate[x] : 29)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     7,
     8,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     9,     2,    10,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     8,    12,    14,    17,    25,    33,    37,    39,
    41,    43,    45,    49,    51,    54,    57,    61,    65,    67,
    70,    73,    77,    82,    84,    86,    89,    94,    98,   102,
   108,   110
};

static const short yyrhs[] = {    12,
    13,     0,     7,     5,     4,     8,     0,     7,     1,     8,
     0,    14,     0,    13,    14,     0,     7,    15,    16,    17,
    18,    26,     8,     0,     7,    15,    16,    17,    18,     1,
     8,     0,     7,     1,     8,     0,     3,     0,    19,     0,
    21,     0,    21,     0,     7,    20,     8,     0,    21,     0,
    20,    21,     0,     7,     8,     0,     7,    22,     8,     0,
     7,     1,     8,     0,     3,     0,    22,     3,     0,    22,
     1,     0,     7,     3,     8,     0,     7,    24,    28,     8,
     0,     3,     0,    23,     0,    25,    23,     0,     9,    23,
    25,    10,     0,     9,    27,    10,     0,     9,     1,    10,
     0,     7,     3,    17,    18,     8,     0,    26,     0,    28,
    26,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    61,    67,    73,    83,    84,    87,   113,   120,   129,   136,
   142,   148,   154,   159,   164,   174,   181,   185,   195,   205,
   216,   225,   248,   313,   319,   323,   335,   381,   385,   396,
   447,   451
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ID","DIGIT",
"BOARDSIZE","ALL","'('","')'","'['","']'","input_file","board_info","pattern_list",
"pattern","pat_start","pat_connect","pat_empty","pat_play","hexlistlist","hexlist_a",
"hexlist","hexes","tree_1ps","name","tree_1ps_list","tree_2ps","pattern_call",
"tree_2ps_list", NULL
};
#endif

static const short yyr1[] = {     0,
    11,    12,    12,    13,    13,    14,    14,    14,    15,    16,
    17,    18,    19,    20,    20,    21,    21,    21,    22,    22,
    22,    23,    23,    24,    25,    25,    26,    26,    26,    27,
    28,    28
};

static const short yyr2[] = {     0,
     2,     4,     3,     1,     2,     7,     7,     3,     1,     1,
     1,     1,     3,     1,     2,     2,     3,     3,     1,     2,
     2,     3,     4,     1,     1,     2,     4,     3,     3,     5,
     1,     2
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     1,     4,     3,     0,     0,
     9,     0,     5,     2,     8,     0,     0,    10,     0,     0,
    14,     0,    11,     0,    19,    16,     0,    13,    15,     0,
    12,    18,    21,    20,    17,     0,     0,     0,     7,     0,
     0,     0,     0,     6,    29,    24,     0,     0,    25,     0,
    28,    22,     0,    31,     0,    24,    27,    26,     0,    23,
    32,    30,     0,     0,     0
};

static const short yydefgoto[] = {    63,
     2,     6,     7,    12,    17,    22,    30,    18,    20,    23,
    27,    42,    47,    50,    38,    43,    55
};

static const short yypact[] = {    11,
    16,    25,    15,    29,    21,    25,-32768,-32768,    26,    27,
-32768,    31,-32768,-32768,-32768,    32,    32,-32768,     4,    18,
-32768,    32,-32768,    28,-32768,-32768,    12,-32768,-32768,     0,
-32768,-32768,-32768,-32768,-32768,    33,     7,    34,-32768,    19,
    37,    36,    35,-32768,-32768,    20,    38,    41,-32768,     9,
-32768,-32768,    32,-32768,    22,    40,-32768,-32768,    42,-32768,
-32768,-32768,    46,    49,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,    45,-32768,-32768,     6,     1,-32768,-32768,   -16,
-32768,   -40,-32768,-32768,   -44,-32768,-32768
};


#define	YYLAST		54


static const short yytable[] = {    21,
    36,    49,    54,    29,    24,    31,    25,    40,    37,    58,
    61,    26,    33,    41,    34,    48,     3,     1,    57,    35,
     4,    10,     8,    11,    19,    28,    19,    52,    45,    60,
    37,     5,     9,    14,    15,    32,    31,    16,    19,    46,
    39,    44,    48,    56,    51,    64,    37,    52,    65,    62,
    13,    53,     0,    59
};

static const short yycheck[] = {    16,
     1,    42,    47,    20,     1,    22,     3,     1,     9,    50,
    55,     8,     1,     7,     3,     7,     1,     7,    10,     8,
     5,     1,     8,     3,     7,     8,     7,     8,    10,     8,
     9,     7,     4,     8,     8,     8,    53,     7,     7,     3,
     8,     8,     7,     3,    10,     0,     9,     8,     0,     8,
     6,    46,    -1,    53
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/lib/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/lib/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 62 "parser.y"
{
	pattern_summary();
;
    break;}
case 2:
#line 68 "parser.y"
{
	if (yyvsp[-1].ival <= 0 || yyvsp[-1].ival >= 19) shutdown ("bad board size: %d\n", yyvsp[-1].ival);
	printf("board size: %d\n\n", yyvsp[-1].ival);
	init_board(yyvsp[-1].ival);   
;
    break;}
case 3:
#line 74 "parser.y"
{
	printf("error in board size.\n");
;
    break;}
case 6:
#line 88 "parser.y"
{
	hlist_t *hl;
	pattern_t *ret = getpattern();
	strcpy(ret->name, yyvsp[-5].str);
	ret->valid = 1;

	ret->connect = yyvsp[-4].hlist;
	ret->empty = yyvsp[-3].hlist;
	ret->played = yyvsp[-2].hlist;
	ret->proof = yyvsp[-1].node;
	yyval.pattern = ret;

	pattern_print_info(ret);

	if ((ret->valid = verify_pattern(ret))) {
		printf("VALID pattern.\n");
	} else {
		printf("INVALID pattern.\n");
	}

	addpattern(ret);
	if (pstricks_on && ret->valid) pattern_pstricks(ret);

	printf("\n");	
;
    break;}
case 7:
#line 114 "parser.y"
{
	pattern_t *ret = getpattern();	
	error("Badly formed proof");
	ret->valid = 0;
	yyval.pattern = ret;
;
    break;}
case 8:
#line 121 "parser.y"
{
	pattern_t *ret = getpattern();
	error("Badly formed pattern.");
	ret->valid = 0;
	yyval.pattern = ret;
;
    break;}
case 9:
#line 130 "parser.y"
{
	printf("%s\n", yyvsp[0].str);
	strcpy(yyval.str,yyvsp[0].str);
;
    break;}
case 10:
#line 137 "parser.y"
{
	yyval.hlist = yyvsp[0].hlist;
;
    break;}
case 11:
#line 143 "parser.y"
{
	yyval.hlist = yyvsp[0].hlist;
;
    break;}
case 12:
#line 149 "parser.y"
{
	yyval.hlist = yyvsp[0].hlist;
;
    break;}
case 13:
#line 155 "parser.y"
{
	yyval.hlist = yyvsp[-1].hlist;
;
    break;}
case 14:
#line 160 "parser.y"
{
	yyval.hlist = yyvsp[0].hlist;

;
    break;}
case 15:
#line 165 "parser.y"
{
	hlist_t *c, *h = malloc(sizeof(hlist_t));
	*h = yyvsp[0].hlist;
	yyval.hlist = yyvsp[-1].hlist;
	for (c=&yyval.hlist; c->next; c=c->next);
	c->next = h;
;
    break;}
case 16:
#line 175 "parser.y"
{
	yyval.hlist.n = 0;
	yyval.hlist.h = NULL;
	yyval.hlist.next = NULL;
	BS__clear(yyval.hlist.hunion);
;
    break;}
case 17:
#line 182 "parser.y"
{
	yyval.hlist = yyvsp[-1].hlist;
;
    break;}
case 18:
#line 186 "parser.y"
{
	error("error in list");
	yyval.hlist.n = 0;
	yyval.hlist.h = NULL;
	yyval.hlist.next = NULL;
	BS__clear(yyval.hlist.hunion);
;
    break;}
case 19:
#line 196 "parser.y"
{
	int bit = label_to_bit(yyvsp[0].str);
	if (bit == -1) error ("invalid hex");
	yyval.hlist.n = 1;
	yyval.hlist.h = addhex(bit);
	yyval.hlist.next = NULL;
	BS__clear(yyval.hlist.hunion);
	BS__setBit(bit, yyval.hlist.hunion);
;
    break;}
case 20:
#line 206 "parser.y"
{
	int bit = label_to_bit(yyvsp[0].str);
	if (bit == -1) error("invalid hex");
	else {
		yyval.hlist.n++;
		addhex(bit);
		if (BS__isBitSet(bit, yyval.hlist.hunion)) 
			warning("hex (%s) duplicated in list", bit_to_label(bit));
		BS__setBit(bit, yyval.hlist.hunion);
	}
;
    break;}
case 21:
#line 217 "parser.y"
{
	error("expected hex");
;
    break;}
case 22:
#line 226 "parser.y"
{
	node_t *ret = getnode();

	yyval.node = ret;
	ret->type = NODE_1PS;
	ret->valid = 1;
	ret->numpaths = 1;
	ret->numLeafs = 1;
	ret->label = label_to_bit(yyvsp[-1].str);
	BS__clear(ret->cUnion);

	if (ret->label == -1) {
		error ("invalid hex");
		ret->valid = 0;
	} else {
		BS__setBit(ret->label, ret->cUnion);
	}
;
    break;}
case 23:
#line 249 "parser.y"
{
	int i,j,invalid;
	node_t *c,*d,*node = getnode();
	BitSet_t cInt;

	yyval.node = node;
	node->type = NODE_1PS;
	node->numpaths = 1;
	node->numAND = 1;
	node->child = yyvsp[-1].node;
	BS__clear(node->cUnion);
 	for (c=node->child; c; c=c->nextsib) {
		node->numAND += c->numAND;
		node->numOR += c->numOR;
		node->numLeafs += c->numLeafs;
		node->numpaths *= c->numpaths;
		c->parent = node; 
	}
	
	node->label = label_to_bit(yyvsp[-2].str);
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
;
    break;}
case 24:
#line 314 "parser.y"
{
	strcpy(yyval.str, yyvsp[0].str);
;
    break;}
case 25:
#line 320 "parser.y"
{
	yyval.node = yyvsp[0].node;
;
    break;}
case 26:
#line 324 "parser.y"
{
	node_t *t;
	for (t=yyvsp[-1].node; t->nextsib; t=t->nextsib);
	t->nextsib = yyvsp[0].node;
	yyval.node = yyvsp[-1].node;
;
    break;}
case 27:
#line 336 "parser.y"
{
	int a=0;
	node_t *c,*node = getnode();
	BitSet_t cInt;

	yyval.node = node;
	node->type = NODE_2PS;
	node->child = yyvsp[-2].node;
	node->child->nextsib = yyvsp[-1].node;
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
;
    break;}
case 28:
#line 382 "parser.y"
{
	yyval.node = yyvsp[-1].node;
;
    break;}
case 29:
#line 386 "parser.y"
{
	error("badly formed OR node; need at least 2 valid children");
	yyval.node = getnode();
	yyval.node->valid = 0;
;
    break;}
case 30:
#line 397 "parser.y"
{
	node_t *ret = getnode();
	pattern_t *pat;
	int mapping[512];

	yyval.node = ret;
	ret->type = NODE_2PS;
	ret->numpaths = 1;
	ret->valid = 0;

	pat = findpattern(yyvsp[-3].str);
	if (!pat) {
		error("pattern '%s' does not exist", yyvsp[-3].str);
		break;
	} 

/* 	if (pat->connect.n != $3.n) { */
/* 		error ("connect lists differ in length");  */
/* 		break; */
/* 	} else  */
        if (pat->empty.n != yyvsp[-2].hlist.n) {
		error ("empty lists differ in length");
		break;
	} else if (pat->played.n != yyvsp[-1].hlist.n) {
		error ("played lists differ in length");
		break;
	}

	// compute the 1-1 mapping
	init_mapping(mapping);
	if (//!update_mapping(mapping, &pat->connect, &$3) ||
	    !update_mapping(mapping, &pat->empty, &yyvsp[-2].hlist)   ||
	    !update_mapping(mapping, &pat->played, &yyvsp[-1].hlist)) 
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
	yyval.node = copy_tree(pat->proof, mapping);
;
    break;}
case 31:
#line 448 "parser.y"
{
	yyval.node = yyvsp[0].node;
;
    break;}
case 32:
#line 452 "parser.y"
{
	node_t *t;

	/* - add $2 to end of list */
	/* - also, update the number of paths to the right for
	     each tree already in this list */
	for (t=yyvsp[-1].node; t->nextsib; t=t->nextsib) 
		t->rightpaths *= yyvsp[0].node->numpaths;
	t->nextsib = yyvsp[0].node;
	t->rightpaths *= yyvsp[0].node->numpaths;
	yyval.node = yyvsp[-1].node;
;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 466 "parser.y"


int yyerror(char *s) { return 0; }

