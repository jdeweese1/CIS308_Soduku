
#ifndef core_h
#define core_h

#include <stdio.h>
#define TRUE 1
#define FALSE 0
enum cellValues
{
	0,1,2,3,4,5,6,7,8,9
};

typedef struct cell
{
	int value;
	int visited = FALSE; 
};

typedef struct board
{
	cell suduko_board[9][9];
	int is_solved = FALSE;
} board;

int check_board(board *);
board * solve_board(board *); 
board * generate_board();
#endif /* core_h */
