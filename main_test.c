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
        {0, 9, 8, 5, 3, 7, 0, 1, 2},
        {1, 4, 0, 2, 6, 8, 9, 5, 3},
        {0, 2, 5, 1, 4, 0, 8, 7, 0},
        {2, 5, 3, 8, 0, 1, 6, 0, 9},
        {0, 6, 1, 0, 9, 4, 5, 0, 8},
        {0, 8, 0, 6, 0, 2, 0, 0, 7},
        {0, 1, 0, 0, 8, 3, 0, 0, 4},
        {0, 0, 6, 4, 2, 5, 3, 0, 0},
        {8, 3, 4, 0, 1, 0, 2, 0, 0}
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


void init_test_board(Board * b, int values[9][9])
{
    
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            Cell c;
            c.visited = TRUE;
            c.value = values[i][j];
            b->suduko_board[i][j] = c;
        }
    }
}
static char * test_check_board()
{
    mu_begin_case("check_board");
    mu_assert_i("checking for null",0 ,check_board(NULL));
    Board b;
    init_test_board(&b, SOLVED_VALUES);
    mu_assert_i("check_board 1", 1, check_board(&b)); 
    init_test_board(&b, INCOMPLETE_VALUES);
    mu_assert_i("checking an incopmlete board",0, check_board(&b));
    mu_end_case("check_board");
    return 0 ;
}

static char * test_solve_board()
{
    mu_begin_case("solve_board");
    Board b;
    init_test_board(&b,INCOMPLETE_VALUES);
    mu_assert_i("foobar",SOLVED_VALUES[0][0],b.suduko_board[0][0].value);//add for loop
    mu_end_case("solve_board");
    return 0;
}

static char * all_tests() {
    test_check_board();
    test_solve_board();
    return 0;
}

#ifdef TEST
int main(int argc, char **argv) {
    mu_run(all_tests);
    return 0;
}
#endif
