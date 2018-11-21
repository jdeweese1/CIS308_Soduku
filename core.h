
#ifndef core_h
#define core_h

#include <stdio.h>
#define TRUE 1
#define FALSE 0

#define BOARD_HEIGHT 9
#define BOARD_WIDTH BOARD_HEIGHT

typedef enum {
	empty,a,b,
	c,d,e,
	f,g,h,
	i,
} CellValue;


typedef struct
{
	CellValue value;
	int visited; 
} Cell;

typedef struct Board
{
	Cell sudoku_board[9][9];
	int is_solved;
} Board;

typedef struct
{
	int is_chosen[BOARD_WIDTH+1];//boolean array
} SimpleDict;


int find_unassigned(Board * sudoku, int * row, int * col);
int used_in_row(Board * sudoku, int * row, int num);
int used_in_col(Board * sudoku, int * col, int num);
int used_in_box(Board * sudoku, int boxStartRow, int boxStartCol, int num);

int check_board(Board * b);
int solve_board(Board * b); 
Board * generate_board();
int read_board(Board * board, FILE * fp);
void print_board(Board * b);

// Methods for a SimpleDict
void dict_clear(SimpleDict * sd);
int dict_add(SimpleDict * sd, CellValue cv);
int dict_contains(SimpleDict *sd, CellValue cv);

int core_main(int argc, const char * argv[]);
#endif /* core_h */
