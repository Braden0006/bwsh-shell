//
// Created by Braden Whitcher on 3/12/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "history.h"

void printHistory(char *input[]) {
    for (int i = 0; i < 3; i++) {
        printf("%s\n", input[i]);
    }
}
