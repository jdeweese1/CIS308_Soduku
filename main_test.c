//
//  main_test.c
//  Week10 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "min_unit.h"

#include "core.h"
int INCOMPLETE_VALUES[9][9] = {
       //0, 1  2  3  4  5  6  7  8
        {0, 9, 8, 5, 3, 7, 4, 1, 2},// 0
        {1, 4, 0, 2, 6, 8, 9, 5, 3},// 1
        {0, 2, 5, 1, 4, 0, 8, 7, 0},// 2
        {2, 5, 3, 8, 0, 1, 6, 0, 9},// 3
        {0, 6, 1, 0, 9, 4, 5, 0, 8},// 4
        {0, 8, 0, 6, 0, 2, 0, 0, 7},// 5
        {0, 1, 0, 0, 8, 3, 0, 0, 4},// 6
        {9, 0, 6, 4, 2, 5, 3, 0, 0},// 7
        {8, 3, 4, 0, 1, 0, 2, 0, 0} // 8
    };

int SOLVED_VALUES[9][9]= {
        {6, 9, 8, 5, 3, 7, 4, 1, 2},
        {1, 4, 7, 2, 6, 8, 9, 5, 3},
        {3, 2, 5, 1, 4, 9, 8, 7, 6},
        {2, 5, 3, 8, 7, 1, 6, 4, 9},
        {7, 6, 1, 3, 9, 4, 5, 2, 8},
        {4, 8, 9, 6, 5, 2, 1, 3, 7},
        {5, 1, 2, 9, 8, 3, 7, 6, 4},
        {9, 7, 6, 4, 2, 5, 3, 8, 1},
        {8, 3, 4, 7, 1, 6, 2, 9, 5}
    };

int INVALID_VALUES[9][9]= {
        {6, 0, 1, 5, 3, 7, 4, 1, 2},//THE 1
        {1, 4, 7, 2, 6, 8, 9, 5, 3},
        {3, 2, 5, 1, 4, 9, 8, 7, 6},
        {2, 5, 3, 8, 0, 1, 6, 4, 0},
        {7, 6, 1, 3, 9, 4, 5, 2, 8},
        {4, 8, 9, 6, 5, 2, 1, 3, 7},
        {5, 1, 2, 5, 8, 3, 7, 6, 4},//THE 5
        {9, 7, 6, 4, 2, 5, 3, 8, 1},
        {8, 3, 4, 7, 1, 0, 2, 9, 5}
    };

void init_test_board(Board * b, int values[9][9])
{
    
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            Cell c;
            c.visited = TRUE;
            c.value = values[i][j];
            b->sudoku_board[i][j] = c;
        }
    }
}

static char * test_check_board()
{
    mu_begin_case("check_board",-1);
    mu_assert_i("Checking on null board",0 ,check_board(NULL));
    Board b;
    init_test_board(&b, SOLVED_VALUES);
    mu_assert_i("check_board on solved board", 1, check_board(&b)); 

    init_test_board(&b, INCOMPLETE_VALUES);
    mu_assert_i("check_board on incomplete board", 0, check_board(&b));

    init_test_board(&b, INVALID_VALUES);
    mu_assert_i("Checking invalid solution", 0, check_board(&b));
    mu_end_case("check_board");
    return 0 ;
}

static char * test_solve_board()
{
    mu_begin_case("solve_board",-1);
    Board b;
    Board b_unsolvable;
    mu_assert_i("testing null board", -1, solve_board(NULL));
    init_test_board(&b, INCOMPLETE_VALUES);
    init_test_board(&b_unsolvable, INVALID_VALUES);
    mu_assert_i("testing invalid incomplete board", 0, solve_board(&b_unsolvable));
    mu_assert_i("testing incompleted valid board", 1, solve_board(&b));
    int coords[29][2] = {
        {0,0},{0,6},{1,2},{2,0},
        {2,5},{2,8},{3,4},{3,7},
        {4,0},{4,3},{4,7},{5,0},
        {5,2},{5,4},{5,6},{5,7},
        {6,0},{6,2},{6,3},{6,6},
        {6,7},{7,0},{7,1},{7,7},
        {7,8},{8,3},{8,5},{8,7},
        {8,8},
    };
    for (int i = 0; i < sizeof(coords)/(2* sizeof(0)); i++)
    {
        int row = coords[i][0];
        int col = coords[i][1];
        char buffer[100];
        snprintf(buffer, 100,"testing that solution matches at row = %d, col = %d", row, col);
        mu_assert_i(buffer, SOLVED_VALUES[row][col], b.sudoku_board[row][col].value);

    }
    mu_end_case("solve_board");
    return 0;
}

