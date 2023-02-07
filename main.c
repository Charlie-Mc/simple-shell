#include "parser.h"
#include "history.h"
#include "ExecuteCommand.h"

int main() {
    char input[MAX_INPUT];
    char** tokens = parse(input);
    char*  history[HISTORY_SIZE];

    while (tokens != NULL) {
        execute(tokens);
        tokens = parse(input);
        checkHist(tokens, history);
    }
}
