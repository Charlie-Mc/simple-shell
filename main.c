#include "parser.h"
#include "ExecuteCommand.h"

//set path on start
int cwdofsimp(char *cwd){
    if (chdir(getenv("HOME")) != 0){
        perror("chdir() error()");
        return 0;
    }else {
        if (getcwd(cwd, MAX_CWD) == NULL){
            perror("getcwd() error");
            return 0;
        }else
            printf("current working directory is: %s\n", cwd);
        return 1;
    }
}

int main() {
    //set path on start
    char *path = getenv("PATH");
    char input[MAX_INPUT];
    char cwd[MAX_CWD];
    cwdofsimp(cwd);
    char** tokens = parse(input);

    while (tokens != NULL) {
        RunPredefined(tokens);
        tokens = parse(input);
    }

    //debug mode as recommended by andrew, to remove this change DEBUG variable in parser.h to 0
    if(DEBUG){
        printf("Old Path:");
        getPath();
    }

    //reset path on completion
    setSystemPath(path);

    if(DEBUG){
        printf("Restored Path:");
        getPath();
    }
}
