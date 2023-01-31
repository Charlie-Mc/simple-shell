//
// Created by connor on 31/01/23.
//

#include "parsing.h"

bool parse() {
    char input[MAX_INPUT];
    bool parsingLine = true;

    printf("simpsh> ");

    char* inputPtr = fgets(input, MAX_INPUT, stdin);
    if (inputPtr == NULL) {
        printf("\n");
        parsingLine = false;
        return false;
    }

    char* token = strtok(input, " \t\n|><&;");
    if (token == NULL)
        parsingLine = false;


    while (parsingLine) {
        printf("%s\n", token);
        if (strcmp(token, "exit") == 0)
            return parsingLine = false;
        token = strtok(NULL, " \t\n|><&;");
        if (token == NULL)
            parsingLine = false;
    }
    return true;
}

