//
// Created by conno on 07/02/2023.
//

#include <math.h>

#include "history.h"
#include "parser.h"

char* toStr(char** val) {
    char* result = malloc(sizeof(char*));
    while (*val != NULL) {
        result = strcat(result, *val);
        result = strcat(result, " ");
        val++;
    }
    return result;
}

int eval(char** tokens) {
    int val;
    // get input value from input token
    if (tokens[0][1] == '-') {
        val = tokens[0][2] - 48;
        if (tokens[0][3] != '\0')
            val = (val * 10) + (tokens[0][3] - 48);

        if (tokens[0][4] != '\0') {
            printf("\nLocation Invalid!\n");
            return 0;
        }
        if (val == 0 || val < -20) {
            printf("\nLocation Invalid!\n");
            return 0;
        }
        return -val;
    }
    val = tokens[0][1] - 48;
    if (tokens[0][2] != '\0')
        val = (val * 10) + (tokens[0][2] - 48);

    if (tokens[0][3] != '\0') {
        printf("\nLocation Invalid!\n");
        return 0;
    }
    if (val == 0 || val > 20) {
        printf("\nLocation Invalid!\n");
        return 0;
    }
    return val;
}

int checkHist(bool prevCalled, char** tokens, List history) {
    if (strcmp(tokens[0], "!!") == 0) {
        if (peek(history) == NULL) {
            printf("\nNo Command History Found!\n");
            return 2;
        }
        if (strcmp(peek(history), "") == 0) {
            printf("\nNo Command History Found!\n");
            return 2;
        } else {
            free(tokens);
            tokens = parse(get_at(history, 0));
        }
        return 0;
    } else if (*tokens[0] == '!') {
        int val = eval(tokens);

        // check for valid commands at location given
        if (size(history) < abs(val)) {
            printf("\nNo Command History Found At Location Given\n");
            return 2;
        }
        // parse command at location given
        else {
            free(tokens);
            if (val < 0)
                tokens = parse(get_at(history, abs(val)-1));
            else if (val > 0)
                tokens = parse(get_at(history, size(history) - val));
            else
                return 2;
        }
        return 0;
    } else if (strcmp(tokens[0], "history") == 0) {
        if (!prevCalled)
            push(history, toStr(tokens));
        printHistory(history);
        return 2;
    }
    if (!prevCalled)
        push(history, toStr(tokens));
    return 1;
}

void printHistory(List history) {
    int j = 1;
    for (int i = size(history); i > 0; --i) {
        printf("%d:  %s\n", j, get_at(history, i - 1));
        j++;
    }
}