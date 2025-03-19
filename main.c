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
	char *commands[] = {"ls", "cd", "history", "alias", "pwd", "cd"};
	char *command = (char *)malloc(50 * sizeof(char));

	char *commandHistory[3] = {};

	// Infinite loop
	main_loop(command, commands, commandHistory);

	// Deallocates memory for the command the user entered
	free(command);

	return 0;
}
