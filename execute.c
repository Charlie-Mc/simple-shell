//
// Created by Robbie Booth and Charlie McMicheal on 07/02/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "list.h"
#include "execute.h"

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

    while(wait(&status) != pid);
    free(argv);
}

//predefined commands below here:

/* Path and working directory are different things.
 * Path is the global like system directory of the shell
 * and directory is the area that it is located in*/
void getPath(char* argv[]) {
    if (argv[1] != NULL) {
        printf("getpath: too many parameters\n");
        return;
    }
    printf("PATH : %s\n", getenv("PATH"));
}

void setSystemPath(char* argv[]) {
    if (argv[1] == NULL)
        printf("setpath: no parameters\n");
    else if (argv[2] != NULL)
        printf("setpath: too many parameters\n");
    else {
        setenv("PATH", argv[1], 1);
        printf("Path restored!\n");
    }
}


//part 4
// Changes the directory to the path given in the parameter
void changeDirectoryParameter(char* dir) {
    if (chdir(dir) != 0) {
        perror(dir);
        return;
    }
    printf("Directory changed to: %s\n", dir);
}
// Changes the directory
void changeDirectory(char* argv[]) {
    if (argv[1] == NULL)
        changeDirectoryParameter(getenv("HOME"));
    else
        changeDirectoryParameter(argv[1]);
}

// Runs all the predefined functions
// Add another else if if you want to add a command

void runPredefined(char *argv[], List aliases) {
    char* command = argv[0];
    if (argv[0] == NULL)
        return;
    if (strcmp(command, "getpath") == 0)
        getPath(argv);
    else if (strcmp(command, "setpath") == 0)
        setSystemPath(argv);
    else if (strcmp(command, "cd") == 0)
        changeDirectory(argv);
    else
        execute(argv);
}