static char * test_find_unassigned()
{
    mu_begin_case("find_unassigned",-1);

    int row;
    int col;
    row = 0;
    col = 0;
    
    mu_assert_i("Checking with null board,", 0, find_unassigned(NULL,&row, &col));
    mu_assert_i("Checking -1 returned for row", -1, row);
    mu_assert_i("Checking -1 returned for col", -1, col);

    Board b_solved;
    init_test_board(&b_solved,SOLVED_VALUES);


    for(int i = 0;i<=8;i++)
    {
        row++;
        col++;
        mu_assert_i("Checking on solved board", 0 ,find_unassigned(&b_solved, &row, &col));
    }
    
    Board b;
    init_test_board(&b,INCOMPLETE_VALUES);
    
    int return_values[][3]  = {
        // return value, row return value, col return value
        {1, 0, 0},
        {1, 1, 2},
        {1, 2, 0},
        {1, 2, 5},
        {1, 2, 8},
    };
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        int return_value = return_values[i][0];
        int unassigned_row = return_values[i][1];
        int unassigned_col = return_values[i][2];
        
        mu_assert_i("Checking return value", return_value ,find_unassigned(&b, &row, &col));
        mu_assert_i("Checking correct value for row", unassigned_row, row);
        mu_assert_i("Checking correct value for col", unassigned_col, col);
        printf("\n");

        //we need to set the board so that the next one could potentially pass, ie setting row, col in the board to be value that is assigned
        b.sudoku_board[unassigned_row][unassigned_col].value = SOLVED_VALUES[unassigned_row][unassigned_col];

    }
    mu_end_case("find_unassigned");
    return 0;
}

static char * test_used_in_row()
{
    mu_begin_case("used_in_row",-1);
    Board b;

    init_test_board(&b,INCOMPLETE_VALUES);
    int valid_int =0;
    mu_assert_i("Testing null board", -1, used_in_row(NULL, &valid_int, 0));
    mu_assert_i("Testing null row pointer", -1, used_in_row(&b, NULL, 0));


    int mthd_values[][3] = {
        //row, value, return value
        {0,1,1},
        {0,6,0},
        {2,9,0},
        {8,3,1},

        {8,5,0},
        {7,4,1},
        {7,8,0},
        {6,6,0},

        {8,9,0},
    };
    for (int i = 0; i <9; i++)
    {
        int row = mthd_values[i][0];
        int val = mthd_values[i][1];
        int return_value = mthd_values[i][2];
        char buffer[100];
        snprintf(buffer, 100, "testing if value %d in row %d", val, row);
        mu_assert_i(buffer, return_value, used_in_row(&b, &row, val));//first row
    }
    mu_end_case("used_in_row");
    return 0;
}

static char * test_used_in_col()
{
    mu_begin_case("used_in_col",-1);
    Board b;
    init_test_board(&b,INCOMPLETE_VALUES);

    int valid_int = 0;
    mu_assert_i("Testing with null board", -1, used_in_col(NULL, &valid_int, 1));
    mu_assert_i("Testing with null col pointer", -1, used_in_col(&b, NULL, 1));

    int mthd_args[][2] = {{0,1}, {0,6}, {3,4}, {8,7}, {8,5}};
    int return_values [] = {1,0,1,1,0};
    for(int i = 0; i<= 4;i++)
    {
        int arg1 = mthd_args[i][0];
        int arg2 = mthd_args[i][1];

        mu_assert_i("Used in column", return_values[i], used_in_col(&b, &arg1, arg2)); 
    }
    
    mu_end_case("used_in_col");
    return 0;
}

