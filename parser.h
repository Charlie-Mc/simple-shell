/*
    This is the header file for the parsing functions

    These functions take the input from the user and then determine what functions to next call based on the input given
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 512
#define DELIMITERS " \t\n|><&;"

bool parse();
