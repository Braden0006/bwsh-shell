#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/syslimits.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sqlite3.h>

#include "shell_functions.h"

void sqlite_check_command(item commands[], int num_commands) {

	sqlite3 *db;
	sqlite3_stmt *stmt;

	for (int i = 0; i < num_commands; i++) {

		char *zErrMsg = 0;

		int rc;

		rc = sqlite3_open("/Users/bradenwhitcher/workspace/github.com/Braden0006/bwsh-shell/build/test.db", &db);

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

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return;
		}

		const char *sql_command = "SELECT value FROM Aliases where name = ?;";

		// Prepares the sqlite statement
		rc = sqlite3_prepare_v2(db, sql_command, -1, &stmt, 0);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return;
		}

		char *key = commands[i].key;

		// Binds the above values to the SQLite command
		sqlite3_bind_text(stmt, 1, key, -1, SQLITE_STATIC);

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			int column_count = sqlite3_column_count(stmt);

			for (int i = 0; i < column_count; i++) {

				char *value_item;
				value_item = (char *)sqlite3_column_text(stmt, i);

				char *duplicate_value = strdup(value_item);

				if (!duplicate_value) {
					fprintf(stderr, "Memory allocation failed!\n");
					exit(EXIT_FAILURE);
				}


				commands[i].value = duplicate_value;

			}

			//printf("%s: %s\n", commands[i].key, commands[i].value);

		}

		if (rc != SQLITE_DONE) {
			fprintf(stderr, "Execution failed: %s;\n", sqlite3_errmsg(db));
		}

	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
