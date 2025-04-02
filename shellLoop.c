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
		char *commands[] = {"ls", "cd", "history", "alias", "pwd", "clear"};

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
			for (int i = 0; i < 6; i++) {
				if (strstr(command, commands[i]) != NULL) {

					// Checks to see if the user command starts with 'ls'
					if (strcmp(commands[i], commands[0]) == 0) {

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
					else if (strcmp(commands[i], commands[1]) == 0) {

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
					else if (strcmp(commands[i], commands[2]) == 0) {

						ncurses_terminal(list);

						is_command = true;
					}

					// Checks to see if the user command starts with 'alias'
					else if (strstr(commands[i], commands[3]) != NULL) {

						// Pointer to sqlite database
						sqlite3 *db;
						sqlite3_stmt *stmt;

						// Error message integer
						char *zErrMsg = 0;

						// Return code variable
						int rc;

						// Opens the database
						rc = sqlite3_open("test.db", &db);

						// Checks to see if the sqlite database can be opened or not
						if (rc != SQLITE_OK) {
							fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
						} else {
							fprintf(stderr, "Database opened successfully!\n");
						}

						char *duplicate_string;

						duplicate_string = strdup(command);

						// Tokenizes user input
						char **separated_command = tokenize_line(duplicate_string);
						
						// Creates table
						const char *create_table = 
							"CREATE TABLE IF NOT EXISTS Aliases ("
							"id INTEGER PRIMARY KEY AUTOINCREMENT, "
							"name TEXT NOT NULL, "
							"value TEXT NOT NULL);";

						// Executes the SQLite command
						rc = sqlite3_exec(db, create_table, 0, 0, &zErrMsg);

						if (rc != SQLITE_OK) {
							fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
							sqlite3_close(db);
							return;
						} else {
							printf("Table created successfully!\n");
						}


						// SQL command to insert data into Aliases table
						const char *sql = "INSERT INTO Aliases (name, value) VALUES (?, ?);";

						// Prepares the sqlite statement
						rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

						if (rc != SQLITE_OK) {
							fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
							sqlite3_close(db);
							return;
						}

						// Stores user input in separate variables
						char *name = separated_command[1];
						char *value = separated_command[2];

						// Binds the above values to the SQLite command
						sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
						sqlite3_bind_text(stmt, 2, value, -1, SQLITE_STATIC);

						rc = sqlite3_step(stmt);

						if (rc != SQLITE_DONE) {
							fprintf(stderr, "Execution failed: %s;\n", sqlite3_errmsg(db));
						} else {
							printf("Data inserted successfully!\n");
						}

						// Inserts command as node in beginning of linked list
						insertAtBeginning(list, command);

						is_command = true;

						// De-allocates memory for string
						free(duplicate_string);
						
						sqlite3_finalize(stmt);
						sqlite3_close(db);
					}

					// Checks to see if the user command starts with 'pwd'
					else if (strstr(commands[i], commands[4]) != NULL) {

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
					else if (strstr(commands[i], commands[5]) != NULL) {

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
