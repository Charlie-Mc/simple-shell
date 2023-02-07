#include "parser.h"

int main() {
    char input[MAX_INPUT];
    char** tokens;

    do {
        tokens = parse(input);
    } while (tokens != NULL);
}
