//
// Created by connor on 11/03/23.
//


#include <stdbool.h>

#ifndef SIMPLE_SHELL_ALIAS_H
#define SIMPLE_SHELL_ALIAS_H

void alias(char** args, List aliases);
void unalias(char* name, List aliases);
bool parse_alias(int* i, char** tokens, char* name, List aliases);
void print_aliases(List aliases);
bool check_alias(char* name, List aliases);

#endif //SIMPLE_SHELL_ALIAS_H
