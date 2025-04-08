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

void main_loop(char *command) {

	linked_list *list = create_list();

	// Infinite loop
	for (;;) {

		// Array that stores key-value pairs of built-in commands, saved aliases are set as the values
		item commands[] = {{"ls", "ls"}, {"cd", "cd"}, {"history", "history"}, {"alias", "alias"}, {"pwd", "pwd"}, {"clear", "clear"}, {"delete", "delete"}};

		int num_commands = sizeof(commands) / sizeof(item);

		// Function that sets the users alias as the value in the key-value pair above
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

			// Creates duplicate string of user input
			char *duplicate_command = strdup(command);

			// Separates each word into different elements of a new array
			char **user_tokenized_command = tokenize_line(duplicate_command);

			// Boolean value that tracks whether the user command is a built-in command or not
			bool is_command = false;

			// Loops over each element in the "command" array
			for (int i = 0; i < num_commands; i++) {
				if (strstr(command, commands[i].value) != NULL) {

					// Checks to see if the user command starts with 'ls'
					if (strcmp(user_tokenized_command[0], commands[0].value) == 0) {

						// Changes the first work in the tokenized array to the original built-in command
						user_tokenized_command[0] = commands[0].key;

						// Creates the child process that executes the 'ls' command
						create_process(user_tokenized_command);

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;
					}

					// Checks to see if the user command starts with 'cd'
					else if (strcmp(user_tokenized_command[0], commands[1].value) == 0) {

						// Creates a separate child process that executes 'cd'
						create_process(user_tokenized_command);

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;
					}

					// Checks to see if the user command start with 'history'
					else if (strcmp(user_tokenized_command[0], commands[2].value) == 0) {

						ncurses_terminal(list);

						is_command = true;
					}

					// Checks to see if the user command starts with 'alias'
					else if (strstr(user_tokenized_command[0], commands[3].value) != NULL) {

						sqlite_add_record(command);

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;
					}

					else if (strstr(user_tokenized_command[0], commands[6].value) != NULL) {
						printf("About to delete a record!!!!\n");

						is_command = true;
					}

					// Checks to see if the user command starts with 'pwd'
					else if (strstr(user_tokenized_command[0], commands[4].value) != NULL) {

						// Changes the first work in the tokenized array to the original built-in command
						user_tokenized_command[0] = commands[4].key;

						// Creates separate child process for 'pwd' commmand
						create_process(user_tokenized_command);

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;
					}

					// Checks to see if the user command is "clear"
					else if (strstr(user_tokenized_command[0], commands[5].value) != NULL) {

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
