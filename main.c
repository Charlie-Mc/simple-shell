#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "parser.h"
#include "history.h"
#include "execute.h"

//set path on start
int cwdofsimp(char *cwd){
    if (chdir(getenv("HOME")) != 0){
        perror("chdir() error()");
        return 0;
    } else if (getcwd(cwd, MAX_CWD) == NULL){
        perror("getcwd() error");
        return 0;
    }
    printf("current working directory is: %s\n", cwd);
    return 1;
}

int main() {
    //set path on start
    char* path = getenv("PATH");
    char input[MAX_INPUT + 2];
    char cwd[MAX_CWD];
    cwdofsimp(cwd);
    List history = new_list();

    char** tokens = readAndParseInput(input, history);

    int hist;
    bool prevCalled;

    while (tokens != NULL) {
        if (tokens[0] != NULL) {
            // hist => 0 means !! or !n
            hist = checkHist(prevCalled, &tokens, history);
            prevCalled = false;
            if (hist == 0)
                prevCalled = true;
            // hist => 1 means non history external command
            else if (hist == 1) {
                runPredefined(tokens);
                tokens = readAndParseInput(input, history);
            }
            // hist => 2 means history command not !! or !n
            else if (hist == 2) {
                free(tokens);
                tokens = readAndParseInput(input, history);
            }
        } else {
            free(tokens);
            tokens = readAndParseInput(input, history);
        }
    }

    //debug mode as recommended by andrew, to remove this change DEBUG variable in parser.h to 0
    if (DEBUG) {
        printf("Old Path:\n");
        getPath();
    }

    //reset path on completion
    setSystemPath(path);

    if (DEBUG) {
        printf("Restored Path:\n");
        getPath();
    }

    return 0;
}
