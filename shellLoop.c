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

	// Infinite loop
	for (;;) {

		char const target[] = "quit";

		printf("\n$ ");

		// Reads line from filestream
		fgets(command, 256, stdin);

		// Replaces newline character with NULL terminator character
		command[strcspn(command, "\n")] = '\0';

		// Checks if the input string is equal to "quit" to break out of infinite loop
		if (strcmp(command, target) == 0) {
			break;
		}
		else {

			// Boolean value that tracks whether the user command is a built-in command or not
			bool is_command = false;

			// Loops over each element in the "command" array
			for (int i = 0; i < 5; i++) {
				if (strstr(command, commands[i]) != NULL) {

					// Checks to see if the user command starts with 'ls'
					if (strcmp(commands[i], commands[0]) == 0) {

						// Tokenizes the input command and saves it to a separate variable
						char **user_line = tokenize_line(command);

						// Creates the child process that executes the 'ls' command
						create_process(user_line);

						is_command = true;
					}

					// Checks to see if the user command starts with 'cd'
					else if (strcmp(commands[i], commands[1]) == 0) {

						// Tokenizes user input and saves it to separate variable
						char **user_input_cd = tokenize_line(command);

						// Creates a separate child process that executes 'cd'
						create_process(user_input_cd);

						is_command = true;
					}

					// Checks to see if the user command start with 'history'
					else if (strcmp(commands[i], commands[2]) == 0) {

						// Prints the command history
						printHistory(commandHistory);
						is_command = true;
					}

					// Checks to see if the user command starts with 'alias'
					else if (strstr(commands[i], commands[3]) != NULL) {

						// Tokenizes user input
						tokenize_line(command);

						is_command = true;
					}

					// Checks to see if the user command starts with 'pwd'
					else if (strstr(commands[i], commands[4]) != NULL) {

						// Tokenizes user input
						char **user_command_clear = tokenize_line(command);

						// Creates separate child process for 'pwd' commmand
						create_process(user_command_clear);

						is_command = true;
					}

					else {
						is_command = false;
					}

					break;
				}
			}

			// Lets the user know the command they entered is not valid
			if (is_command == false) {
				printf("This is not a built-in command!\n");
			}
		}
	}
}
