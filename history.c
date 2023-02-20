//
// Created by conno on 07/02/2023.
//


#include "history.h"
#include "parser.h"

char* toStr(char** val) {
    char* result = malloc(sizeof(char*));
    while (*val != NULL) {
        result = strcat(result, *val);
        val++;
    }
    return result;
}

int checkHist(bool prevCalled, char** tokens, List history) {
    if (strcmp(tokens[0], "!!") == 0) {
        if (strcmp(peek(history), "") == 0) {
            printf("\nNo Command History Found!\n");
            return 2;
        } else {
            free(tokens);
            tokens = parse(get_at(history, size(history)-1));
        }
        return 0;
    } else if (strcmp(tokens[0], "history") == 0) {
        printHistory(history);
        if (!prevCalled)
            push(history, toStr(tokens));
        return 2;
    }
    if (!prevCalled)
        push(history, toStr(tokens));
    return 1;
}

void printHistory(List history) {
    for (int i = size(history); i > 0; --i)
        printf("%d:  %s\n", i, get_at(history, i-1));
}