//
// Created by connor on 11/03/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"
#include "alias.h"

void alias(char** tokens, List aliases, char* input) {

    char* token = strtok(strdup(input), DELIMITERS);
    token = strtok(NULL, DELIMITERS);

    if (token == NULL) {
        print_aliases(aliases);
        return;
    }

    int i = 0;

    char* name = malloc(sizeof(token) + 2);
    name = strdup(token);
    bool override = contains_alias(aliases, name);
    if (override) {
        printf("alias <%s> already exists, overriding\n", name);
        remove_at(aliases, index_of_alias(aliases,name));
    }

    if (size(aliases) >= MAX_ALIASES && !override) {
        printf("max number of aliases reached: %d", MAX_ALIASES);
        return;
    }

    strtok(input, DELIMITERS);
    strtok(NULL, DELIMITERS);
    token = strtok(NULL, "\n");
    if (token == NULL){
        printf("alias: too few parameters\n");
        return;
    }


    char* alias = malloc(128 * sizeof(char));
    alias = strdup(name);
    strcat(alias, ",");
    strcat(alias, strdup(token));
    strcat(alias, "\n");
    add(aliases, alias);
}

void unalias(char* name, List aliases) {
    if (size(aliases) == 0)
        printf("unaliase: no aliases defined\n");
    else if (remove_at(aliases, index_of_alias(aliases, name)) == NULL)
        printf("unalias: no alias <%s> found\n", name);
}

char** parse_alias(char* name, char* input, char** tokens, List aliases) {
    char* token = strtok(strdup(get_at(aliases, index_of_alias(aliases, name))), ",");
    int i = 0;

    token = strtok(NULL, DELIMITERS);

    if (strcmp(token, "exit") == 0) {
        free(tokens);
        return NULL;
    }

    while (token != NULL) {
        if (DEBUG)
            printf("token = %s\n", token);
        tokens[i++] = token;


        token = strtok(NULL, DELIMITERS);
    }

    token = strtok(input, DELIMITERS);
    token = strtok(NULL,  DELIMITERS);

    while (token != NULL) {
        if (DEBUG)
            printf("token = %s\n", token);
        tokens[i++] = token;

        token = strtok(NULL, DELIMITERS);
    }


    tokens[i] = NULL;
    return tokens;
}

void print_aliases(List aliases) {
    print_list(aliases);
}

bool check_alias(char* name, List aliases) {
    if (contains_alias(aliases, name))
        return true;
    return false;
};