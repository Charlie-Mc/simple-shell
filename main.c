#include "parser.h"
#include "history.h"
#include "execute.h"

int main() {
    char input[MAX_INPUT];
    char** tokens = parse(input);
    char** history = malloc(HISTORY_SIZE * sizeof(char*));
    *history = malloc(sizeof(char*));
    int hist;
    bool prevCalled;

    while (tokens != NULL) {
        // hist => 0 means !! or !n
        hist = checkHist(prevCalled, tokens, history);
        prevCalled = false;
        if (hist == 0) prevCalled = true;
        // hist => 1 means non history external command
        if (hist == 1) {
            execute(tokens);
            tokens = parse(input);
        }
        // hist => 2 means history command not !! or !n
        if (hist == 2) {
            tokens = parse(input);
        }
    }
}
