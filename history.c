//
// Created by conno on 07/02/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "parser.h"
#include "history.h"

int checkHist(char*** tokensPtr, List history, List aliases) {
    char** tokens = *tokensPtr;
    if (strcmp(tokens[0], "!!") == 0) {
        if (tokens[1] != NULL) {
            printf("!!: too many parameters\n");
            return 2;
        }
        if (peek(history) == NULL) {
            printf("No command history found!\n");
            return 2;
        }
        if (strcmp(peek(history), "") == 0) {
            printf("No command history found!\n");
            return 2;
        }
        free(*tokensPtr);
        *tokensPtr = parse(strdup(get_at(history, 0)), aliases);
        return 0;
    } else if (tokens[0][0] == '!' && tokens[0][1] != '\0') {
        if (tokens[1] != NULL) {
            printf("%s: too many parameters\n", tokens[0]);
            return 2;
        }
        errno = 0;
        char* firstNonNumber;
        long lVal = strtol(&tokens[0][1], &firstNonNumber, 10);
        int val;
        if (errno != 0 || firstNonNumber == &tokens[0][1]) {
            printf("%s: invalid history position\n", tokens[0]);
            return 2;
        } else if (lVal < -20 || lVal > 20) {
            printf("%s: history position out of bounds (-20 - 20)\n", tokens[0]);
            return 2;
        } else
            val = (int) lVal;

        // check for valid commands at location given
        if (size(history) < abs(val)) {
            printf("No command history found at location given\n");
            return 2;
        }
        // parse command at location given
        else {
            if (val < 0) {
                free(*tokensPtr);
                *tokensPtr = parse(strdup(get_at(history, abs(val)-1)), aliases);
            } else if (val > 0) {
                free(*tokensPtr);
                *tokensPtr = parse(strdup(get_at(history, size(history) - val)), aliases);
            } else
                return 2;
        }
        return 0;
    } else if (strcmp(tokens[0], "history") == 0) {
        if (tokens[1] != NULL)
            printf("history: too many parameters\n");
        else if (size(history) == 1)
            printf("history: no history exists\n");
        else
            printHistory(history, true);
        return 2;
    }
    return 1;
}

void printHistory(List history, bool prevCalled) {
    int j = 1;
    for (int i = size(history); i > (prevCalled ? 0 : 1); --i) {
        printf("%d:\t%s", j, get_at(history, i - 1));
        j++;
    }
}