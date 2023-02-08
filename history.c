//
// Created by conno on 07/02/2023.
//


#include "history.h"

char* toStr(char** val) {
    char* result;
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

void revArr(char** src) {
    char* temp = *src;
    int i = 0;

    while (strcmp(*src, "") != 0) {
        src++;
        i++;
    }

    char** des = malloc(sizeof(char*) * i);
    for (int j = 0; j < i; j++) {
        *des = *src;
        des++;
        src--;
    }
    src = des;
    free(des);
}

int checkHist(char** tokens, char** history) {
    if (strcmp(tokens[0], "!!") == 0) {
        if (strcmp(history[0], "") == 0) {
            printf("\nNo Command History Found!\n");
            return 1;
        } else {
            tokens[0] = *history;
        }
        return 1;
    } else if (strcmp(tokens[0], "history") == 0) {
        printHistory(history);
        push(history, tokens[0]);
        return 1;
    } else if (strcmp(tokens[0], "ls") == 0) {
        push(history, tokens[0]);
        printf("ls Tried");
    }
    push(history, tokens[0]);
    return 0;
}

void printHistory(char** history) {
    char* latestCall = *history;
    int i = 0;
    if (strcmp(*history, "") == 0) {
        printf("No Command History Found!\n");
        return;
    }
    while (strcmp(*history, "") != 0) {
        history++;
        i++;
    }
    history++;
    *history = malloc(sizeof(char *));
    history--;
    history--;
    while (i != 1) {
        printf("%d:  %s\n", i, *history);
        history--;
        i--;
    }
    printf("%d:  %s\n", i, *history);
}