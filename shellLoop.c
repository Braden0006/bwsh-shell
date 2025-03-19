//
// Created by Braden Whitcher on 3/17/25.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/syslimits.h>
#include <unistd.h>

#include "shell_functions.h"

void main_loop(char *command, char *commands[], char *commandHistory[]) {

	for (;;) {

		char const target[] = "quit";

		printf("\n$ ");
		fgets(command, 256, stdin);

		command[strcspn(command, "\n")] = '\0';

		// Checks if the input string is equal to "quit" to break out of infinite loop
		if (strcmp(command, target) == 0) {
			break;
		}
		else {
			bool booleanValue = false;

			for (int i = 0; i < 6; i++) {
				if (strstr(command, commands[i]) != NULL) {

					// Checks to see if the user command starts with 'ls'
					if (strcmp(commands[i], commands[0]) == 0) {

						// Tokenizes the input command and saves it to a separate variable
						char **user_line = tokenize_line(command);

						// Creates the child process that executes the 'ls' command
						create_process(user_line);

						booleanValue = true;

						if (commandHistory[0] == NULL) {
							commandHistory[0] = commands[i];
						} else {
							commandHistory[1] = commandHistory[0];
							commandHistory[0] = commands[i];
						}
					}

					// Checks to see if the user command starts with 'cd'
					else if (strcmp(commands[i], commands[1]) == 0) {

						// Tokenizes user input and saves it to separate variable
						char **user_input_cd = tokenize_line(command);

						// Creates a separate child process that executes 'cd'
						create_process(user_input_cd);

						if (commandHistory[0] == NULL) {
							commandHistory[0] = commands[i];
						} else {
							commandHistory[1] = commandHistory[0];
							commandHistory[0] = commands[i];
						}

						booleanValue = true;
					}

					// Checks to see if the user command start with 'history'
					else if (strcmp(commands[i], commands[2]) == 0) {

						// Prints the command history
						printHistory(commandHistory);
						booleanValue = true;
					}

					// Checks to see if the user command starts with 'alias'
					else if (strstr(commands[i], commands[3]) != NULL) {
						tokenize_line(command);
						booleanValue = true;
					}

					else if (strstr(commands[i], commands[4]) != NULL) {
						char **user_command_clear = tokenize_line(command);

						create_process(user_command_clear);

						booleanValue = true;
					}
					else if (strstr(commands[i], commands[5]) != NULL) {
						char **user_command_cd = tokenize_line(command);
						chdir(user_command_cd[1]);

						create_process(user_command_cd);

						booleanValue = true;
					}

					else {
						booleanValue = false;
					}

					break;
				}
			}

            // Lets the user know the command they entered is not valid
            if (booleanValue == false) {
                printf("This is not a built-in command!\n");
            }
		}
	}
}
