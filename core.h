
#ifndef core_h
#define core_h

#include <stdio.h>
#define TRUE 1
#define FALSE 0

#define BOARD_HEIGHT 9
#define BOARD_WIDTH 9

typedef enum {
	a,b,c,
	d,e,f,
	g,h,i
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

int find_assigned(Board *, int * , int *);
int used_in_row(Board *, int, int);
int used_in_col(Board *, int, int);

int check_board(Board * b);
Board * solve_board(Board * b); 
Board * generate_board();
int read_board(Board * board, FILE * fp); 

int core_main(int argc, const char * argv[]);
#endif /* core_h */
