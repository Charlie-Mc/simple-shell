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
    // Create array of tokens
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));
    // Index into array of tokens
    char* token = strtok(input, DELIMITERS);
    int* i;
    *i = 0;

    if (token != NULL) {
        // If the token is the exit command, terminate shell
        if (strcmp(token, "exit") == 0) {
            free(tokens);
            return NULL;
        }
    }


    // If token is null value ignore parsing
    while (token != NULL) {
        if (DEBUG)
            printf("%s\n", token);

        if (check_alias(token, aliases)) {
            if (!parse_alias(i, tokens, token, aliases))
                return NULL;
        } else {

        }
        tokens[(*i)++] = token;
        if (strcmp(token, "unalias") == 0) {
            token = strtok(NULL, DELIMITERS);
            if (token == NULL) {
                printf("unalias: no parameter given\n");
                break;
            }
            unalias(token, aliases);
            break;
        }

        // Otherwise get next keyword and repeat
        token = strtok(NULL, DELIMITERS);
    }
    tokens[*i] = NULL;
    return tokens;
    // commit
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
