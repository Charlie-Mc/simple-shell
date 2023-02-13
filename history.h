//
// Created by conno on 07/02/2023.
//


#include <string.h>
#ifndef stdio_h
#define stdio_h
    #include <stdio.h>
#endif

#ifndef stdbool_h
#define stdbool_h
    #include <stdbool.h>
#endif

#ifndef stdlib_h
#define stdlib_h
    #include <stdlib.h>
#endif


int checkHist(bool prevCalled, char** argv, char** history);
void printHistory(char** history);