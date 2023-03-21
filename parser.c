//
// Created by connor on 31/01/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"
#include "alias.h"

// Parses a command line.
// Parameter is mutated. If subsequent access to original command line is required make sure to pass a copy to this function.
// Returns NULL if execution of the shell is to end after this line, otherwise an array of strings representing the tokens of the line read.
char** parse(char* input, List aliases) {
    char* incpy = strdup(input);
    // Create array of tokens
    char** tokens = malloc(MAX_TOKENS * sizeof(char *));

    // Take first keyword off of input line, keywords are defined by words before the parsing characters (2nd input to fgets)
    char *token = strtok(input, DELIMITERS);

    // If token is NULL ignore parsing
    if (token != NULL) {
        // if token is name of stored alias
        bool is_alias = check_alias(token, aliases);
        bool aliased = is_alias;
        while (is_alias) {
            // execute alias using current token as the name
            tokens = parse_alias(token, incpy, tokens, aliases);
            // command was exit
            if (tokens == NULL)
                return NULL;

            token = strtok(strdup(tokens[0]), DELIMITERS);
            if (token == NULL)
                break;
            is_alias = check_alias(token, aliases);
        }
        if (aliased)
            return tokens;
    }
}


// Gets a command line from user
// Stores fetched line in input parameter
// Returns 0 if line was fetched OK, 1 if line was too long, and 2 if <ctrl-D> was pressed
int get_input(char* input, List history) {
    // Print user prompt
    printf("simpsh> ");

    // If reading an input line fails, terminate shell
    if (fgets(input, MAX_INPUT + 2, stdin) == NULL) {
        printf("\n");
        return 2;
    }

    // Check if line is too long (>512 characters)
    int lastCharIndex = strlen(input) - 1;
    if (input[lastCharIndex] != '\n') {
        fprintf(stderr, "Error: Maximum line length exceeded. Please ensure your command is less than 512 characters long.\n");
        while (getchar() != '\n'); // Clears the input buffer
        return 1;
    }

    // If command is not a history invocation, add to history
    if (input[0] != '\0' && input[0] != '!' && input[0] != '\n')
        push(history, input);

    return 0;
}

// Gets a command line from user and parses into tokens
// Returns NULL if execution of the shell is to end after this line, otherwise an array of strings representing the tokens of the line read.
char** readAndParseInput(char* input, List history, List aliases) {
    int inputStatus = get_input(input, history);
    if (inputStatus == 0)
        return parse(input, aliases);
    else if (inputStatus == 2)
        return NULL; 
    else {
        char** tokens = malloc(sizeof(char*));
        tokens[0] = NULL;
        return tokens;
    } 
}
