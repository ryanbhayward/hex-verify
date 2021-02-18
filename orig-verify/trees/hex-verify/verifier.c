#include <stdlib.h>
#include <stdarg.h>
#include <getopt.h>

#include "verifier.h"


int print_paths = 0;
int print_proofs = 0;

int pstricks_on = 0;
int pstricks_circles = 0;


extern int yydebug;
int yyparse();

void shutdown(char *str, ...)
{
	char out[128];
	va_list args;
	va_start(args, str);
	vsnprintf(out, 128, str, args);
	va_end(args);

	printf("error: %s\n", out);
	
	exit(1);
}


/*
 *  Command-line option stuff
 */
static struct option long_options[] =
{
        /* These options set a flag. */
        {"debug",              no_argument,       &yydebug,          1},
	{"print-paths",        no_argument,       &print_paths,      1},
	{"print-proofs",       no_argument,       &print_proofs,     1},
	{"pstricks",           no_argument,       &pstricks_on,      1},
	{"pstricks-circles",   no_argument,       &pstricks_circles, 1},

        /* These options don't set a flag.
           We distinguish them by their indices. */
        {"help",               no_argument,       0,              'h'},

        //{"lex-tab-width",      required_argument, NULL,           't'},

        {0, 0, 0, 0}
};

void usage()
{
	printf("usage:\n");
	printf("\t--debug [-d]           -- turn grammar debugging on\n");
	printf("\t--print-paths          -- display paths during verification\n");
	printf("\t--print-proofs         -- display parsed proof tree\n");
	printf("\t--pstricks             -- dump each pattern in pstricks format\n");
	printf("\t\t--pstricks-circles   -- places circles around hex labels\n");
	printf("\t--help [-h]            -- this message\n");
	exit(0);
}

void handle_args(int argc, char **argv)
{
        int c,index;
        while (1) {
                c = getopt_long (argc, argv, "dhpt:", long_options, &index);
                if (c == -1) break;
                switch(c) {
                case 'd': yydebug = 1; break;
                case 'h': usage(); break;
//	  	  case 't': sscanf(optarg, "%d", &lex_tabwidth);
//                          break;
                }
        }
}

int main(int argc, char **argv)
{
	handle_args(argc, argv);

	lex_init();
	if (yyparse()) shutdown ("hex: errors occured during parsing."); 

	lex_shutdown();
	return 0;
}
