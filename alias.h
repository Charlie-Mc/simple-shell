//
// Created by connor on 11/03/23.
//


#ifndef SIMPLE_SHELL_ALIAS_H
#define SIMPLE_SHELL_ALIAS_H

void alias(char** tokens, List aliases, char* input);
char** parse_alias(char* name, char* input, char** tokens, List aliases);
void print_aliases(List aliases);
bool check_alias(char* name, List aliases);

#endif //SIMPLE_SHELL_ALIAS_H
