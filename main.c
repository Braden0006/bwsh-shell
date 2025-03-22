#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <stdlib.h>
#include <stdbool.h>

#include "shell_functions.h"

// TODO: separate data structure and data integration into separate files
// TODO: create the functionality for the built-in "cd" command
// TODO: properly set up SQLite database for aliases

int main()
{
	char *commands[] = {"ls", "cd", "history", "alias", "pwd"};
	char *command = (char *)malloc(50 * sizeof(char));

	// Checks to see if memory allocation failed
	if (command == NULL) {
		free(command);
		perror("Memory allocation for user command failed!");
		exit(EXIT_FAILURE);
	}

	char *commandHistory[3] = {};

	// Infinite loop
	main_loop(command, commands, commandHistory);

	// Deallocates memory for the command the user entered
	free(command);

	return 0;
}
