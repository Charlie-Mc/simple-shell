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

    while(wait(&status) != pid);
    free(argv);
}

//predefined commands below here:

/* Path and working directory are different things.
 * Path is the global like system directory of the shell
 * and directory is the area that it is located in*/
void getPath(){
    printf("PATH : %s\n", getenv("PATH"));
}

int setSystemPath(char *path){
    setenv("PATH",path, 1);
    printf("Path restored!");
}

int changeDirectory(){

}

//Runs all of the predefined functions
//add another else if if you want to add a command
int RunPredefined(char *argv[]){
    char* command = argv[0];
    if(strcmp(command, "getpath")==0){
        getPath();
    }else if(strcmp(command, "setpath")==0){
        if(argv[1] != NULL){
            setSystemPath(argv[1]);
        }else{
            printf("setpath: No path parameter!");
            return 0;
        }

    }else if(strcmp(command, "cd")==0){
        changeDirectory();
    }else{
        execute(argv);
    }
    return 1;
}