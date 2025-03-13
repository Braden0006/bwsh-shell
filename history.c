//
// Created by Braden Whitcher on 3/12/25.
//

#include <stdlib.h>
#include <stdio.h>

#include "history.h"

char command_history(const char *input) {
    int size = 0;
    size += 1;

    char *history = (char *)malloc(size * sizeof(char));

    for (int i = 0; i < size; i++) {
        history[0] = *input;
        printf("%s\n", history);
    }

    if (size == 0) {
        printf("this array is empty!!");
    }

    free(history);
    return 0;
}
