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

int times_two(int x) {
    return x * 2;
}

int add_three(int x) {
    return x + 3;
}

int make_zero(int x) {
    return 0;
}

char next_char(char c) {
    return ++c;
}

char to_lower(char c) {
    if (c == ' ') { return c; }
    return c + 32;
}

static char * test_apply_twice() {
    mu_begin_case("apply_twice", 5);

    {
        int result = apply_twice(0, NULL);
        mu_assert_i("Assert apply_twice(0, NULL) returns 0", 0, result);
    }

    {
        int result = apply_twice(5, NULL);
        mu_assert_i("Assert apply_twice(5, NULL) returns 5", 5, result);
    }

    {
        int result = apply_twice(5, times_two);
        mu_assert_i("Assert apply_twice(5, times_two) returns 20", 20, result);
    }

    {
        int result = apply_twice(7, add_three);
        mu_assert_i("Assert apply_twice(7, add_three) returns 13", 13, result);
    }

    {
        int result = apply_twice(4, make_zero);
        mu_assert_i("Assert apply_twice(4, make_zero) returns 0", 0, result);
    }

    mu_end_case("apply_twice");
    return 0;
}

static char * test_change_string() {
    mu_begin_case("change_string", 3);

    {
        char s[] = "Hello World";
        change_string(s, NULL);
        mu_assert_s("Verify that change_string(s, NULL) does nothing", "Hello World", s);
    }

    {
        char s[] = "Hello World";
        change_string(s, next_char);
        mu_assert_s("Verify that change_string(s, next_char) goes to the next char", "Ifmmp!Xpsme", s);
    }

    {
        char s[] = "HELLO WORLD";
        change_string(s, to_lower);
        mu_assert_s("Verify that change_string(s, to_lower) makes the string lowercase", "hello world", s);
    }

    mu_end_case("change_string");
    return 0;
}

static char * all_tests() {
    test_apply_twice();
    test_change_string();
    return 0;
}

#ifdef TEST
int main(int argc, char **argv) {
    mu_run(all_tests);
    return 0;
}
#endif

