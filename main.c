#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(void) {
    bool running = true;
    char input[512];

    while (running) {
        bool parsingLine = true;

        printf("simpsh> ");

        // TODO: Rename penis before comitting
        char* penis = fgets(input, 512, stdin);
        if (penis == NULL) {
            running = parsingLine = false;
            printf("\n");
        }

        char* token = strtok(input, " \t\n|><&;");
        
        while (parsingLine) {
            printf("%s\n", token);
            if (strcmp(token, "exit") == 0) 
                running = parsingLine = false;
            token = strtok(NULL, " \t\n|><&;");
            if (token == NULL)
                parsingLine = false;
        }
    }
}
