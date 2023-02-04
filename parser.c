//
// Created by connor on 31/01/23.
//

#include "parser.h"

bool parse() {

    // Define input buffer
    char input[MAX_INPUT];

    // Print user prompt
    printf("simpsh 8---->");

    // Get user input and store it into a character pointer that then pushes into the input buffer declared on line 8
    char* inputPtr = fgets(input, MAX_INPUT, stdin);

    // If input starts with a NULL value, quit terminal
    if (inputPtr == NULL) {
        printf("\n");
        return false;
    }

    // Take first keyword off of input line, keywords are defined by words before the parsing characters (2nd input to fgets)
    char* token = strtok(input, DELIMITERS);

    // If token is null value ignore parsing
    while (token != NULL) {
        printf("%s\n", token);

        // If the token is the exit command, terminate shell
        if (strcmp(token, "exit") == 0)
            return false;

        // Otherwise get next keyword and repeat
        token = strtok(NULL, DELIMITERS);

    }
    return true;
}
