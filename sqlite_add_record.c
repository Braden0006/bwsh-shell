
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/syslimits.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sqlite3.h>

#include "shell_functions.h"

void sqlite_add_record(char *command) {

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

	// De-allocates memory for string
	free(duplicate_string);
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