static char * test_used_in_box()
{
    mu_begin_case("used_in_box",-1);
    Board b;
    init_test_board(&b,INCOMPLETE_VALUES);
    mu_assert_i("testing null board", -1, used_in_box(NULL,0,0,0));
    mu_assert_i("testing bad coords row (8), col (8)", -1, used_in_box(&b,8,8,0));
    mu_assert_i("testing bad coords row (7), col (7)", -1, used_in_box(&b,7,7,0));

    int mthd_args[][4] ={
        // boxStartRow, boxStartCol, num, return value
        {-1, 0, 0, -1},
        {9, 0, 0, -1},
        {0,-1, 0, -1},
        {0, 9, 0, -1},

        {0, 0, -1, -1},
        {0, 0, 6, 0},
        {3, 6, 6, 1},
        {3, 6, 1, 0},

        {6, 6, 1, 0},
        {6, 6, 2, 1},
    };
    for (int i = 0; i < 10; i++)
    {
        char buffer[100];
        int row = mthd_args[i][0];
        int col = mthd_args[i][1];
        int num = mthd_args[i][2];
        int return_value = mthd_args[i][3];
        int output = snprintf(buffer,100,"testing start row (%d), start col (%d), value (%d)", row, col, num);
        mu_assert_i(buffer, return_value, used_in_box(&b, row, col, num));
    }


    mu_end_case("used_in_box");
    return 0;
}

static char * test_is_safe()
{
    mu_begin_case("is_safe", -1);
    Board b;
    init_test_board(&b,INVALID_VALUES);
    int row = 0;
    int col = 0;
    mu_assert_i("testing with null Board", -1, is_safe(NULL,&col, &row,0));
    mu_assert_i("testing with null col pointer", -1, is_safe(&b, NULL, &row,0));
    mu_assert_i("testing with null row pointer", -1, is_safe(&b, &col, NULL, 0));
    int mthd_args[][4] = {
        // is in the format of col, row, num, expected return value
        {0,0,1,0},
        {0,0,6,1},
        {4,3,6,0},
        {4,3,7,1},

        {5,2,4,0},
        {5,2,9,1},
        {8,8,5,1},
        {8,8,4,0},

        {8,8,3,0},
        {2,6,9,0},
        {7,8,9,1},
    };
    for (int i = 0; i < 11; i++)
    {
        col = mthd_args[i][0];
        row = mthd_args[i][1];
        int val_to_check = mthd_args[i][2];
        int return_value = mthd_args[i][3];
        char buffer[100];
        snprintf(buffer, 100, "testing placable num (%d), row (%d) col (%d)", val_to_check, row, col);
        mu_assert_i(buffer, return_value, is_safe(&b, &col, &row, val_to_check));
    }

    mu_end_case("is_safe");
    return 0;
}

static char * test_dict_add()
{
    mu_begin_case("dict_add",-1);
    SimpleDict sd;
    dict_clear(&sd);
    int valid_values[3] = {0,4,8};
    int invalid_values[2] = {-1,BOARD_WIDTH+1};
    for(int i = 0; i<=2;i++)// loop through valid_values
    {
        int cell_num = valid_values[i];
        mu_assert_i("Returned TRUE", 1, dict_add(&sd,cell_num));
        mu_assert_i("Correctly placed value in dict", 1, sd.is_chosen[cell_num]);
    }
    for(int i = 0; i<=1;i++)
    {
        int cell_num = invalid_values[i];
        mu_assert_i("Returned FALSE", 0, dict_add(&sd, cell_num));
    }
    mu_end_case("dict_add");
    return 0;
}

