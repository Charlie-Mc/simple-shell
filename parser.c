//
// Created by connor on 31/01/23.
//

#include "parser.h"

// Parses a line of user input. 
// Returns false if execution of the shell should terminate after this line, or true if execution should continue.
char** parse(char* input) {

    // Print user prompt
    printf("simpsh> ");

    // If reading an input line fails, terminate shell
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        printf("\n");
        return NULL;
    }

    // Create array of tokens
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));

    // Index into array of tokens
    int i = 0;

    // Take first keyword off of input line, keywords are defined by words before the parsing characters (2nd input to fgets)
    char* token = strtok(input, DELIMITERS);

    // If token is null value ignore parsing
    while (token != NULL) {
        printf("%s\n", token);
        tokens[i] = token;

        // If the token is the exit command, terminate shell
        if (strcmp(token, "exit") == 0) {
            free(tokens);
            return NULL;
        }

        // Otherwise get next keyword and repeat
        token = strtok(NULL, DELIMITERS);
    }
    return tokens;
}
