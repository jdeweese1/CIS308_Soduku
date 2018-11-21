//
//  main.c 
//  Week 10 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include "core.h"

#ifndef TEST
int main(int argc, const char * argv[]) {
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
#endif
