//
// Created by connor on 31/01/23.
//

#include "parser.h"

// Parses a line of user input. 
// Returns NULL if execution of the shell is to end after this line, otherwise an array of strings representing the tokens of the line read.
char** parse(char* input) {

    // Create array of tokens
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));

    // Index into array of tokens
    int i = 0;

    // Take first keyword off of input line, keywords are defined by words before the parsing characters (2nd input to fgets)
    char* token = strtok(input, DELIMITERS);

    // If token is null value ignore parsing
    while (token != NULL) {
        // printf("%s\n", token);
        tokens[i++] = token;

        // If the token is the exit command, terminate shell
        if (strcmp(token, "exit") == 0) {
            free(tokens);
            return NULL;
        }

        // Otherwise get next keyword and repeat
        token = strtok(NULL, DELIMITERS);
    }
    tokens[i] = NULL;
    return tokens;
}

void get_input(char* input) {
    // Print user prompt
    printf("simpsh> ");

    // If reading an input line fails, terminate shell
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        printf("\n");
    }
}
