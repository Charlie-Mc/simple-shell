#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
    char cwd[MAX_CWD];
    cwdofsimp(cwd);
    char* path = getenv("PATH");
    List history = load_list(".hist_list");
    if (history == NULL)
        history = new_list();
    List aliases = load_list(".aliases");
    if (aliases == NULL)
        aliases = new_list();
    char input[MAX_INPUT + 2];


    char** tokens = readAndParseInput(input, history);

    int hist;
    
    while (tokens != NULL) {
        if (tokens[0] != NULL) {
            // hist => 0 means !! or !n
            hist = checkHist(&tokens, history);
            if (hist == 0)
                continue;
            // hist => 1 means non history external command
            else if (hist == 1) {
                runPredefined(tokens, aliases);
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

    // Save history in user's home directory
    chdir(getenv("HOME"));
    save_list(history, ".hist_list");
    clear(history);
    free(history);

    //debug mode as recommended by andrew, to remove this change DEBUG variable in parser.h to 0
    if (DEBUG) {
        printf("Old Path:\n");
        getenv("PATH");
    }

    //reset path on completion
    setenv("PATH", path, 1);

    if (DEBUG) {
        printf("Restored Path:\n");
        getenv("PATH");
    }

    return 0;
}
