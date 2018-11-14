#include <stdlib.h>
#include <string.h>

#include "core.h"

int find_assigned(Board * suduko, int * row, int * col)
{
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(suduko->sudoku_board[i][j].value == 0) {
				*row = i;
				*col = j;
				return TRUE;
			}
		}
	}
	row = 0;
	col = 0;
	return FALSE;
}
int used_in_row(Board * sudoku, int row, int num) 
{
	for(int col = 0; col < 9; col++) {
		if(sudoku->sudoku_board[row][col].value == num) {
			return TRUE;
		}
	}
	return FALSE;
}

int used_in_col(Board * sudoku, int col, int num)
{
        for(int row = 0; row < 9; row++) {
                if(sudoku->sudoku_board[row][col].value == num) {
                        return TRUE;
                }
        }
        return FALSE;
}

int check_board(Board * b)
{
	return FALSE;
}
Board * solve_board(Board * b)
{
	return NULL;
}
Board * generate_board()
{
	return NULL;
}
int core_main(int argc, const char * argv[]) 
{
	return 0;
}