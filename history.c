//
// Created by conno on 07/02/2023.
//


#include "history.h"

char* toStr(char** val) {
    char* result = malloc(sizeof(char*));
    while (*val != NULL) {
        result = strcat(result, *val);
        val++;
    }
    return result;
}

void push(char** des, char** value) {
    char *val = toStr(value);
    char* temp  = *des;
    char* temp2;
    *des = val;
    des++;
    while (strcmp(temp, "") != 0) {
        temp2 = *des;
        *des = temp;
        temp = temp2;
        des++;
    }
}


int checkHist(bool prevCalled, char** tokens, char** history) {
    if (strcmp(tokens[0], "!!") == 0) {
        if (strcmp(history[0], "") == 0) {
            printf("\nNo Command History Found!\n");
            return 2;
        } else {
            tokens[0] = *history;
        }
        return 0;
    } else if (strcmp(tokens[0], "history") == 0) {
        printHistory(history);
        if (!prevCalled)
            push(history, tokens);
        return 2;
    } else if (strcmp(tokens[0], "ls") == 0) {
        if (!prevCalled)
            push(history, tokens);
        printf("ls Tried\n");
        return 2;
    }
    push(history, tokens);
    return 1;
}

void printHistory(char** history) {
    if (*history == NULL) {
        *history = malloc(sizeof(char*));
    }
    int i = 0;
    if (strcmp(*history, "") == 0) {
        printf("No Command History Found!\n");
        return;
    }
    while (strcmp(*history, "") != 0) {
        history++;
        i++;
        if (*history == NULL) *history = malloc(sizeof(char*));
    }
    history--;
    while (i != 1) {
        printf("%d:  %s\n", i, *history);
        history--;
        i--;
    }
    printf("%d:  %s\n", i, *history);
}