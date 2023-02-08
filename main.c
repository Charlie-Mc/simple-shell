#include "parser.h"
#include "history.h"
#include "ExecuteCommand.h"

int main() {
    char input[MAX_INPUT];
    char** tokens = parse(input);
    char** history = malloc(HISTORY_SIZE * sizeof(char*));
    *history = malloc(sizeof(char*));

    while (tokens != NULL) {
        checkHist(tokens, history);
        //execute(tokens);
        tokens = parse(input);
    }
}
