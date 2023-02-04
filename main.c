#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_INPUT 512

int main(void) {
    bool running = true;
    char input[MAX_INPUT];

    while (running) {
        bool parsingLine = true;

        printf("simpsh> ");

        char* inputPtr = fgets(input, MAX_INPUT, stdin);
        if (inputPtr == NULL) {
            running = parsingLine = false;
            printf("\n");
        }

        char* token = strtok(input, " \t\n|><&;");
        if (token == NULL)
            parsingLine = false;
        
        while (parsingLine) {
            printf("\"%s\"\n", token);
            if (strcmp(token, "exit") == 0) 
                running = parsingLine = false;
            token = strtok(NULL, " \t\n|><&;");
            if (token == NULL)
                parsingLine = false;
        }
    }
}
