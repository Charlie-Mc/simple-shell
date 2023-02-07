//
// Created by Robbie Booth and Charlie McMicheal on 07/02/23.
//

#include "ExecuteCommand.h"

int ExecuteCommand(char* argv[]) {
    pid_t pid = fork();

    // Error occured
    if (pid < 0){
        fprintf(stderr, "Fork execute command failed\n");
        return 1;
    }
    // Child Process
    else if (pid == 0) {
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(1);
    }
    // Parent Process
    else {
        // Wait for child
        wait(NULL);
        printf("Child Process Complete\n");
    }
    return 0;
}