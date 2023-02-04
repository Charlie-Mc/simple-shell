#include <stdbool.h>

#include "parser.h"

int main() {
    bool running = true;

    while (running) {
        running = parse();
    }
}