static char * test_dict_clear()
{
    mu_begin_case("dict_clear",-1);
    SimpleDict sd;
    dict_clear(&sd);
    for (int cell_num = 0; cell_num < sizeof(sd.is_chosen)/sizeof(sd.is_chosen[0]); cell_num++)
    {
        mu_assert_i("Assert dict cleared",0,sd.is_chosen[cell_num]);
    }
    return 0;
}
static char * test_dict_contains()
{
    mu_begin_case("dict_contains",-1);
    SimpleDict sd;
    dict_clear(&sd);
    int chosen_values[3] = {0,4,8};
    sd.is_chosen[0] =1;
    sd.is_chosen[4] =1;
    sd.is_chosen[8] =1;

    int unchosen_values[5] = {1,2,6,-1,10};

    for(int i = 0; i<(sizeof(chosen_values)/sizeof(0));i++)
    {
        mu_assert_i("Returned TRUE", 1, dict_contains(&sd,chosen_values[i]));
    }

    for(int i = 0; i<(sizeof(unchosen_values)/sizeof(0));i++)
    {
        mu_assert_i("Returned FALSE", 0, dict_contains(&sd,unchosen_values[i]));
    }

    mu_end_case("dict_contains");
    return 0;
}

static char * test_read_board()
{
    mu_begin_case("read_board", -1);
    mu_end_case("read_board");
    mu_assert_i("Null board and Null File should return FALSE",0,read_board(NULL,NULL));
    {
        Board b;
        char contents[] = "";
        FILE * fp = fmemopen(contents, strlen(contents),"r");
        mu_assert_i("Null File should return FALSE",0,read_board(&b,NULL));
        mu_assert_i("Null board should return FALSE",0,read_board(NULL,fp));
        fclose(fp);
    }
    {    
        char contents[] = "698537412\n147268953\n325149876\n253871649\n761394528\n489652137\n512983764\n976425381\n834716295";
        FILE * fp = fmemopen(contents, strlen(contents),"r");
        Board b;
        mu_assert_i("read_board(&b, fp should return TRUE",1,read_board(&b,fp));
        int coords[29][2] = {
            {0,0},{0,6},{1,2},{2,0},
            {2,5},{2,8},{3,4},{3,7},
            {4,0},{4,3},{4,7},{5,0},
            {5,2},{5,4},{5,6},{5,7},
            {6,0},{6,2},{6,3},{6,6},
            {6,7},{7,0},{7,1},{7,7},
            {7,8},{8,3},{8,5},{8,7},
            {8,8},
        }; 
        for (int i = 0; i < sizeof(coords)/(2* sizeof(0)); i++)
    {
        int row = coords[i][0];
        int col = coords[i][1];
        char buffer[100];
        snprintf(buffer, 100,"testing that value at row = %d, col = %d is %d", row, col, SOLVED_VALUES[row][col]);
        mu_assert_i(buffer, SOLVED_VALUES[row][col], b.sudoku_board[row][col].value);

    } 

    }    


    return 0;
}

static char * test_write_board()
{
    mu_begin_case("write_board",-1);
    mu_end_case("write_board");
    return 0;
}
static char * dict_tests()
{
    test_dict_clear();
    test_dict_add();
    test_dict_contains();
    return 0;
}

static char * board_tests()
{
    test_check_board();
    test_find_unassigned();
    test_used_in_row();
    test_used_in_col();
    test_used_in_box();
    test_is_safe();
    test_solve_board();
    return 0;
}
static char * io_tests()
{
    test_read_board();
    test_write_board();
    return 0;
}
static char * all_tests() 
{
    board_tests();
    dict_tests();
    return 0;
}

static void print_test_usage()
{
    printf("To run all tests: ./test\n");
    printf("To run board tests: ./test  -board\n");
    printf("To run dict tests: ./test -dict\n");
}
#ifdef TEST
/*
To run all:         ./test         
To run board tests: ./test -board  
To run dict tests:  ./test -dict
To run IO tests: ./test -io 
*/
int main(int argc, char **argv) 
{
    if(argc == 1)
    {
        mu_run(all_tests);
    }
    else if ( argc == 2)
    {
        if (strcmp(argv[1], "-board") == 0 )
        {
            mu_run(board_tests);
        }
        else if (strcmp(argv[1], "-dict") == 0)
        {
            mu_run(dict_tests);
        }
        else if (strcmp(argv[1], "-io") == 0)
        {
            mu_run(io_tests);
        }
        else
        {
            print_test_usage();
        }
    }
    else
    {
        print_test_usage();
    }
    return 0;
}
#endif
