#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parsing.h"

#define MAX_INPUT 512

int main(void) {
    bool running = true;

    while (running) {
        running = parse();
    }
}
