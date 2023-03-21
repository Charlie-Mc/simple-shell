//
// Created by connor on 11/03/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"
#include "alias.h"

bool looping(char* name, List called, List aliases) {
    List new = new_list();
    for (int i = 0; i < size(called) - 1; ++i) {
        char* alias = get_at(called, i);
        strtok(strdup(alias), ",");
        char* token = strtok(NULL, DELIMITERS);
        char** tokens;
        int temp;
        while (token != NULL) {
            tokens[temp++] = token;
            if (contains_alias(aliases, token))
                add(new, token);
            if (contains_alias(new, name))
                return true;
            token = strtok(NULL, DELIMITERS);
        }
    }
    return looping(name, new, aliases);
}

bool check_loop(char** alias_tokens, List aliases) {
    int index = 2;
    List called = new_list();

    while (alias_tokens[index] != NULL) {
        if (strcmp(alias_tokens[1], alias_tokens[index]) == 0) {
            return true;
        }
        index++;
        if (contains_alias(aliases, alias_tokens[index]))
            add(called, alias_tokens[index]);
    }

    return looping(alias_tokens[1], called, aliases);
}

void alias(char** args, List aliases) {
    char* name = args[0];
    bool override = contains_alias(aliases, name);
    if (override) {
        printf("alias <%s> already exists, overriding\n", name);
        remove_at(aliases, index_of_alias(aliases,name));
    }

    if (size(aliases) >= MAX_ALIASES && !override) {
        printf("max number of aliases reached: %d", MAX_ALIASES);
        return;
    }

    if (check_loop(args, aliases)) {
        printf("<%s> alias cannot be made as this would cause a loop\n", name);
        return;
    }

    char* command = malloc(MAX_INPUT * sizeof(char));
    for (int i = 1; i < sizeof(args); ++i) {
        strcat(command, strcat(args[i], " "));
    }

    char* alias = malloc(MAX_INPUT * sizeof(char) + sizeof(name));
    strcat(alias, strcat(name, strcat(",", command)));
    alias[strlen(alias)-1] = '\n';
    add(aliases, strdup(alias));
    free(alias);
    free(command);
}

void unalias(char* name, List aliases) {
    if (size(aliases) == 0)
        printf("unalias: no aliases defined\n");
    else if (remove_at(aliases, index_of_alias(aliases, name)) == NULL)
        printf("unalias: no alias <%s> found\n", name);
}

bool parse_alias(int* i, char** tokens, char* name, List aliases) {
    strtok(strdup(get_at(aliases, index_of_alias(aliases, name))), ",");

    char* token = strtok(NULL, DELIMITERS);

    if (strcmp(token, "exit") == 0) {
        free(tokens);
        return false;
    }

    while (token != NULL) {
        if (DEBUG)
            printf("token = %s\n", token);
        tokens[(*i)++] = token;


        token = strtok(NULL, DELIMITERS);
    }
    return true;
}

void print_aliases(List aliases) {
    printf("Printing Aliases...");
    for (int i = 0; i < size(aliases) - 1; i++) {
        printf("%s\n", get_at(aliases, i));
    }
}

bool check_alias(char* name, List aliases) {
    if (contains_alias(aliases, name))
        return true;
    return false;
}
