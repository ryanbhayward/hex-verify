// The board is laid out like this:
//
/*
//             WEST (12)
//             \-1-2-3-\
//             a\ 0 1 2 \ a
//  SOUTH (11)  b\ 3 4 5 \ b  NORTH (9)
//               c\ 6 7 8 \ c
//                 \-1-2-3-\
//                  EAST(10)
*/

int is_null(int);
int label_to_bit(char *str);
char *bit_to_label(int );
void init_board(int size);

void print_bitset_to_str(BitSet_t p, char *s);
void print_bitset_as_label(BitSet_t p);

void set_all_playable(BitSet_t p);
void set_starting_board();
void play_moves(BitSet_t p);

int winning(BitSet_t s);

void init_mapping(int mapping[512]);
int isomorphic_mapping(int *);


extern int boardsize;
