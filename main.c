#include "parser.h"
#include "history.h"
#include "execute.h"

int main() {
    char input[MAX_INPUT];
    get_input(input);
    char** tokens = parse(input);
    List history = new_list();
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
            get_input(input);
            tokens = parse(input);
        }
        // hist => 2 means history command not !! or !n
        if (hist == 2) {
            get_input(input);
            tokens = parse(input);
        }
    }
}
