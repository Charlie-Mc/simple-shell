//
// Created by xbb21163 on 07/02/23.
//

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void execute(char* argv[]);

int runPredefined(char* argv[]);

void getPath();

int setSystemPath(char *path);
