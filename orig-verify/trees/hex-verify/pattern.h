
int *addhex(int h);
void print_hlist(hlist_t *h);

node_t *getnode();
void print_tree(node_t *t);
node_t *copy_tree(const node_t *orig, int *mapping);

pattern_t *getpattern();
pattern_t *findpattern(char *name);
void addpattern(pattern_t *p);
void pattern_print_info(pattern_t *p);

int verify_pattern(pattern_t *pat);

void pattern_pstricks(pattern_t *pat);

void pattern_summary();
