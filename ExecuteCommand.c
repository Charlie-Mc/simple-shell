//
// Created by Robbie Booth and Charlie McMicheal on 07/02/23.
//

#include "ExecuteCommand.h"

int ExecuteCommand(char *argv[]) {
    pid_t pid;
    pid = fork();
    Char* pathFile;

    if (&pathFile == NULL){
        fprintf(stderr, "file path NULL");
        return 1;
    }
//    Error occured
    if(pid < 0){
        fprintf(stderr, "Fork execute command failed");
        return 1;
    }
//    Child Process
    else if( pid == 0) {
        execv(pathFile, *argv[]);
    }
    //Parent Process
    else{
//        Wait for child
        wait(NULL);
        printf("Child Process Complete");
    }
    return 0;
}