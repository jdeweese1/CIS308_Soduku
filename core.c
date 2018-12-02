#include <stdlib.h>
#include <string.h>

#include "core.h"


int find_unassigned(Board * suduko, int * row, int * col)
{
	if (suduko == NULL)
	{
		*row = 0;
		*col = 0;
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
int check_board(Board * b) {
        if(b == NULL) {
                return FALSE;
        }
        SimpleDict sd;
        //row checks
        for(int i = 0; i < 9; i++) {
                dict_clear(&sd);
                for(int j = 0; j < 9; j++) {
                        if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
                                dict_add(&sd, b->sudoku_board[i][j].value);
                        }
                        else {
                                return FALSE;
                        }
                }
        }
        //col checks
         for(int i = 0; i < 9; i++) {
                dict_clear(&sd);
                for(int j = 0; j < 9; j++) {
                        if(!dict_contains(&sd, b->sudoku_board[j][i].value)) {
                                dict_add(&sd, b->sudoku_board[j][i].value);
                        }
                        else {
                                return FALSE;
                        }
                }
        }
        //box checks
	//top-left
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}

	//top-center
	for(int i = 0; i < 3; i++) {
		for(int j = 3; j < 6; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}

	//top-right
	for(int i = 0; i < 3; i++) {
		for(int j = 6; j < 9; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}
	//middle-left
	for(int i = 3; i < 6; i++) {
		for(int j = 0; j < 3; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}
	//middle-center
	for(int i = 3; i < 6; i++) {
		for(int j = 3; j < 6; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}
	//middle-right
	for(int i = 3; i < 6; i++) {
		for(int j = 6; j < 9; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}
	//bottom-left
	for(int i = 6; i < 9; i++) {
		for(int j = 0; j < 3; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}
	//bottom-center
	for(int i = 6; i < 9; i++) {
		for(int j = 3; j < 6; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}
	//bottom-right
	for(int i = 6; i < 9; i++) {
		for(int j = 6; j < 9; j++) {
			if(!dict_contains(&sd, b->sudoku_board[i][j].value)) {
				dict_add(&sd, b->sudoku_board[i][j].value);
			}
			else {
					return FALSE;
			}
		}
	}
        return TRUE;

}

int solve_board(Board * b)
{
	if(b == NULL)
	{
		return -1;
	}
	int row = 0;
	int col = 0;

	if(!find_unassigned(b, &row, &col)) {
		return TRUE;
	}
	else {
		for(int i = 1; i <= 9; i++) {
			if(is_safe(b, &row, &col, i)) {
				b->sudoku_board[row][col].value = i;
				if(solve_board(b)) {
					return TRUE;
				}
				b->sudoku_board[row][col].value = 0;
			}
		}
	return FALSE;
	}

}
Board * generate_board()
{
	printf("entered generate");
	int random = rand() % 9;
	int random2 = rand() % 9;
	printf("generated random ints");
	Board * board;
	board->sudoku_board[random][random2].value = rand() % 9;
	printf("added number");
	solve_board(board);
	printf("solved board");
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			int random3 = rand() % 9;
			if(random3 % 4 != 0)
			{
				board->sudoku_board[i][j].value = 0;
			}
		}
	}
	return board;
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
			board->sudoku_board[i][j].value = buffer[j] -'0';
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
	return TRUE;
}

// ./main solve -i text.txt -o out.txt
// ./main validate -i text.txt
// ./main generate -o out.txt
int core_main(int argc, const char * argv[]) 
{
	if(argc < 4)
	{
		printf("Missing required arguments\n");
		return 1;
	}
	File file_read;
	File file_write;
	if (argc == 6)
	{
		if(strcmp(argv[1], "solve") == 0)
		{
			if(strcmp(argv[2], "-i") == 0)
			{
				if (strcmp(argv[4], "-o") == 0)
				{
					Board board1;
		
					file_read.fp = fopen(argv[3], "r");
					read_board(&board1, file_read.fp);
					print_board(&board1);
		
					if (solve_board(&board1))
					{
						file_write.fp = fopen(argv[5], "w");
						write_board(&board1, file_write.fp);
					}
					else
					{
						printf("Board not solvable\n");
					}
				}
	
			}
			else
				{
					printf("Must pass in an input file (-i followed by the filename)\n");
					fclose(file_read.fp);
					fclose(file_write.fp);
					return 1;
				}
		}
	}
	else if(strcmp(argv[1], "check") == 0)
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
	else if(strcmp(argv[1], "generate") == 0)
	{
		if(strcmp(argv[2], "-o") == 0)
		{
			printf("Above write");
			file_write.fp = fopen(argv[3], "w");
			printf("opened file writer");
			Board * b = generate_board();
			printf("generated board");
			write_board(b, file_write.fp);
			printf("finished");
		}
		else printf("Must be writing to an output file (-o followed by the filename)\n.");
	}
	else 
		printf("Invalid input.  Try again.  Format: ./main action -i text.txt\n");


	fclose(file_read.fp);
	fclose(file_write.fp);
	return 0;
}
