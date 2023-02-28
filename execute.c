//
// Created by Robbie Booth and Charlie McMicheal on 07/02/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
void getPath() {
    printf("PATH : %s\n", getenv("PATH"));
}

void setSystemPath(char *path) {
    setenv("PATH", path, 1);
    printf("Path restored!\n");
}


//part 4
// Changes the directory to the path given in the parameter
int changeDirectoryParameter(char *argv[]) {
    if (argv[1] != NULL) {
        if (chdir(argv[1]) != 0) {
            perror(argv[1]);
            return 0;
        }
        printf("Directory changed to: %s\n", argv[1]);
        return 0;
    }
    return 0;
}
// Changes the directory to the home directory
int changeDirectory() {
        char *path = getenv("HOME");
        if (chdir(path) != 0) {
            perror(NULL);
            return 0;
        }
        printf("Directory changed to: %s\n", path);
        return 0;
}

// Runs all the predefined functions
// Add another else if if you want to add a command

int runPredefined(char *argv[]) {
    char *command = argv[0];
    if (argv[0] == NULL)
        return 0;
    if (strcmp(command, "getpath") == 0) {
        if (argv[1] != NULL) {
            printf("getpath: Too many parameters!\n");
            return 0;
        }
        getPath();
    } else if (strcmp(command, "setpath") == 0) {
        if (argv[2] != NULL) {
            printf("setpath: Too many parameters!\n");
            return 0;
        }
        if (argv[1] != NULL) {
            setSystemPath(argv[1]);
        } else {
            printf("setpath: No path parameter!\n");
            return 0;
        }

        //change directory
    } else if (strcmp(command, "cd") == 0) {
        //if no parameter is given, change to home directory
        if (argv[2] != NULL) {
            printf("cd: Too many parameters!\n");
            return 0;
        }
        if (argv[1] == NULL) {
            changeDirectory();
            return 0;
        }
        // else change to the directory given in the parameter
        changeDirectoryParameter(argv);
    } else {
        execute(argv);
    }
    return 1;
}

