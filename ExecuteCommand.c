//
// Created by Robbie Booth and Charlie McMicheal on 07/02/23.
//

#include "ExecuteCommand.h"

void execute (char* argv[]) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        perror(NULL);
        free(argv);
        exit(1);
    }

    if (pid == 0) {
        execvp(argv[0], argv);
        perror(argv[0]);
        free(argv);
        exit(1);
    }

    wait(NULL);
    free(argv);
}