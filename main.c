#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"

int main() {
    bool running = true;

    while (running) {
        running = parse();
    }
}
