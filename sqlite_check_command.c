#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sqlite3.h>

#include "shell_functions.h"

void sqlite_check_command(item commands[], int num_commands) {

	// Defines variables for database
	sqlite3 *db;
	sqlite3_stmt *stmt;

	// Loops over built-in command array
	for (int i = 0; i < num_commands; i++) {

		char *zErrMsg = 0;

		int rc;

		// Opens the database file
		rc = sqlite3_open("/Users/bradenwhitcher/workspace/github.com/Braden0006/bwsh-shell/build/test.db", &db);

		// Error message if the database could not be opened
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Could not open database: %s\n", sqlite3_errmsg(db));
		}
		
		// Creates table if it doesn't exist
		const char *create_table = 
			"CREATE TABLE IF NOT EXISTS Aliases ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"name TEXT NOT NULL, "
			"value TEXT NOT NULL);";

		// Executes the SQLite command
		rc = sqlite3_exec(db, create_table, 0, 0, &zErrMsg);

		// Error message if the command above could not be executed
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return;
		}

		// SQL command to search for specific record in the Aliases table
		const char *sql_command = "SELECT value FROM Aliases where name = ?;";

		// Prepares the sqlite statement
		rc = sqlite3_prepare_v2(db, sql_command, -1, &stmt, 0);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return;
		}

		// Gets the key from the key-value pair array of built-in commands
		char *key = commands[i].key;

		// Binds the above values to the SQLite command
		sqlite3_bind_text(stmt, 1, key, -1, SQLITE_STATIC);

		// Loops over rows in each column
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {

			int column_count = sqlite3_column_count(stmt);

			for (int j = 0; j < column_count; j++) {

				// Gets the value of the SQLite column
				char *value_item;
				value_item = (char *)sqlite3_column_text(stmt, j);

				// Creates a duplicate
				char *duplicate_value = strdup(value_item);

				// Error message if duplication fails
				if (!duplicate_value) {
					fprintf(stderr, "Memory allocation failed!\n");
					exit(EXIT_FAILURE);
				}


				// Sets the value in the key-value pair as the alias value in the SQLite table
				commands[i].value = duplicate_value;

			}
		}

		if (rc != SQLITE_DONE) {
			fprintf(stderr, "Execution failed: %s;\n", sqlite3_errmsg(db));
		}
	}

	// Closes the database file
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
