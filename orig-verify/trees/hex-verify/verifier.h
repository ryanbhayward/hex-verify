#include "bitset.h"
#include "types.h"

#include "parser.h"
#include "board.h"
#include "pattern.h"

void error(char *str, ...);
void warning(char *str, ...);
void lex_init();
void lex_shutdown();

void shutdown(char *str, ...);

// cmdline args
extern int print_proofs;
extern int print_paths;

extern int pstricks_on;
extern int pstricks_circles;
