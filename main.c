#include "parser.h"
#include "ExecuteCommand.h"

int main() {
    char input[MAX_INPUT];
    char** tokens = parse(input);

    while (tokens != NULL) {
        ExecuteCommand(tokens);
        tokens = parse(input);
    }
}
