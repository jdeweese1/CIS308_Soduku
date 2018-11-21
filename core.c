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
	*row = 0;
	*col = 0;
	return FALSE;
}


int used_in_row(Board * sudoku, int * row, int num) 
{
	for(int col = 0; col < 9; col++) {
		if(sudoku->sudoku_board[*row][col].value == num) {

			return TRUE;
		}
	}
	return FALSE;
}

int used_in_col(Board * sudoku, int * col, int num)
{
        for(int row = 0; row < 9; row++) {
                if(sudoku->sudoku_board[row][*col].value == num) {

                        return TRUE;
                }
        }
        return FALSE;
}
int used_in_box(Board * sudoku, int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    if (sudoku->sudoku_board[row + boxStartRow][col + boxStartCol].value == num) {
                        return TRUE;
			}
		}
	}
       return FALSE;
}
int is_safe(Board * sudoku, int * col, int * row, int num)
{
	return (!used_in_row(sudoku, row, num) &&
		!used_in_col(sudoku, col, num) &&
		!used_in_box(sudoku, (*row) - (*row) % 3, (*col) - (*col) % 3, num));
}
int check_board(Board * b)
{
	return FALSE;
}
int solve_board(Board * b)
{
	int * row;
	int * col;
	if(!find_unassigned(b, row, col)) {
		return TRUE;
	}
	else {
		for(int i = 1; i <= 9; i++) {
			if(is_safe(b, row, col, i)) {
				b->sudoku_board[*row][*col].value = i;
				if(solve_board(b)) {
					return TRUE;
				}
				b->sudoku_board[*row][*col].value = 0;
			}
		}
	return FALSE;
	}

}
Board * generate_board()
{
	return NULL;
}

void print_board(Board * b) {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			printf("%d ", b->sudoku_board[i][j].value);
		}
	printf("\n");
	}
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
	printf("This is before board");
	Board * example;
	printf("this is before loop");
	for(int i = 0; i < 9; i++) {
                for(int j = 0; j < 9; j++) {
                         example->sudoku_board[i][j].value = 0;
                }
        }
	printf("this is before print board");
	print_board(example);
	printf("Print board worked fine");
	solve_board(example);
	print_board(example);
	return 0;
}
