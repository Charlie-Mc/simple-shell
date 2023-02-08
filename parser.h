/*
    This is the header file for the parsing functions

    These functions take the input from the user and then determine what functions to next call based on the input given
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"

#define MAX_INPUT 512
#define MAX_TOKENS 50
#define HISTORY_SIZE 20
#define DELIMITERS " \t\n|><&;"

char** parse(char* input);
