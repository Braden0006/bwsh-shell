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
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stderr, "Database opened successfully!\n");
	}

	char *commands[] = {"ls", "cd", "history", "alias", "pwd", "clear"};
	char *command = (char *)malloc(50 * sizeof(char));

	// Checks to see if memory allocation failed
	if (command == NULL) {
		free(command);
		perror("Memory allocation for user command failed!");
		exit(EXIT_FAILURE);
	}

	linked_list *list = create_list();

	// Infinite loop
	main_loop(command, commands, list);

	// Deallocates memory for the command the user entered
	free(command);

	// Deallocates memory for the linked list
	free_list(list);

	sqlite3_close(db);

	return 0;
}
