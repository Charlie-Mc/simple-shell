#include "parser.h"
#include "ExecuteCommand.h"

int main() {
    char input[MAX_INPUT];
    char** tokens = parse(input);

    while (tokens != NULL) {
        execute(tokens);
        tokens = parse(input);
    }
}
