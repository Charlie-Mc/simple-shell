//
// Created by xbb21163 on 07/02/23.
//

#ifndef SIMPLE_SHELL_P2_EXECUTECOMMAND_H
#define SIMPLE_SHELL_P2_EXECUTECOMMAND_H

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int ExecuteCommand(char* argv[]);

#endif //SIMPLE_SHELL_P2_EXECUTECOMMAND_H
