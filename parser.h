/*
    This is the header file for the parsing functions

    These functions take the input from the user and then determine what functions to next call based on the input given
 */

#define MAX_INPUT 512
#define MAX_TOKENS 50
#define MAX_CWD 256

//debug mode as recommended by andrew, to remove this change DEBUG variable in parser.h to 0
#define DEBUG 1
#define DELIMITERS " \t\n|><&;"

char** parse(char* input);
