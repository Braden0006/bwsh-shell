//
// Created by Braden Whitcher on 3/12/25.
//

#include <stdio.h>

#include "shell_functions.h"

// Prints every element in the 'input' array
void printHistory(char *input[]) {
    for (int i = 0; i < 3; i++) {
        printf("%s\n", input[i]);
    }
}
