//
// Created by Braden Whitcher on 3/18/25.
//

#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

// Deals with the main, infinite loop
void main_loop(char *command, char *commands[], char *commandHistory[]);

// Prints the history of commands
void printHistory(char *input[]);

// Function for creating and executing a new process
int create_process(char **args);

// Tokenizes a line entered by the user
char **tokenize_line(char *line);

#endif //SHELL_FUNCTIONS_H
