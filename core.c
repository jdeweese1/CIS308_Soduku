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
// Methods for SimpleDict
void clear_dict(SimpleDict * sd)
{
	for (int i = 0; i < sizeof(sd->is_chosen)/sizeof(sd->is_chosen[0]); i++)
	{
		sd->is_chosen[i] = 0;
	}
}
int dict_add(SimpleDict * sd, CellValue cv)
{
	if (cv > BOARD_WIDTH || cv < 0) return FALSE;
	sd->is_chosen[cv] = 1;
	return TRUE;
}
int dict_contains(SimpleDict *sd, CellValue cv)
{
	if (cv > BOARD_WIDTH || cv < 0) return FALSE;
	return sd->is_chosen[cv] >= 1;
}
int core_main(int argc, const char * argv[]) 
{
	return 0;
}