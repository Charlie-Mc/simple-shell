//
// Created by connor on 31/01/23.
//

#include "parser.h"

bool parse() {

    // Define input buffer
    char input[MAX_INPUT];

    // print user prompt
    printf("simpsh 8---->");

    // get user input and store it into a character pointer that then pushes into the input buffer declared on line 8
    char* inputPtr = fgets(input, MAX_INPUT, stdin);

    // if input starts with a NULL value, quit terminal
    if (inputPtr == NULL) {
        printf("\n");
        return false;
    }

    // take first keyword off of input line, keywords are defined by words before the parsing characters (2nd input to fgets)
    char* token = strtok(input, " \t\n|><&;");

    // if there are viable words, find what to do with them
    while (token != NULL) {
        printf("%s\n", token);

        // if the word is the exit command, terminate shell
        if (strcmp(token, "exit") == 0)
            return false;

        // get next keyword
        token = strtok(NULL, " \t\n|><&;");

    }
    return true;
}
