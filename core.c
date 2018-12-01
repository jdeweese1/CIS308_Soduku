#include <stdlib.h>
#include <string.h>

#include "core.h"


int find_unassigned(Board * suduko, int * row, int * col)
{
	if (suduko == NULL)
	{
		*row = -1;
		*col = -1;
		 return FALSE;
	}
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(suduko->sudoku_board[i][j].value == 0) {
				*row = i;
				*col = j;
				return TRUE;
			}
		}
	}
	*row = -1;
	*col = -1;
	return FALSE;
}

int used_in_row(Board * sudoku, int * row, int num) 
{
	if (sudoku == NULL ||
		row == NULL)
	{
		return -1;
	}
	for(int col = 0; col < 9; col++) {
		if(sudoku->sudoku_board[*row][col].value == num) {

			return TRUE;
		}
	}
	return FALSE;
}

int used_in_col(Board * sudoku, int * col, int num)
{
	if (sudoku == NULL ||
		col == NULL)
	{
		return -1;
	}
        for(int row = 0; row < 9; row++) {
                if(sudoku->sudoku_board[row][*col].value == num) {

                        return TRUE;
                }
        }
        return FALSE;
}
int used_in_box(Board * sudoku, int boxStartRow, int boxStartCol, int num)
{
	if(sudoku == NULL ||
		boxStartRow < 0 || boxStartRow >= BOARD_HEIGHT -2|| // Row out of bounds
		boxStartCol < 0 || boxStartCol >= BOARD_HEIGHT -2|| // Col out of bounds
		num < 0 || num > BOARD_HEIGHT) // Value to search for is out of bounds
	{
		return -1;
	}
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
	 if( sudoku == NULL || col == NULL || row == NULL)
	 {
	 	return	-1;
	 }
	return (!used_in_row(sudoku, row, num) &&
		!used_in_col(sudoku, col, num) &&
		!used_in_box(sudoku, (*row) - (*row) % 3, (*col) - (*col) % 3, num));
}
int check_board(Board * b)
{
	if (b == NULL) return FALSE;
	//check all rows
	for(int row_num =0;row_num<BOARD_HEIGHT; row_num++)
	{
		for (int col_num = 0; col_num < BOARD_WIDTH; col_num++)
		{
			int value = b->sudoku_board[row_num][col_num].value;
			// if(has_row_duplicates(b,row_num,value)) return FALSE;
			// if(has_col_duplicates(b,col_num,value)) return FALSE;
		}
	}
	// should we check if the board is valid? i.e. no number conflicts in square, rows, cols?
	// or  
	//check all columns
	//check all 3x3 boxes
	return FALSE;
}
int solve_board(Board * b)
{
	if(b == NULL)
	{
		return -1;
	}
	int * row;
	int * col;
	if(!find_unassigned(b, row, col)) {
		return TRUE;
	}
	else {
		for(int i = 1; i <= 9; i++) {
			if(is_safe(b, col, row, i)) {
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

void dict_clear(SimpleDict * sd)
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

int read_board(Board * board, FILE * fp)
{
	if(fp == NULL)
		return FALSE;
	if(board == NULL)
		return FALSE;
	char buffer[50];
	for(int i = 0; i < 9; i++)
	{
		fscanf(fp, "%s", buffer);
		for(int j = 0; j < 9; j++)
		{
			board->sudoku_board[i][j].value = atoi(&buffer[j]);
		}
	}
	return TRUE;
}

int write_board(Board * board, FILE * fp)
{
	if(fp == NULL) return FALSE;
	if(board == NULL) return FALSE;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			fprintf(fp, "%d", board->sudoku_board[i][j].value);
		}
		fprintf(fp, "\n");
	}
}

// ./main solve -i text.txt
// ./main validate -i text.txt
// ./main generate -o out.txt
int core_main(int argc, const char * argv[]) 
{
	if(argc < 4)
	{
		printf("Missing required arguments\n");
	}
	File file_read;
	File file_write;
	if(strcmp(argv[1], "solve") == 0)
	{
		if(strcmp(argv[2], "-i") == 0)
		{
			file_read.fp = fopen(argv[3], "r");
			Board board1;
			read_board(&board1, file_read.fp);
			solve_board(&board1);
			print_board(&board1);
			file_write.fp = fopen(argv[3], "w");
			write_board(&board1, file_write.fp);
		}
		else
			printf("Must pass in an input file (-i followed by the filename)\n");
	}
	else if(strcmp(argv[1], "validate") == 0)
	{
		if(strcmp(argv[2], "-i") == 0)
		{
			file_read.fp = fopen(argv[3], "r");
			Board board1;
			read_board(&board1, file_read.fp);
			if(check_board(&board1) == TRUE)
				printf("Valid completed Soduku board.\n");
			else
				printf("Invalid Soduku board. Try again.\n");
		}
		else
			printf("Must pass in an input file (-i followed by the filename)\n");
	}
	else 
		printf("Invalid input.  Try again.  Format: ./main action -i text.txt\n");


	fclose(file_read.fp);
	fclose(file_write.fp);
}
