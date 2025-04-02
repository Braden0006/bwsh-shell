//
// Created by Braden Whitcher on 3/17/25.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/syslimits.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sqlite3.h>

#include "shell_functions.h"

item *linear_search(item *commands, size_t size, const char *key) {
	for (size_t i = 0; i < size; i++) {
		if (strcmp(commands[i].key, key) == 0) {
			return &commands[i];
		}
	}

	return NULL;
}


void main_loop(char *command) {

	linked_list *list = create_list();

	// Infinite loop
	for (;;) {
		item commands[] = {{"ls", "ls"}, {"cd", "cd"}, {"history", "history"}, {"alias", "alias"}, {"pwd", "pwd"}, {"clear", "clear"}};

		int num_commands = sizeof(commands) / sizeof(item);

		sqlite_check_command(commands, num_commands);

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
			for (int i = 0; i < num_commands; i++) {
				if (strstr(command, commands[i].value) != NULL) {

					// Checks to see if the user command starts with 'ls'
					if (strcmp(commands[i].value, commands[0].value) == 0) {

						char *duplicate_string;

						duplicate_string = strdup(command);

						// Tokenizes the input command and saves it to a separate variable
						char **user_line = tokenize_line(duplicate_string);

						// Creates the child process that executes the 'ls' command
						create_process(user_line);

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;

						free(duplicate_string);
					}

					// Checks to see if the user command starts with 'cd'
					else if (strcmp(commands[i].value, commands[1].value) == 0) {

						char *duplicate_string;

						duplicate_string = strdup(command);

						// Tokenizes user input and saves it to separate variable
						char **user_input_cd = tokenize_line(duplicate_string);

						// Creates a separate child process that executes 'cd'
						create_process(user_input_cd);

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;

						free(duplicate_string);
					}

					// Checks to see if the user command start with 'history'
					else if (strcmp(commands[i].value, commands[2].value) == 0) {

						ncurses_terminal(list);

						is_command = true;
					}

					// Checks to see if the user command starts with 'alias'
					else if (strstr(commands[i].value, commands[3].value) != NULL) {

						sqlite_add_record(command);
						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;
					}

					// Checks to see if the user command starts with 'pwd'
					else if (strstr(commands[i].value, commands[4].value) != NULL) {

						char *duplicate_string;

						duplicate_string = strdup(command);

						// Tokenizes user input
						char **user_command_clear = tokenize_line(duplicate_string);

						// Creates separate child process for 'pwd' commmand
						create_process(user_command_clear);

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;

						free(duplicate_string);
					}

					// Checks to see if the user command is "clear"
					else if (strstr(commands[i].value, commands[5].value) != NULL) {

						// Clears the terminal
						system("clear");

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

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

				// Inserts command as node in beginning of list
				insertAtBeginning(list, command);

				printf("This is not a built-in command!\n");
			}
		}
	}

	// Deallocates memory for the linked list
	free_list(list);
}
