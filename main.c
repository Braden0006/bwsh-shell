#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>

#include "shell_functions.h"

int main()
{
	char *command = (char *)malloc(50 * sizeof(char));

	// Checks to see if memory allocation failed
	if (command == NULL) {
		free(command);
		perror("Memory allocation for user command failed!");
		exit(EXIT_FAILURE);
	}


	// Infinite loop
	main_loop(command);

	// Deallocates memory for the command the user entered
	free(command);


	return 0;
}
