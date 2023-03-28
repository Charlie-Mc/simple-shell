#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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


    char** tokens = readAndParseInput(input, history, aliases);

    int hist;

    while (tokens != NULL) {
        if (tokens[0] != NULL) {
            // hist => 0 means !! or !n
            hist = checkHist(&tokens, history, aliases);
            if (hist == 0)
                continue;
            // hist => 1 means non history external command
            else if (hist == 1) {

                runPredefined(tokens);
                tokens = readAndParseInput(input, history, aliases);
            }
            // hist => 2 means history command not !! or !n
            else if (hist == 2) {
                free(tokens);
                tokens = readAndParseInput(input, history, aliases);
            }
        } else {
            free(tokens);
            tokens = readAndParseInput(input, history, aliases);
        }
    }

    // Save history in user's home directory
    chdir(getenv("HOME"));
    save_list(history, ".hist_list");
    clear(history);
    free(history);
    save_list(aliases, ".aliases");
    clear(aliases);
    free(aliases);

    //reset path on completion
    setSystemPath(path);

    if (DEBUG) {
        printf("Restored Path:\n");
        getPath();
    }

    return 0;
}
